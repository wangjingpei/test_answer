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
    //TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
    //TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�
	test_string1();
#ifdef WIN32
    system("pause");
#endif

	return 0;
}

