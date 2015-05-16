#include <stdlib.h>
#include<string.h>
#include "qh_vector.h"

void chartest()
{
	qh::vector<char>vec;
	char data = 'a';
	char *result = "abcdefgf";

	for (int i = 0; i < 10; i++)
		vec.push_back(data + i);
	vec.pop_back();
	vec.resize(7,'a' );
	vec.push_back('f');
	int len = strlen(result);
	for (int i = 0; i < len; i++)
	{
		assert(vec[i]==result[i]);
	}
	assert(vec.size() == 8);
	assert(vec.capacity() == 16);//capacity按2倍数增长，以提高效率


}
void inttest()
{
	qh::vector<int>vec;
	for (int i = 0; i < 10; i++)
		vec.push_back(i);
	vec.pop_back();
	vec[3] = 20;
	vec.push_back(100);
	int result[] = { 0, 1, 2, 20, 4, 5, 6, 7, 8, 100 };
	for (int i(0); i < 10; i++)
		assert(vec[i] == result[i]);
	assert(vec.size() == 10);

 
}
void doubletest()
{
	return;
}
int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。
	chartest();
	inttest();
	doubletest();
     

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

