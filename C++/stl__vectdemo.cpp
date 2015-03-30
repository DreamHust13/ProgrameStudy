/*
	stl学习之容器迭代器的使用
*/
#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> intVector(100);

int  main()
{
	intVector[20] = 50;
	const vector<int>::iterator intIter = find(intVector.begin(),intVector.end(),50);
	*intIter = 123;//注：const指的是intIter为const，而非其指向的内容！！
	if(intIter != intVector.end())
		cout <<"Vector contains value "<< *intIter<<endl;//会变为123
	else
		cout <<"Vector does not contain 50"<<endl;
		
	return 0;
}