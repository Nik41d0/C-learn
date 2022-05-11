#include<stdio.h>
void  reverse(int  r[],int  left,int  right) // 将数组中的元素左右反转
{
	int t;
	while(left<right)
	{
		t=r[right];
		r[right]=r[left];
		r[left]=t;
		left++;
		right--;
	}
}
void  fun(int  r[],int  n,int  p) // n为有总共几个元素，p为将几个元素移动
{
	reverse(r,0,14);
	reverse(r,0,n-p-1);
	reverse(r,n-p,n-1);
}
int  main()
{
    int a[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},i;
    fun(a,15,5);
    for(i=0;i<=14;i++)
    printf("%d ",a[i]);
	return 0;
}
