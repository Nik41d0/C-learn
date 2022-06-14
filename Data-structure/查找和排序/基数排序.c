#include<stdio.h>
#include<stdlib.h>


int getDight(int i,int d)	// d的值为1,2,3...，表示要求取的相应位的值，1表示求取个位
{
	int val;
	while(d--)
	{
		val=i%10;
		i/=10;
	}
	return val;
}

void RadixSort(int *list,int n,int digit)	// 基数排序算法的具体实现
{
	int radix=10;	// 基数
	int i=0,j=0,d;
	int *count=(int *)malloc(radix*sizeof(int));	// 存放各数据位的数据个数
	int *bucket=(int *)malloc(n*sizeof(int));
	for(d=1;d<=digit;d++)	// d的值为1,2,3...分别表示个、十、百位
	{
		for(i=0;i<radix;i++)
			count[i]=0;	// 置空某位是0~9数字的统计数据
		for(i=0;i<=n-1;i++)	// 统计某位是0~9数字个数
		{
			j=getDight(list[i],d);
			count[j]++;
		}
		for(i=1;i<radix;i++)	// count[i]表示各数据位的右边界索引、末位位置
			count[i]=count[i]+count[i-1];
		for(i=n-1;i>=0;i--)	// 分配
		{
			j=getDight(list[i],d);
			bucket[count[j]-1]=list[i];
			count[j]--;
		}
		for(i=0,j=0;j<=n-1;j++,i++)	// 收集
			list[i]=bucket[j];
	}
	free(count);
	free(bucket);
}


int main() 
{
	int i,a[]={278,109,63,930,589,184,505,268,8,83};
	RadixSort(a,10,3);
	printf("基数排序为:");
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	return 0;
}
