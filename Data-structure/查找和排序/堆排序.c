#include<stdio.h>


int c=0;	// 全局变量，记录交换次数
void swap(int a[],int i,int j)	// 交换a[i]和a[j]的值并计数
{
	int temp;
	temp=a[i];
	a[i]=a[j];
	a[j]=temp;
	c++;
}

void headpadjust(int a[],int m,int n)	// 调整a[m]到a[n]为大根堆
{
	int i;
	for(i=2*m;i<=n;i*=2)	// i=2*m-i为m的左孩子；i*=2-一次交换后可能引起后面子树的连锁交换
	{
		if(i+1>n)	// 如果m没有右孩子，i+1为m的右孩子
		{
			if(a[i]>a[m])	// 若左孩子大于根，交换左孩子和根
			{
				swap(a,i,m);
				m=i;	// 为子树连锁交换做准备
			}
			else	// 否则若根大于等于左孩子，本身就是大根堆，不用交换
				break;
		}
		else if(i+1<=n)	// 若m有左右两个孩子，i+1为m的右孩子
		{
			if(a[i+1]>a[i])	// 若右孩子大于左孩子
			{
				if(a[i+1]>a[m])	// 若大的右孩子大于根，交换根和右孩子
				{
					swap(a,i+1,m);
					i++;	// i取右子树
					m=i;	// 为子树连锁交换做准备 
				}
				else	// 否则大的孩子都小于等于根，则小的更小于根，跳出不用调整
					break;
			}
			else	// 若左孩子大于等于右孩子
			{
				if(a[i]>a[m])	// 若大的(或相等的)左孩子大于根，交换根和左孩子
				{
					swap(a,i,m);
					m=i;
				}
				else
					break;
			}
		}
	}
}

void headpadjust_s(int a[],int m,int n)	// 调整数值a[m]到a[n]为大根堆
{
	int i,temp;
	temp=a[m];
	for(i=2*m;i<=n;i*=2)	// 从m的左子树开始
	{
		if(i+1<=n&&a[i]<a[i+1])	// 若左孩子小于右孩子则i++，使i值为最大孩子的下标
			i++;
		if(a[i]<temp)	// 若最大孩子小于temp，则退出
			break;
		a[m]=a[i];
		m=i;
	}
	a[m]=temp;
}

void crtheap(int a[],int n)	// 初始化创建一个大顶堆
{
	int i;
	for(i=n/2;i>=1;i--)	// n/2-最后一个双条节点，依次向前建立大顶堆
		headpadjust(a,i,n);
}

void HeapSort(int a[],int n)
{
	int i;
	crtheap(a,n);	// 第一次调整为大根堆
	for(i=n;i>=2;i--)	// n-1趟调整/交换
	{
		swap(a,1,i);	// 将推顶的最大数(第一个数)，放到a[i]位置
		headpadjust(a,1,i-1);	// 对剩下的a[1]到a[i-1]，再调整
		
	}
}


int main() 
{
	int i;
	int a[11]={-1,8,5,2,6,0,3,9,1,7,4};	// a[0]为使用
	HeapSort(a,10);
	printf("共交换数据%d次\n",c);
	for(i=1;i<=10;i++)
		printf("%d ",a[i]);
	return 0;
}
