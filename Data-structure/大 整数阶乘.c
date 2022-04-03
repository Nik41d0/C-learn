#include<stdio.h>
#include<string.h>

int main()
{
	int i,j,n,t,ws=1,jw; // ws 为位数，jw 是进位，t 阶乘元素与临时结果的积
	int a[3000];
	printf("请输入n的值:");
	scanf("%d",&n);
	a[0]=1;
	for(i=2;i<=n;i++)
	{
		for(j=1,jw=0;j<=ws;j++)  // 每次循环初始化 进位 的值
		{
			t=a[j-1]*i+jw;
			a[j-1]=t%10;  // 保存每一次乘积的 末位数
			jw=t/10;
		}
		while(jw)  // 判断是否进位
		{
			++ws;
	        	a[ws-1]=jw%10;  //保存每一次进位的 倒数第二位 的值
			jw/=10;  // 看是否还需再次进位
		}
	}
	for(j=ws-1;j>=0;j--)
	printf("%d",a[j]);
	printf("\n");
}
