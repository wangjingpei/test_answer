#include <stdlib.h>
#include<string.h>
#include "qh_vector.h"
typedef struct Point{
	int x, y;
	char value;
}Point;
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
	assert(vec.capacity() == 16);//capacity��2���������������Ч��


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
	vec.resize(10);
	assert(vec.size() == 10);

 
}
void structtest()
{
	 
	qh::vector<Point>vec;
	for (int i(0); i < 10; i++)
	{
		Point temp;
		temp.x = i;
		temp.y = i + 1;
		temp.value = 'z';
		vec.push_back(temp);
	}
	vec.pop_back();
	assert(vec.size() == 9);
	return;
}
int main(int argc, char* argv[])s
{
    //TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
    //TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�
	chartest();
	inttest();
	structtest();
     

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

