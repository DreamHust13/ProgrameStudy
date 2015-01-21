/*
	Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

	You may assume that the array is non-empty and the majority element always exist in the array.

思路：排序（快排），找中间元素，验证
剑指offerP163，先自己写，写一个出来后，再看其他，再总结，别怕
//若无，需要测试：数组是否为空，参数是否合格，是否存在这样的数（自己检测一下即可）
*/
/*
 Solution:
 1.Runtime: O(n2) — Brute force solution: Check each element if it is the majority element.暴力破解，全统计次数

 2.Runtime: O(n), Space: O(n) — Hash table: Maintain a hash table of the counts of each element, then find the most common one.哈希表

 3.Runtime: O(n log n) — Sorting: As we know more than half of the array are elements of the same value, we can sort the array and all majority elements will be grouped into one contiguous chunk. Therefore, the middle (n/2th) element must also be the majority element.排序，然后第n/2位置上的数字.转换为第n/2大的数字

 4.Average runtime: O(n), Worst case runtime: Infinity — Randomization: Randomly pick an element and check if it is the majority element. If it is not, do the random pick again until you find the majority element. As the probability to pick the majority element is greater than 1/2, the expected number of attempts is < 2.随机选数，然后判断

 5.Runtime: O(n log n) — Divide and conquer: Divide the array into two halves, then find the majority element A in the first half and the majority element B in the second half. The global majority element must either be A or B. If A == B, then it automatically becomes the global majority element. If not, then both A and B are the candidates for the majority element, and it is suffice to check the count of occurrences for at most two candidates. The runtime complexity, T(n) = T(n/2) + 2n = O(n logn).一分为二，分别选出一个，再进一步确定

 6.Runtime: O(n) — Moore voting algorithm: We maintain a current candidate and a counter initialized to 0. As we iterate the array, we look at the current element x:
If the counter is 0, we set the current candidate to x and the counter to 1.
If the counter is not 0, we increment or decrement the counter based on whether x is the current candidate.
After one pass, the current candidate is the majority element. Runtime complexity = O(n).根据数组特点，该数出现次数比其他所有的出现次数之和还大，current：当前抵消统计之和不为0的数字，finalcount低效的统计之和，选出最后统计之和不为0的数字

7.Runtime: O(n) — Bit manipulation: We would need 32 iterations, each calculating the number of 1's for the ith bit of all n numbers. Since a majority must exist, therefore, either count of 1's > count of 0's or vice versa (but can never be equal). The majority number’s ith bit must be the one bit that has the greater count.位操作，迭代32次，统计所有数二进制表示中‘1’的出现次数？？？？没明白


Update (2014/12/24): Improve algorithm on the O(n log n) sorting solution: We do not need to 'Find the longest contiguous identical element' after sorting, the n/2th element is always the majority.
*/

#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;

class Solution
{
public:
	int majorityElement(vector<int> &num)
	{
		int current = *(num.begin());
		int finalCount = 1;

		for(auto it = num.begin()+1; it!=num.end(); ++it)
		{
			if(*it == current)
				++finalCount;
			else
			{
				if(--finalCount <=0)
				{
					current = *it;
					finalCount = 1;
				}
			}
		}

		return (finalCount>0) ? current : 0;
	}
};

int main()
{
	Solution sol;
	vector<int> num;
	num.push_back(1);
	num.push_back(2);
	num.push_back(3);
	num.push_back(2);
	num.push_back(2);

	cout << sol.majorityElement(num) << endl;


	return 0;
}