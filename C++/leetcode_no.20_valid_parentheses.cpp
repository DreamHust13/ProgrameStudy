/*
Given a string containing just the characters
'(', ')', '{', '}', '[' and ']', determine if the input string is valid.
The brackets must close in the correct order,
"()" and "()[]{}" are all valid but "(]" and "([)]" are not.
问题：括号匹配
注意：空串，”([])“，”}}}}]]“
*/
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
using namespace std;
/* 方法一：使用vector模拟栈
class Solution
{
public:
	bool ismatched(char second,char first)
	{
		switch(first)
		{
		case '(':
			if(second == ')')
				return true;
			break;
		case '{':
			if(second == '}')
				return true;
			break;
		case '[':
			if(second == ']')
				return true;
			break;
		}
//其余所有情况，如输入符号错误，不匹配等都是不匹配，返回false
		return false;
	}
	bool isValid(string s)
	{
//vector模拟栈
		vector<char> stack;
//s大小必为偶数
		if(s.size()%2 != 0)
			return false;
//s为空串
		if(s.size() == 0)
			return true;
//逐一判断是否匹配
		for(auto it = s.begin(); it != s.end(); it++)
		{
			if(*it == '(' || *it == '[' || *it == '{')
				stack.push_back(*it);
			else if(stack.size() == 0) //表明栈空，现在的字符却为}、]、)，不可能匹配
				return false;
			else
			{
				if(!ismatched(*it,*(stack.end()-1)))
					return false;
				stack.pop_back();//移除栈中最后一个元素
			}
		}
		if(stack.size() == 0)
			return true;
		else
			return false;
	}
};
*/

/* 方法二：使用stack
class Solution
{
public:
	bool ismatched(char second,char first)
	{
		switch(first)
		{
		case '(':
			if(second == ')')
				return true;
			break;
		case '{':
			if(second == '}')
				return true;
			break;
		case '[':
			if(second == ']')
				return true;
			break;
		}
//其余所有情况，如输入符号错误，不匹配等都是不匹配，返回false
		return false;
	}
	bool isValid(string s)
	{
		stack<char> temp;
//s大小必为偶数
		if(s.size()%2 != 0)
			return false;
//s为空串
		if(s.size() == 0)
			return true;
//逐一判断是否匹配
		for(auto it = s.begin(); it != s.end(); it++)
		{
			if(*it == '(' || *it == '[' || *it == '{')
				temp.push(*it);
			else if(temp.size() == 0) //表明栈空，现在的字符却为}、]、)，不可能匹配
				return false;
			else
			{
				if(!ismatched(*it,temp.top()))
					return false;
				temp.pop();//移除栈中最后一个元素
			}
		}
		if(temp.empty())
			return true;
		else
			return false;
	}
};
*/

/*方法三：使用关联容器map*/
class Solution
{
public:
	bool isValid(string s)
	{
		//卡在map的初始化，本想定义为const static的成员变量，但不能列表初始化。
		//之后又因为没有删除const，导致报错
		map<char,char> MapParentheses;
		MapParentheses.insert(pair<char,char>('(',')'));
		MapParentheses.insert(pair<char,char>('[',']'));
		MapParentheses.insert(pair<char,char>('{','}'));
		stack<char> temp;
		
		for(auto c : s)
		{
			if(MapParentheses.find(c) != MapParentheses.end())
				temp.push(c);
			else
			{
				if(temp.empty() || MapParentheses[temp.top()] != c)
					//用错pop，导致出错
					return false;
				else
					temp.pop();//移除栈中最后一个元素
			}
		}
		return temp.empty(); //形式很好！

	}
};


int main()
{
	//测试用例组
	vector<string> testCol;

	testCol.push_back("");//空串
	testCol.push_back("()");
	testCol.push_back("()[]{}");
	testCol.push_back("[)]");
	testCol.push_back("([])");
	testCol.push_back("}}}}]]");//!!!之前忽略了

	Solution sol;

for(auto &temp : testCol)
		cout << temp << ":\t"
		     <<(sol.isValid(temp) ? "true" : "false")<<endl;
	return 0;
}