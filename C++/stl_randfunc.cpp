/*
	stl学习之函数对象：
		发生器函数对象：有一类有用的函数对象是“发生器”，这类函数有自己的内存，				  也就是说它能够从之前的调用中记住一个值
*/
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <vector>
#include <functional>

using namespace std;

//Data to randomize
int iarray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
vector<int> v(iarray, iarray+10);//vector初始化！！

void Display(vector<int> &vr, const char *s);
unsigned int RandInt(const unsigned int n);

int main()
{
	srand(time(NULL));//Seed random generator
	Display(v, "Before shuffle:");

	pointer_to_unary_function<unsigned int, unsigned int>
		ptr_RandInt = ptr_fun(RandInt);// Pointer to RandInt() //!!!注意
		//使用stl的单目函数模板定义了一个变量ptr_RandInt，并将地址初始化到函数RandInt().
	random_shuffle(v.begin(), v.end(), ptr_RandInt);

	Display(v, "After shuffle:");
	return 0;
}

void Display(vector<int> &v, const char *s)
{
	cout << endl << s << endl;
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

//Return next random value in sequence modulo n
unsigned int RandInt(const unsigned int n)
{
	return rand()%n;
}
