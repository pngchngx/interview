��Ŀ������ͨ��ͼƬ�����Ķ���https://github.com/zieckey/interview/blob/master/climber_problem/The%20problem.png 


1��û���ڴ�й©����resolve�����ж�̬�����ڴ棬���ڴ洢Mountain�������飬�������º��������õ��ã�
	void strToMountainArray(Mountain *&mountainArray, const char *str)
	int horizontal_walks(Mountain *&mountainArray, size_t mCount)
	int vertical_walks(Mountain *&mountainArray, size_t mCount)
    ֮����resolve������returned֮ǰ�ͷŶ�̬������ڴ档
    

2������ʱ�临�ӶȺͿռ临�Ӷ�

	void strToMountainArray(Mountain *&mountainArray, const char *str)
	�ַ�������N������һ��ʱ�临�Ӷ�O(N);

	int horizontal_walks(Mountain *&mountainArray, size_t mCount)
	ʱ�临�Ӷ�O(1)��

	int vertical_walks(Mountain *&mountainArray, size_t mCount)
	Mountain�������鳤��M������һ��ʱ�临�Ӷ�O(M)��	
	
	�ռ临�Ӷȶ���O(M)��


3��֮ǰ�ύ�ĺ���
	void strToMountainArray(Mountain *&mountainArray, const char *str)
   ���ܴ���mBegin��mEnd�Ƕ�λ�����������ֻ�ܴ���0~9��Χ�����֣��޸ĺ��ܹ������λ���ˣ�������˲���������
	
