
#include "proxy_url_extractor.h"
#include <fstream>
#include <vector>
#include "tokener.h"

namespace qh
{

    namespace {

        template< class _StringVector, 
        class StringType,
        class _DelimType> 
            inline void StringSplit(  
            const StringType& str, 
            const _DelimType& delims, 
            unsigned int maxSplits, 
            _StringVector& ret)
        {
            unsigned int numSplits = 0;

            // Use STL methods
            size_t start, pos;
            start = 0;

            do
            {
                pos = str.find_first_of( delims, start );

                if ( pos == start )
                {
                    ret.push_back(StringType());
                    start = pos + 1;
                }
                else if ( pos == StringType::npos || ( maxSplits && numSplits + 1== maxSplits ) )
                {
                    // Copy the rest of the string
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, str.size() - start);
                    break;
                }
                else
                {
                    // Copy up to delimiter
                    //ret.push_back( str.substr( start, pos - start ) );
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, pos - start);
                    start = pos + 1;
                }

                ++numSplits;

            }
            while ( pos != StringType::npos );
        }
    }

    ProxyURLExtractor::ProxyURLExtractor()
    {
    }

    bool ProxyURLExtractor::Initialize( const std::string& param_keys_path )
    {
        std::ifstream ifs;
        ifs.open(param_keys_path.data(), std::fstream::in);
        typedef std::vector<std::string> stringvector;
        stringvector keysvect;
        
        while (!ifs.eof()) {
            std::string line;
            getline(ifs, line);
            if (ifs.fail() && !ifs.eof()) {
                fprintf(stderr, "SubUrlExtractor::LoadParamKeysFile readfile_error=[%s] error!!", param_keys_path.data());
                ifs.close();
                return false;
            }
            if (line.empty()) continue;

            keysvect.clear();
            StringSplit(line, ",", static_cast<unsigned int>(-1), keysvect);
            assert(keysvect.size() >= 1);
            keys_set_.insert(keysvect.begin(), keysvect.end());
            keys_set_.erase("");
        }

        ifs.close();

        return true;
    }

    std::string ProxyURLExtractor::Extract( const std::string& raw_url )
    {
        std::string sub_url;
        ProxyURLExtractor::Extract(keys_set_, raw_url, sub_url);
        return sub_url;
    }

    void ProxyURLExtractor::Extract( const KeyItems& keys, const std::string& raw_url, std::string& sub_url )
    {
#if 1
        //TODO 请面试者在这里添加自己的代码实现以完成所需功能
		Tokener token(raw_url);
		//private:
		//	const char* m_pData;	//! the source text string to be parsed
		//	const char* m_pCurPos;  //! At first, set it 0
		//	const char* m_pDataEnd; //!
		
		//Skip characters until the next character is the requested character.??????
		//Skip characters up to the character is the requested character............
		//char Tokener::skipTo( char to )
		//{ do{ c = next();} while (c != to);  back(); return c; }
		//======>>>bool Tokener::back() { --m_pCurPos; }
		//======>>>char Tokener::next() { return *m_pCurPos++; }
		//skip to the position of the first '?'
		token.skipTo('?');
		//what if more than one '?', skip over non-letter
		for (; !isalpha(token.current()); token.next());
		//token.next(); //skip one char : '?'      This function will make the current position flag move to next position
		
		std::string key;
		//bool isEnd() const  { return (m_pCurPos >= m_pDataEnd || *m_pCurPos == '\0'); }
		while (!token.isEnd()) {
			//Get the characters up to the next character <code>quote< / code>.
			//while ( *m_pCurPos++ != quote ) { ... }
			//return std::string( startpos, m_pCurPos - startpos - 1 );
			//so, m_pCurPos is the positio behind quote
			key = token.nextString('=');//now, m_pCurPos ======  1 + position'='
			//if string key include '&'
			if (key.find('&') != std::string::npos)
			{
				token.skipBackTo('&');
				key = token.nextString('=');
			}

			//if find out the 'key' in the set of string keys
			if (keys.find(key) != keys.end()) {
				//Gets size of data that can read from the current read position.---return (s32)(m_pDataEnd - m_pCurPos)
				const char* curpos = token.getCurReadPos();
				int nreadable = token.getReadableSize();

				/**
				* case 1:
				*  raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/&xx=yy"
				*  sub_url="http://hnujug.com/"
				*/
				//return empty string when '&' next to '=', i.e. parameter (char quote) is next to the current position
				//also when there is no '&'
				sub_url = token.nextString('&');//now, m_pCurPos ======  1 + position'&'

				if (sub_url.empty() && nreadable > 0) {
					/**
					* case 2:
					* raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/"
					* sub_url="http://hnujug.com/"
					*/
					assert(curpos);
					sub_url.assign(curpos, nreadable);
					if (sub_url.find('&') != std::string::npos)
						sub_url = std::string();
				}
			}
			
			//if there is no key in set of keys
			token.skipTo('&');
			//skipTo(char):when skip over '\0', m_pCurPos = startIndex;
			token.next();//skip one char : '&'
		}
#else
        //这是一份参考实现，但在特殊情况下工作不能符合预期
        Tokener token(raw_url);
        token.skipTo('?');
        token.next(); //skip one char : '?' 
        std::string key;
        while (!token.isEnd()) {
            key = token.nextString('=');
            if (keys.find(key) != keys.end()) {
                const char* curpos = token.getCurReadPos();
                int nreadable = token.getReadableSize();

                /**
                * case 1: 
                *  raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/&xx=yy"
                *  sub_url="http://hnujug.com/"
                */
                sub_url = token.nextString('&');

                if (sub_url.empty() && nreadable > 0) {
                    /**
                    * case 2: 
                    * raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/"
                    * sub_url="http://hnujug.com/"
                    */
                    assert(curpos);
                    sub_url.assign(curpos, nreadable);
                }
            }
            token.skipTo('&');
            token.next();//skip one char : '&'
        }
#endif
    }

    std::string ProxyURLExtractor::Extract( const KeyItems& keys, const std::string& raw_url )
    {
        std::string sub_url;
        ProxyURLExtractor::Extract(keys, raw_url, sub_url);
        return sub_url;
    }
}

