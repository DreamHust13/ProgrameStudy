/*
	题目：
		输入包含很多组2元组(ID1,ID2)。其中ID1、ID2均为32位正整数。任意两个2元组，如果包含了相同的数子，则这两个2元组合成同一个group。
		例如如下的输入：(1,8)(2,5)(3,5)(8,4)(2,3)
		按照规则，(2,5)(3,5)(2,3)合并成一个group，成员包含2,3,5
				   (1,8)(8,4)合并成第二个group，成员包含1,4,8
		要求：
		1. 假设内存是足够的，写一个函数来计算输入的2元组总共形成了多少个group，group各包含哪些成员，要求算法的效率尽可能高
		2.可以使用任何语言，并且需要定义必要的数组结构
		3.评估算法的时间和空间复杂度
*/
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <set>

using namespace std;

struct data
{   //二元组结构
    int id1;
    int id2;
};

void FindGroup(const vector<data> &input, vector<set<int>> &group)
{
	if(input.size() == 0)
		throw new logic_error("Invalid parameters.");

	for(const auto each1 : input)
	{
		bool isExist = false;

		if(group.size() == 0)//group为空
		{
			set<int> temp;
			temp.insert(each1.id1);
			temp.insert(each1.id2);
			group.push_back(temp);
		}
		else
		{
			for(auto &each2 : group)//要有&！！！
			{
				if(each2.find(each1.id1) != each2.end())//在当前set中找到该元素
				{
					each2.insert(each1.id2);
					//each2.insert(each1.id2);
					isExist = true;
					break;//继续下一个输入
				}
				if(each2.find(each1.id2) != each2.end())//在当前set中找到该元素
				{
					each2.insert(each1.id1);
					//each2.insert(each1.id2);
					isExist = true;
					break;//继续下一个输入
				}
			}
			if(!isExist)//无包含的group，需新建set插入
			{
				set<int> temp;
				temp.insert(each1.id1);
				temp.insert(each1.id2);
				group.push_back(temp);
			}
		}
	}
}

int main()
{
	struct data temp[] ={{1,8},{2,5},{3,5},{8,4},{2,3}};
	vector<data> input(temp,temp+5);
	vector<set<int>> group;//存储合并后结果的数组

	FindGroup(input, group);
	int number = 1;
	for(auto i = group.cbegin(); i != group.cend(); i++)
	{
		cout << "Group " << number << ": ";
		for(auto j = (*i).cbegin(); j != (*i).cend(); j++)
			cout << *j << "  ";
		cout << endl;
		number++;
	}

	return 0;
}