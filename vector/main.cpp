#include <stdlib.h>
#include <assert.h>
#include "qh_vector.h"
using qh::vector;

int main(int argc, char* argv[])
{
	//TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
	//TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�

	vector<int> v1;
	assert(v1.size() == 0 && v1.capacity() == 0);
	assert(v1.empty());

	vector<char> v2(6, 'v');
	for (size_t i = 0; i < v2.size(); ++i)
	{
		assert(v2.data()[i] == 'v');
	}
	assert(v2.size() == 6 && v2.capacity() == 6);

	vector<char> v3;
	v3 = v2;
	for (size_t i = 0; i < v3.size(); ++i)
	{
		assert(v3.data()[i] == 'v');
	}
	assert(v3.size() == 6 && v3.capacity() == 6);

	vector<char> v4;
	char ch1 = 'q';
	char ch2 = 'h';
	v4.push_back(ch1);
	v4.push_back(ch2);
	assert(v4.size() == 2);
	assert(v4[0] == 'q' && v4[1] == 'h');

	v4.pop_back();
	assert(v4[0] == 'q');
	assert(v4.size() == 1);


#ifdef WIN32
	system("pause");
#endif

	return 0;
}

