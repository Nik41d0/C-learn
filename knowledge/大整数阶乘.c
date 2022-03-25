#include<stdio.h>
#include<string.h>

int main()
{
	int i,j,n,t,ws=1,jw; // ws 为位数，jw 是进位，t 阶乘元素与临时结果的积
	int a[3000];
	printf("请输入n的值:");
	scanf("%d",&n);
	a[0]=1;
	for(i=1;i<=n;i++)
	{
		for(j=1,jw=0;j<=ws;j++)  // 每次循环初始化 进位 的值
		{
			t=a[j-1]*i+jw;
			a[j-1]=t%10;  // 保存第一次乘积的末位数
			jw=t/10;
		}
		while(jw)  // 判断是否进位
		{   ++ws;
	        a[ws-1]=jw%10;
			jw/=10;
		}
	}
	for(j=ws-1;j>=0;j--)
	printf("%d",a[j]);
	printf("\n");
}
