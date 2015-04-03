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