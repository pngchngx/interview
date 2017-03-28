题目内容请通过图片链接阅读：https://github.com/zieckey/interview/blob/master/climber_problem/The%20problem.png 


1、没有内存泄漏。在resolve函数中动态分配内存，用于存储Mountain类型数组，方便以下函数传引用调用：
	void strToMountainArray(Mountain *&mountainArray, const char *str)
	int horizontal_walks(Mountain *&mountainArray, size_t mCount)
	int vertical_walks(Mountain *&mountainArray, size_t mCount)
    之后在resolve函数的returned之前释放动态分配的内存。
    

2、关于时间复杂度和空间复杂度

	void strToMountainArray(Mountain *&mountainArray, const char *str)
	字符串长度N，遍历一次时间复杂度O(N);

	int horizontal_walks(Mountain *&mountainArray, size_t mCount)
	时间复杂度O(1)；

	int vertical_walks(Mountain *&mountainArray, size_t mCount)
	Mountain类型数组长度M，遍历一次时间复杂度O(M)；	
	
	空间复杂度都是O(M)。


3、之前提交的函数
	void strToMountainArray(Mountain *&mountainArray, const char *str)
   不能处理mBegin和mEnd是多位整数的情况，只能处理0~9范围的数字；修改后能够处理多位数了，并添加了测试用例。
	
