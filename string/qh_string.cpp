#include "qh_string.h"

#include <string.h>

#include <assert.h>

namespace qh
{
    // TODO 将在这里写实现代码

    string::string()
        : data_(NULL), len_(0)
    {
		data_ = new char[1];
		assert(data_ != NULL);
		*data_ = '\0';
		len_ = 0;
    }

    string::string( const char* s )
    {
		if (s == NULL)
		{
			data_ = new char[1];
			assert(data_ != NULL);
			*data_ = '\0';
			len_ = 0;
		}
		else
		{
			len_ = strlen(s);
			data_ = new char[len_ + 1];
			assert(data_ != NULL);
			strcpy(data_, s);
		}
    }

    string::string( const char* s, size_t len )
    {
		if (s == NULL)
		{
			data_ = new char[1];
			assert(data_ != NULL);
			*data_ = '\0';
			len_ = 0;
		}
		else
		{
			size_t sLen = strlen(s);
			if (sLen > len)
			{
				data_ = new char[len + 1];
				assert(data_ != NULL);
				strncpy(data_, s, len);
				*(data_ + len) = '\0';
				len_ = len;
			}
			else
			{
				data_ = new char[len + 1];
				assert(data_ != NULL);
				strncpy(data_, s, len);
				len_ = len;
			}
		}
    }

    string::string( const string& rhs )
    {
		if (rhs.data_ == NULL)
		{
			data_ = new char[1];
			assert(data_ != NULL);
			*data_ = '\0';
			len_ = 0;
		}
		else
		{
			data_ = new char[rhs.len_ + 1];
			assert(data_ != NULL);
			strcpy(data_, rhs.data_);
			len_ = rhs.len_;
		}
    }

    string& string::operator=( const string& rhs )
    {
		if (data_ == rhs.data_ && len_ == rhs.len_)
		{
			return *this;
		}
		else
		{
			delete [] data_;
			data_ = new char[rhs.len_ + 1];
			assert(data_ != NULL);
			strcpy(data_, rhs.data_);
			len_ = rhs.len_;
			return *this;
		}
    }

    string::~string()
    {
		delete[] data_;
		data_ = NULL;
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        return data_;
    }

    const char* string::c_str() const
    {
        return data_;
    }

    char* string::operator[]( size_t index )
    {
		if (index < 0 || index > len_ - 1)
			return NULL;
		else
			return data_ + index;
    }
}
