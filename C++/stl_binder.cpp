/*
	stl学习之绑定器函数对象
		一个绑定器使用另一个函数对象f()和参数值V创建一个函数对象。被绑定函数对象必须为双目函数，也就是说有两个参数,A和B。STL 中的绑定器有：
       bind1st() 创建一个函数对象，该函数对象将值V作为第一个参数A。
       bind2nd()创建一个函数对象，该函数对象将值V作为第二个参数B。
	   
	之否定函数对象
		所谓否定(negator)函数对象，就是它从另一个函数对象创建而来，如果原先的函数返回真，则否定函数对象返回假。有两个否定函数对象：not1()和not2()。not1()接受单目函数对象，not2()接受双目函数对象。否定函数对象通常和绑定器一起使用。
*/
#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

//Data to randomize
int iarray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
vector<int> v(iarray, iarray+10);//vector初始化！！


int main()
{
	int k = 0, q = 0;
	k = count_if(v.begin(), v.end(), bind1st(greater<int>(),8));
	q = count_if(v.begin(), v.end(), bind2nd(greater<int>(),8));
	//注：bind1st把8作为第一个参数，即8>q，求小于8的数；而bind2nd则相反
	cout << "Number elements < 8 == "<< k <<endl;
	cout << "Number elements > 8 == "<< q <<endl;

	/*
	start = find_if(aList.begin(), aList.end(),	not1(bind1nd(greater<int>(), 6)));
	你必须使用not1，因为bind1nd返回单目函数。

	*/
	return 0;
}
