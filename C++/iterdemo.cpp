/*
STL 中指针迭代器的使用
*/
#include "stdafx.h"
#include <iostream>
#include <algorithm>

using namespace std;

#define SIZE 100
int iarray[SIZE];

int main()
{
	iarray[20] = 50;
	int *ip = find(iarray,iarray+SIZE,50);
	if(ip == iarray+SIZE)
		cout << "not in."<<endl;
	else
		cout <<*ip << "in"<<ip-iarray <<endl;
	return 0;

}