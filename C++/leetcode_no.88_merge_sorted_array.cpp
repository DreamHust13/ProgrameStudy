/*
	Given two sorted integer arrays A and B, merge B into A as one sorted array.
Note:
	You may assume that A has enough space (size that is greater or equal to m + n) 
to hold additional elements from B. The number of elements initialized in A and B 
are m andn respectively.

有序数组合并：居然卡住了，淡定，慢慢来，可以的
*/
#include "stdafx.h"
#include <iostream>
using namespace std;

class Solution
{
public:
	void merge(int A[], int m, int B[], int n) 
    {
        if(m < 0 || n < 0)
		{
			return;
		}
		
		int indexA=m-1;
		int indexB=n-1;
		int indexCurrent = m+n-1;
		//假设排序是升序排列的
		//假设是排序的！！
		//题意：将B插入A中，故从后往前找

		while(indexB >= 0 && indexCurrent>=0)   //仍有需要插入的数据
		{
			if(indexA < 0)
				break;

			if(A[indexA] >=B [indexB])
				A[indexCurrent--] = A[indexA--];
			else
				A[indexCurrent--] = B[indexB--];
		}

		//！！！之前忘记了
		while(indexB >= 0)
		{
			A[indexCurrent--] = B[indexB--];
		}

    }
};

int main()
{	
	Solution sol;


//测试1:a空
	int a1[10];//特殊情况：a[]
	int b1[4]={1,3,5,6};

	sol.merge(a1,0,b1,4);

	for(auto p : a1)
		cout << p << " ";
	cout << endl;

//测试2:a长，b短
	int a2[10]={0,1,4,7};
	int b2[3]={3,5,6};

	sol.merge(a2,4,b2,3);

	for(auto p : a2)
		cout << p << " ";
	cout << endl;

//测试3:a短，b长
	int a3[10]={0,1,2};
	int b3[4]={3,4,4,6};

	sol.merge(a3,3,b3,4);

	for(auto p : a3)
		cout << p << " ";
	cout << endl;


	return 0;
}