#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
/*
	//二进制法:时间复杂度O(n^2)，空间复杂度O(1)
	//前提：数组中的元素数不超过int位数。用一个int整数表示位向量，第i位为1；表示选择S[i]为0，表示不选择。
 　　//这种方法最巧妙，其实可看做位向量法，只不过更加优化

vector<vector<int>> subsets(vector<int> &s)
{
	sort(s.begin(),s.end());//要求有序
	vector<vector<int>> result;
	const size_t size = s.size();//数组组成
	vector<int> temp;

	for(size_t i = 0; i<(1<<size); i++)
	{
		for(size_t j = 0; j<size; j++)
			if(i & (1<<j))
				temp.push_back(s[j]);
		result.push_back(temp);
		temp.clear();

	}
	return result;
}
*/

//位向量法：深搜，时间复杂度O(n^2)，空间复杂度O(n)
//设置一个位向量组，每个元素只有两种状态：选或者不选
void subsets(const vector<int> &S, vector<bool> &selected, int step, vector<vector<int>> &result);
vector<vector<int>> subsets(vector<int> &S)
{
	sort(S.begin(),S.end());

	vector<vector<int>> result;
	vector<bool> selected(S.size(),false);
	subsets(S, selected, 0, result);
	return result;
}

void subsets(const vector<int> &S, vector<bool> &selected, int step, vector<vector<int>> &result)
{
	if(step == S.size())
	{
		vector<int> temp;
		for(int i=0; i<S.size(); i++)
		{
			if(selected[i]==true)//=true与==true
				temp.push_back(S[i]);
		}
		result.push_back(temp);
		return;
	}

	//不选S[step]
	selected[step] = false;
	subsets(S, selected, step+1, result);
	//选S[step]
	selected[step] = true;
	subsets(S, selected, step+1, result);
}

int main()
{
	const int data[6] = {0};
	vector<int> s(data,data+1);
	vector<vector<int>> result = subsets(s);
	int count = 1;

	for(auto sub : result)
	{
		cout << count++ <<" : ";
		for(auto ch : sub)
			cout << ch << " ";
		cout<<endl;
	}
	
	return 0;
}