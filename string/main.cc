#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "qh_string.h"


void test_string1()
{
// test string()
qh::string str;
assert( '\0' == *str[0] );
assert( 0 == str.size() );
assert( '\0' == *str.c_str() );
assert( '\0' == *str.data() );
 
// test copy assign
str = qh::string();
assert( '\0' == *str[0] );
assert( 0 == str.size() );
assert( '\0' == *str.c_str() );
assert( '\0' == *str.data() );
 
// test string(cahr *) && copy assign
str = qh::string( "jhsf" );
assert( 'j' == *str[0] );
assert( 4 == str.size() );
assert( 'j' == *str.c_str() );
assert( 'j' == *str.data() );
printf( "%s() all test OK!\n", __FUNCTION__ );
}
int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。
	test_string1();
#ifdef WIN32
    system("pause");
#endif

	return 0;
}

