/*
	Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
	For example, given n = 3, a solution set is:
	"((()))", "(()())", "(())()", "()(())", "()()()"
	
	回溯法，深度优先搜索，递归思想，卡特兰数，加油！
*/
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void generator(vector<string> &result, string s, int left, int right);

vector<string> generateParentheses(int n)
{
	vector<string> result;
	string s;
	generator(result, s, n, n);
	return result;
}

void generator(vector<string> &result, string s, int left, int right)
{
	if(left == 0 && right == 0)//s已包括所有左右括号
		result.push_back(s);
	if(left > 0)
		generator(result, s+'(', left-1, right);
	if(right > 0 && right > left)
		generator(result, s+')', left, right-1);
}

int main()
{
	int n = 6;
	vector<string> result = generateParentheses(n);
	int i=1;
	for(auto c : result)
	{
		cout << i << " : " << c << endl;
		i++;
	}

	return 0;
}