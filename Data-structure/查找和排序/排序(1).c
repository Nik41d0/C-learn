#include<stdio.h>

void InsSort(int r[],int n)	// 直接插入排序
{
	int i,j;
	for(i=2;i<=n;i++)
	{
		if(r[i]<r[i-1])
		{
			r[0]=r[i];
			j=i-1;
			while(r[j]>r[0])
			{
				r[j+1]=r[j];
				j--;
			}
			r[j+1]=r[0];
		}
	}
	printf("直接插入排序为:");
}


void BinSort(int r[],int n)	// 折半插入排序
{
	int low,high,mid,i,j;
	for(i=2;i<=n;i++)
		if(r[i]<r[i-1])
		{
			r[0]=r[i];
			low=1;
			high=i-1;
			while(low<=high)
			{
				mid=(low+high)/2;
				if(r[0]<r[mid])
					high=mid-1;
				else
					low=mid+1;
			}
			for(j=i-1;j>=low;j--)
				r[j+1]=r[j];
			r[low]=r[0];
		}
	printf("折半插入排序为:");
}


void xrsort(int r[],int dk,int n)
{
	int i,j;
	for(i=dk+1;i<=n;i++)
		if(r[i]<r[i-dk])
		{
			r[0]=r[i];
			for(j=i-dk;j>0&&r[j]>r[0];j-=dk)
				r[j+dk]=r[j];
			r[j+dk]=r[0];
		}
}
void ShellSort(int *L,int *dk,int t,int n)	// 希尔排序
{
	int k;
	for(k=0;k<t;k++)
		xrsort(L,dk[k],n);
	printf("希尔排序为:");
}


void MpSort(int r[],int n)	// 冒泡排序
{
	int i,j,exchange,t;
	printf("冒泡排序为:");
	for(i=1;i<=n-1;i++)
	{
		exchange=0;
		for(j=1;j<=n-i;j++)
		{
			if(r[j]>r[j+1])
			{
				t=r[j];
				r[j]=r[j+1];
				r[j+1]=t;
				exchange=1;
			}
		}
		if(exchange==0)
			return ;
	}
}


int parti(int r[],int low,int high)
{
	int pkey;
	r[0]=r[low];
	pkey=r[low];
	while(low<high)
	{
		while(low<high&&r[high]>=pkey)
			high--;
		r[low]=r[high];
		while(low<high&&r[low]<=pkey)
			low++;
		r[high]=r[low];
	}
	r[low]=r[0];
	return low;
}
void KsSort(int r[],int low,int high)	// 快速排序
{
	int piv;
	if(low<high)
	{
		piv=parti(r,low,high);
		KsSort(r,low,piv-1);
		KsSort(r,piv+1,high);
	}
}


void XzSort(int r[],int n)	// 简单排序
{
	int i,j,minxb,t;
	for(i=1;i<=n-1;i++)
	{
		minxb=i;
		for(j=i+1;j<=n;j++)
			if(r[j]<r[minxb])
				minxb=j;
		if(minxb!=i)
		{
			t=r[minxb];
			r[minxb]=r[i];
			r[i]=t;
		}
	}
	printf("简单排序为:");
}


int main()
{
	int a[11]={0,3,5,2,1,9,12,8,6,18,7},i;
	int dk[3]={5,3,1};
	InsSort(a,10);
	BinSort(a,10);
	ShellSort(a,dk,3,10);
	MpSort(a,10);
	KsSort(a,1,10);
	printf("快速排序为:");
	XzSort(a,10);
	for(i=1;i<=10;i++)
		printf("%d ",a[i]);
	return 0;
}
