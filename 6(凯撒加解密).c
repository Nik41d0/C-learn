#include<stdio.h>
#include<string.h>
int main()
{
	int i,n,b,x;
	char a[100];
	printf("加密请输入1\n解密请输入2\n请输入:");
	b:scanf("%d",&x);
	if(x!=1&&x!=2)
	{
		printf("不符合，请重输入:");		
		goto b; 
	}
	a:printf("请输入密钥(1~25):");
	scanf("%d",&n);
	if(n<=0||n>=26)
	{printf("不符合，请重输:");
	goto a;
	}
	if(x==1)//加密
	{
	printf("请输入要加密的明文:");
	scanf("%s",a);
	b=strlen(a);
	for(i=0;i<b;i++)
	{
		if((a[i]>='A'&&a[i]<='Z'-n)||(a[i]>='a'&&a[i]<='z'-n)) a[i]+=n;
		else if((a[i]>'Z'-n&&a[i]<='Z')||(a[i]>'z'-n&&a[i]<='z')) a[i]-=26-n;
	}
	}
	if(x==2)//解密
	{
		printf("请输入要解密的密文:");
		scanf("%s",a);
		b=strlen(a);
		for(i=0;i<b;i++)
		{
			if((a[i]>'A'+n&&a[i]<'Z')||(a[i]>'a'+n&&a[i]<='z')) a[i]-=n;
			else if((a[i]>='A'&&a[i]<='A'+n)||(a[i]>='a'&&a[i]<='a'+n)) a[i]+=26-n;
		}
	}
	for(i=0;i<=b;i++)
	printf("%c",a[i]);
	return 0;	
}
