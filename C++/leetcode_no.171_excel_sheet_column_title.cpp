/*
Related to question Excel Sheet Column Title
Given a column title as appear in an Excel sheet, return its corresponding column number.
For example:
    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
	
//理解题意：对excel表，其列的表示方法，输入字母，输出对应的列号（开个excel就知道了）
//相当于26进制吧！！哇咔咔
//询问：是否输入大小写敏感
*/
#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
	int titleToNumber(string s)
	{
		int sum = 0;
		for(auto it = s.begin(); it != s.end() ; it++)
		{
			if(!isalpha(*it))
				return 0;//输入有误，返回0
			sum = sum*26 + toupper(*it) - 'A' + 1;
		}
		return sum;
	}
};
int main()
{
	Solution sol;
	vector<string> testCol;
	testCol.push_back(""); //输出：0
	testCol.push_back(" "); //输出：0
	testCol.push_back("AA"); //输出：27
	testCol.push_back("C"); //输出：3
	testCol.push_back("2a"); //输出：0
	testCol.push_back("aa"); //输出：27
for(const auto &it : testCol)
	{
		if(sol.titleToNumber(it))
			cout << it << " -> "<<sol.titleToNumber(it)<<endl;
		else
			cout << it << ":the wrong input!"<<endl;
	}
}