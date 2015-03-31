/*
	stl学习之函数对象
*/
#include "stdafx.h"
#include <iostream>
#include <numeric>
#include <vector>
#include <functional>

#define MAX 10
using namespace std;
vector<long> v(MAX);

int main()
{
	//Fill vector using conventional loop
	for(int i=0; i<MAX; i++)
		v[i] = i + 1;

	//Accumulate the sum of contained values
	long sum = accumulate(v.begin(), v.end(), 0);
	cout << "Sum of values == "<< sum << endl;

	//Accumulate the product of contained values
	long product = accumulate(v.begin(), v.end(), 1,multiplies<long>());//!!!注意
	//accumulate()在内部将每个容器中的对象和第三个参数作为multiplies函数对象的参数，multiplies(1,v[i])计算乘积。
	cout << "Product of values == "<< product << endl;
	//Product of values == 3628800//为10！

	return 0;
}