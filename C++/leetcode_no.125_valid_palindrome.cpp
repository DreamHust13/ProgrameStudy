/*

Given a string, determine if it is a palindrome, considering only alphanumeric characters and    ignoring cases.
	For example,
	"A man, a plan, a canal: Panama" is a palindrome.
	"race a car" is not a palindrome.
Note:
	Have you consider that the string might be empty? This is a good question to ask during an interview.
For the purpose of this problem, we define empty string as valid palindrome.

问题：回文，忽略大小写，只考虑字母数字
注意：空串

*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    bool isPalindrome(string s)
    {
        if(s.size() == 0)
            return true;//根据题意
           
        auto start = s.begin();
        auto tail = s.end() - 1;
       
        while(start < tail)//注：!!!为start<tail,否则，对“ ”测试用例，会超出范围！！
        {
            while((start<s.end()) && !isalnum(*start))
                start++;
           
            while((tail>=s.begin()) && !isalnum(*tail))
                tail--;
               
            if( (start <= tail) && (toupper(*start) != toupper(*tail)))
                return false;
            else
            {
                start++;
                tail--;
            }
        }
        return true;
    }
};

int main()
{
	//测试用例组
	vector<string> testCol;

	testCol.push_back("");
	testCol.push_back(" ");//!!!之前忽略了
	testCol.push_back("A man, a plan, a canal: Panama");
	testCol.push_back("race a car");
	testCol.push_back("2aa4");//!!!之前忽略了
	
	Solution sol;
		
	for(auto &temp : testCol)
		{cout << temp << ":\t"
			  <<(sol.isPalindrome(temp) ? "true" : "false")<<endl;
	}
	return 0;
}

