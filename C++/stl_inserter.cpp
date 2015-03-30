/*
	stl学习之插入迭代器：back_inserter、front_inserter、inserter
*/
#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <list>

using namespace std;

int iArray[5] = {1, 2, 3, 4, 5};

void Display(list<int> &v, const char *s);

int  main()
{
	list<int> iList;

	//Copy iArray backwords into iList
	copy(iArray, iArray+5, front_inserter(iList));
	//copy(iArray, iArray+5, back_inserter(iList));//试试用back_inserter
	Display(iList,"Before find and copy");
	//5, 4, 3, 2, 1

	//Locate value 3 in iList
	list<int>::iterator p = find(iList.begin(), iList.end(), 3);

	//Copy first two iArray values to iList ahead of p
	copy(iArray, iArray+2, inserter(iList, p));//在p所指元素之前插入
	Display(iList, "After find and copy");
	//5, 4, 1, 2, 3, 2, 1

	//如果用find()去查找在列表中不存在的值，例如99。由于这时将p设置为past-the-end值。最后的copy()函数将iArray的值附加到链表的后部


	return 0;
}

//Display label s and contents of integer vector v
void Display(list<int> &v, const char *s)
{
	cout << endl << s << endl;
	copy(v.begin(),v.end(),ostream_iterator<int>(cout,"\t"));
	cout << endl;
}