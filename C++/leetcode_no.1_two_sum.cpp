/*
	Given an array of integers, find two numbers such that they add up to a specific target number.

	The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

	You may assume that each input would have exactly one solution.

	Input: numbers={2, 7, 11, 15}, target=9
	Output: index1=1, index2=2

Solution:
暴力破解法：不被接受
	O(n2) runtime, O(1) space – Brute force:

	The brute force approach is simple. Loop through each element x and find if there is another value that equals to target – x. As finding another value requires looping through the rest of array, its runtime complexity is O(n2).
哈希表：O(n)
	O(n) runtime, O(n) space – Hash table:

	We could reduce the runtime complexity of looking up a value to O(1) using a hash map that maps a value to its index.

//不能排序：因为：输出为下标，而不是数字，会破坏结构
*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;



class Solution
{
public:
	vector<int> twoSum(vector<int> &numbers,int target)
	{
		unordered_map<int,int> mapping;
		vector<int> result;
		for(int i = 0; i<numbers.size() ; i++)
			mapping[numbers[i]] = i;//vector的下标操作！！！
	//	for(auto it = numbers.begin(); it != numbers.end() ; it++)
	//		mapping[*it] = it;
		for(int i=0 ; i<numbers.size() ; i++)
		{
			const int gap = target - numbers[i];
			if(mapping.find(gap) != mapping.end() && mapping[gap] > i)//!!!
			{
				result.push_back(i+1);
				result.push_back(mapping[gap]+1);
				break;
			}
		}
		return result;
	}
};

int main()
{
	Solution sol;
	int data[] = {3,2,4};//{1,2,3,4,5,6};{2,7,11,15};{-2,3,2,5,13}
	vector<int> numbers(data,data+sizeof(data)/sizeof(int));
	vector<int> result;

	result = sol.twoSum(numbers,6);
	cout<<"Sum 7 index is:"
		<<"index1="<<*result.begin()
		<<" index2="<<*(result.begin()+1)<<endl;
}