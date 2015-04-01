/*
	Implement atoi to convert a string to an integer.

	Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

	Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.

	spoilers alert... click to show requirements for atoi.

	Requirements for atoi:
	The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

	The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

	If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

	If no valid conversion could be performed, a zero value is returned. If the correct value is out of the range of representable values, INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.

	//审题：atoi，返回int型（想多了）
	//考虑情况：+、-、是否合法
	如果传的字符串指针为NULL；
	如果传的字符串为空；
	如果传的字符串中包含非法的字符；
	如果传的字符串中包含+-符号；
	如果字符串代表的整数超过了整数能表示的范围
	只有一个+或-，也是非法的
	忽略前面的空白"   98"
*/

#include "stdafx.h"
#include <iostream>

using namespace std;

bool isLegal = true;

class Solution
{
public:
	int atoi(const char *str)
	{
		int  sum = 0;//空串返0
		const char *p = str;
		bool isNegative = false;//是否为负数
		//或者设为int sign = 1;为负时设为-1，返回sign*sum
		//bool isDecimal = false;//是否为小数
		if(str == NULL)
		{
			isLegal = false;
			return 0;
		}
		//先过滤掉空格！！！
		while(*p==' '&&*p!='\0')//！！！
			p++;

		if(*p == '+')
		{
			//仅有“ +”不合法！！！
			p++;
			if(*p == '\0')
			{
				isLegal = false;
				return 0;
			}
		}
		else
		{
			if(*p == '-')
			{
				//仅有“ -”不合法！！！
				isNegative = true;
				p++;
				if(*p == '\0')
				{
					isLegal = false;
					return 0;
				}
			}
		}

		while(*p != '\0')
		{
			if(*p>='0' && *p<='9')
			{
				//	if(!isDecimal)//不是小数！！！
				//计算之前判断：不在int表示范围内！！！
				if(!isNegative)
				{
					if(sum>0x7fffffff/10 ||( sum==0x7fffffff/10 && (*p-'0') >= 0x7fffffff%10))
						return 0x7fffffff;//最大最小值表示法！！！
				}
				else
				{
					if(sum>0x80000000/10 ||( sum==0x80000000/10 && (*p-'0') >= 0x80000000%10))
						return (int)0x80000000;//最大最小值表示法！！！(0x不要漏掉了！！)
				}

				sum = sum*10+(*p-'0');

				//	else
				//		sum = sum + (*p-'0')*0.1;//计算方式不对！！
			}
			else
			{
				isLegal = false;//表示含非法部分
				break;//！！！返回可转换部分
				//	if(*p=='.' && !isDecimal)
				//	{
				//		isDecimal=true;
				//	}
				//	else
				//	{
				
				//	isLegal = false;
				//	return 0;


				//	}
			}
			p++;
		}

//		if( (isNegative&& sum>0x80000000) || (!isNegative&& sum>0x7fffffff))
//			return isNegative ? (int)0x80000000 : 0x7fffffff;

		return isNegative ? -sum : sum;
	}

};

int main()
{
	Solution sol;
	cout << sol.atoi("-2147483647")<<endl;
	//“-123”，“”，NULL，“  213”，超过范围，“+”
	//不规则输入，但是有效：“-3924x8fc”、“+413”
	//边界：“-2147483647”“-2147483648”“2147483647”
	//无效格式：“++c”、“++1”
	//溢出数据“2147483648”“9223372036854775809”

}