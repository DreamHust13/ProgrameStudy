/*
	stl学习之：流与迭代器
			   重点为将输入/输出流作为容器看待
			   任何接收迭代器参数的算法都可以和流一起工作
*/
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

void Display(vector<int> &v, const char *s);

int  main()
{
	//Seed the random number generator
	srand(time(NULL));//!!

	//Consruct vector and fill with random integer values
	vector<int> collection(10);
	for(int i=0; i<10; i++)
		collection[i] = rand() % 10000;//!!

	//Display, sort, and redisplay
	Display(collection, "Before sorting");
	sort(collection.begin(),collection.end());
	Display(collection, "After sorting");

	return 0;
}

//Display label s and contents of integer vector v
void Display(vector<int> &v, const char *s)
{
	cout << endl << s << endl;
	copy(v.begin(),v.end(),ostream_iterator<int>(cout,"\t"));//!!	//第三个参数实例化了ostream_iterator<int>类型，并将它作为copy()函数的输出目标迭代器对象。“\t”字符串是作为分隔符。
	cout << endl;
}