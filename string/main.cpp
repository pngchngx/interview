#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "qh_string.h"
using qh::string;


int main(int argc, char* argv[])
{
	//TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
	//TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�
	
	string s1;
	assert(*(s1.data()) == '\0' && s1.size() == 0);

	const char *cstr = "valar morghulis";
	string s2("valar morghulis");
	assert(strcmp(s2.data(), cstr) == 0);

	size_t cstrLen = strlen(cstr);
	string s3(cstr, 6);
	assert(strncmp(s3.data(), cstr, 6) == 0);

	string s4(cstr, cstrLen + 6);
	assert(strcmp(s4.data(), cstr) == 0);
	assert(s4.size() != cstrLen);

	string s5(s4);
	assert(strcmp(s5.data(), s4.data()) == 0);
	assert(s5.size() == s4.size());

	string s6;
	s6 = s2;
	assert(strcmp(s6.data(), s2.data()) == 0);
	assert(s6.size() == s2.size());

	string s7(s2);
	assert(*(s7[0]) == 'v');
	assert(s7[cstrLen] == NULL);



#ifdef WIN32
	system("pause");
#endif

	return 0;
}
