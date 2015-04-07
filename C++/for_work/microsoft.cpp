/*
	微软2016校园招聘在线笔试
	题目1 : Magic Box
	时间限制:10000ms
	单点时限:1000ms
	内存限制:256MB
描述
	The circus clown Sunny has a magic box. When the circus is performing, Sunny puts some balls into the box one by one. The balls are in three colors: red(R), yellow(Y) and blue(B). Let Cr, Cy, Cb denote the numbers of red, yellow, blue balls in the box. Whenever the differences among Cr, Cy, Cb happen to be x, y, z, all balls in the box vanish. Given x, y, z and the sequence in which Sunny put the balls, you are to find what is the maximum number of balls in the box ever.

	For example, let's assume x=1, y=2, z=3 and the sequence is RRYBRBRYBRY. After Sunny puts the first 7 balls, RRYBRBR, into the box, Cr, Cy, Cb are 4, 1, 2 respectively. The differences are exactly 1, 2, 3. (|Cr-Cy|=3, |Cy-Cb|=1, |Cb-Cr|=2) Then all the 7 balls vanish. Finally there are 4 balls in the box, after Sunny puts the remaining balls. So the box contains 7 balls at most, after Sunny puts the first 7 balls and before they vanish.

输入
Line 1: x y z

Line 2: the sequence consisting of only three characters 'R', 'Y' and 'B'.

For 30% data, the length of the sequence is no more than 200.

For 100% data, the length of the sequence is no more than 20,000, 0 <= x, y, z <= 20.

输出
The maximum number of balls in the box ever.

提示
Another Sample

Sample Input	Sample Output
0 0 0
RBYRRBY            	4


样例输入
1 2 3
RRYBRBRYBRY
样例输出
7
*/
#include "stdafx.h"
#include <iostream>
#include <string>
#include <cmath>//abs()
using namespace std;

int isMatch(int x, int y, int z, int abs_ry, int abs_rb, int abs_by)
{
	if((x==abs_ry && y==abs_rb&& z==abs_by) || (x==abs_ry && z==abs_rb && y==abs_by))
		return 1;
	if((y==abs_ry && x==abs_rb&& z==abs_by) || (y==abs_ry && z==abs_rb && x==abs_by))
		return 1;
	if((z==abs_ry && x==abs_rb&& y==abs_by) || (z==abs_ry && y==abs_rb && x==abs_by))
		return 1;

	return 0;
}
int main()
{
	int x=0, y=0, z=0;
	cin >> x >> y >> z;
	string input;
	cin >> input;
	
	int max = 0;
	int current = 0;
	int Cr=0, Cy=0, Cb=0;
	int abs_ry=0, abs_rb=0, abs_by=0;
	for(auto const ch : input)
	{
		switch(ch)
		{
			case('R'):
				Cr++;
				break;
			case('Y'):
				Cy++;
				break;
			case('B'):
				Cb++;
				break;
			default:
				throw new logic_error("Invalid input");
		}
		abs_ry=abs(Cr-Cy);
		abs_rb=abs(Cr-Cb);
		abs_by=abs(Cb-Cy);
		current++;
		if(current > max)
			max = current;

		if(isMatch(x, y, z, abs_ry, abs_rb, abs_by))
			current = 0;		
	}
	cout << max;

	return 0;
}




