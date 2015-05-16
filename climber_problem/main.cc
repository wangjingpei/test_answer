/**
*本题目的复杂度为o(n),只是顺次编译一遍即可
*由于题目中没有动态申请内存，故在题目中不存在内存泄露的问题
*该算法也解决了山峰位置，高度为多位数的问题
**/

#include <stdio.h>
#include<string.h>
#include<ctype.h>
#include <assert.h>

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))


//transfer the characters into number if they are numbers
int charToNum(const char *&p)
{
	int res = 0;
	while (isdigit(*p)){
		res *= 10;
		res += *p-'0';
		p++;
	}
	return res;
}
//skip to the next num
void skipToDigit(const char *&p)
{
	while (*p!='\0'&&!isdigit(*p))
		p++;
}
int resolve(const char* input)				//复杂度o（n)
{
	int curr_pos = 0,curr_height=0,result=0;
	const char *curr =input;
	int mount[3] = { 0, 0, 0 };	
	int mountNum = charToNum(curr); 
	skipToDigit(curr);
	for (int i(0); i < mountNum; i++)
	{
		for (int j(0); j < 3; j++)
		{
			mount[j] = charToNum(curr);
			skipToDigit(curr);
		}
		if (mount[0]>curr_pos)
		{
			result += curr_height;
			result += mount[2];
		}
		else  
		{
			int dis = mount[2]>curr_height ? mount[2] - curr_height : curr_height - mount[2];
			result += dis;
		}		
		curr_pos = mount[1];
		curr_height = mount[2];
	}
	//处理最后结果
	result += mount[2];
	result += curr_pos;//加上水平距离

	return result;
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
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
	    assert(resolve(input[i]) == expectedSteps[i]);
    }
    return 0;
}
