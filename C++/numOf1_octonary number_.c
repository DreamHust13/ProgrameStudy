#include "stdafx.h"
#include <stdio.h>

static long long prim_poly[33] =
{
	0,
	/*  1 */     1,
	/*  2 */    07,
	/*  3 */    013,
	/*  4 */    023,
	/*  5 */    045,
	/*  6 */    0103,
	/*  7 */    0211,
	/*  8 */    0435,
	/*  9 */    01021,
	/* 10 */    02011,
	/* 11 */    04005,
	/* 12 */    010123,
	/* 13 */    020033,
	/* 14 */    042103,
	/* 15 */    0100003,
	/* 16 */    0210013,
	/* 17 */    0400011,
	/* 18 */    01000201,
	/* 19 */    02000047,
	/* 20 */    04000011,
	/* 21 */    010000005,
	/* 22 */    020000003,
	/* 23 */    040000041,
	/* 24 */    0100000207,
	/* 25 */    0200000011,
	/* 26 */    0400000107,
	/* 27 */    01000000047,
	/* 28 */    02000000011,
	/* 29 */    04000000005,
	/* 30 */    010040000007,
	/* 31 */    020000000011, //坑：int型无法表示，把数组类型改了，就是long也不行
	/* 32 */    00020000007
};  /* Really 40020000007, but we're omitting the high order bit */

int main()
{
	unsigned int count = 0;
	for(int i=0; i<33; i++)
	{
		long long temp = prim_poly[i];
		while(temp>0)
		{
			if((temp%8) == 1)//!!!
				++count;
			temp=temp>>3;//!!!
		}
		printf("%d:%d\n",i,count);
	}

	printf("\n%d\n",count);

	/*
	 int temp=prim_poly[31];
	 count = 0;
	 while(temp>0)
	  {
	   if((temp%8) == 1)
	    ++count;
	   temp=temp>>3;
	  }
	  printf("%d\n",prim_poly[31]);
	*/
//	printf("%lld\n",prim_poly[31]);//!!!
	return 0;
}