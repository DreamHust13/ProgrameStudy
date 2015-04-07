/*
	输入两个整数n和m，从数列1,2,3...n中随意取几个数，使其和等于m，要求列出所有的组合。
*/
#include "stdafx.h"
#include <iostream>
#include <list>
using namespace std;

list<int> seq;

void findList(int sum, int num)
{
	if(num < 1 || sum < 1)
		return;
	if(sum == num)
	{
		for(auto i : seq)
			cout << i << "+";
		cout << num << endl;
	}
	seq.push_back(num);
	findList(sum-num, num-1);
	seq.pop_back();
	findList(sum, num-1);
}
 

int main()
{
	int num, sum;
	cin >> num >> sum;
	findList(sum,num);

	return 0;
}