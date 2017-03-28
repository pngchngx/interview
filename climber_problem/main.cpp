#include <stdio.h>
#include <assert.h>
#include <cstdlib>
#include <iostream>

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))


struct Mountain
{
	int mBegin;
	int mEnd;
	int mHeight;
};

void strToMountainArray(Mountain *&mountainArray, const char *str)
{
	int mIndex = 0;
	for (size_t i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] == '\n' && str[i + 1] != '\0')
		{
			mountainArray[mIndex].mBegin = str[i + 1] - '0';
			mountainArray[mIndex].mEnd = str[i + 3] - '0';
			mountainArray[mIndex].mHeight = str[i + 5] - '0';
			++mIndex;
		}
	}
}

int horizontal_walks(Mountain *&mountainArray, size_t mCount)
{
	return mountainArray[mCount - 1].mEnd;
}

int vertical_walks(Mountain *&mountainArray, size_t mCount)
{
	int notoverlaps = 0;
	int overlaps = 0;
	for (size_t mIndex = 0; mIndex != mCount - 1; ++mIndex)
	{
		notoverlaps += 2 * (mountainArray[mIndex].mHeight);
		if (mountainArray[mIndex].mEnd >= mountainArray[mIndex + 1].mBegin)
		{
			int temp = (mountainArray[mIndex].mHeight) < (mountainArray[mIndex + 1].mHeight) ? \
				mountainArray[mIndex].mHeight : mountainArray[mIndex + 1].mHeight;
			overlaps += 2 * temp;
		}
	}
	notoverlaps += 2 * (mountainArray[mCount - 1].mHeight);
	return notoverlaps - overlaps;
}



int resolve(const char* input)
{
	if (*input == '\0' || *input == '0')
		return 0;

	int mCount = input[0]-'0';

	Mountain *mountainArray = new Mountain[mCount];
	

	strToMountainArray(mountainArray, input);
	int hWalks = horizontal_walks(mountainArray, mCount);
	int vWalks = vertical_walks(mountainArray, mCount);
	int totalWalks = hWalks + vWalks;


	delete[] mountainArray;
	mountainArray = NULL;

	return totalWalks;
}

int main(int argc, char* argv[])
{
	const char* input[] = {
		"3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
		"1\n1,2,1\n",
		"2\n1,2,1\n2,3,2",
		"3\n1,2,1\n2,3,2\n3,6,1",
		"4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
		"5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
		"1\n0,1,1",
		"2\n0,1,1\n2,4,3",
		"3\n0,1,1\n2,4,3\n3,5,1",
		"4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
		"5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
		//TODO please add more test case here
	};
	int expectedSteps[] = { 25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20 };
	for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
	{
		assert(resolve(input[i]) == expectedSteps[i]);
		//std::cout << resolve(input[i]) << ' ';
	}
	//std::cout << std::endl;
	return 0;
}
