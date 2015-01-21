/*
Given a positive integer, return its corresponding column title as appear in an Excel sheet.
For example:
    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB 
	
与第171题相对
*/

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
	string convertToTitle(int num)
	{
		string current;

		if(num<1)
			return current;//返回空串
		while(num)
		{
			num--;//与26进制不同，是从1开始的，而不是0

			current = static_cast<char>('A'+num%26) + current;//必须强制类型转换
			num/=26;
		}

		return current;
	}
};

int main()
{
	Solution sol;
	vector<int> testCol;
	testCol.push_back(0);//特殊
	testCol.push_back(1);//边界
	testCol.push_back(26);//输出有误，应为Z，却为A@
	testCol.push_back(3);
	testCol.push_back(28);


for(const auto it : testCol)
		cout << it <<" -> " << sol.convertToTitle(it) <<endl;
	return 0;
}