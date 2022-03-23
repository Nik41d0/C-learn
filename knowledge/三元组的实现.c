#include<stdio.h>
#define maxsize 100


typedef struct
{
	int i,j;
	int e;
}triple;
typedef struct
{
	triple data[maxsize+1];
	int mu,nu,tu;
}tsmat;


void cjsyz(tsmat *s)  //创建三元组，但要从键盘输入值
{
	int i;
	printf("共有几行几列几个非零元素");
	scanf("%d%d%d",&s->mu,&s->nu,&s->tu);
	for(i=1;i<=s->tu;i++)
		scanf("%d%d%d",&s->data[i].i,&s->data[i].j,&s->data[i].e);
}
void cjsyz1(tsmat *s,int a[],int h,int l)   //通过数组创建三元组
{
	int i,j,k=1;
	s->mu=h;
	s->nu=l;
	for(i=0;i<=h-1;i++)
		for(j=0;j<=l-1;j++)
			if(a[i*l+j]!=0)
			{
				s->data[k].i=i+1;
				s->data[k].j=j+1;
				s->data[k].e=a[i*l+j];
				k++;
			}
	s->tu=k-1;
}


void psyz(tsmat *s)  // 显示三元组
{
	int i;
	printf("行数:%d 列数:%d 值:%d\n",s->mu,s->nu,s->tu);
	printf("三元组为:\n");
	for(i=1;i<=s->tu;i++)
		printf("%4d%4d%4d\n",s->data[i].i,s->data[i].j,s->data[i].e);
}


void syzzz(tsmat *s,tsmat *k)  //三元组转置，以目的数组为基准
{
	k->mu=s->nu;
	k->nu=s->mu;
	k->tu=s->tu;
	if(s->tu>0)
	{
		int q=1,m,p;
		for(m=1;m<=s->tu;m++)
			for(p=1;p<=s->tu;p++)
				if(s->data[p].j==m)
				{
					k->data[q].i=s->data[p].i;
					k->data[q].j=s->data[p].j;
					k->data[q].e=s->data[p].e;
					q++;
				}
	}
}
void syzzzd(tsmat *s,tsmat *k)   //三元组转置，以原数组为基准
{
	int num[maxsize],i,copt[maxsize],col,q;
	k->mu=s->nu;
	k->nu=s->mu;
	k->tu=s->tu;
	if(s->tu>0)
	{
		for(i=1;i<=s->tu;i++)
			num[i]=0;
		for(i=1;i<=s->tu;i++)
			num[s->data[i].j]++;
		copt[i]=1;
		for(i=2;i<=s->nu;i++)
			copt[i]=copt[i-1]+num[i-1];
		for(i=1;i<=s->tu;i++)
		{
			col=s->data[i].j;
			q=copt[col];
			k->data[q].i=s->data[i].j;
			k->data[q].j=s->data[i].i;
			k->data[q].e=s->data[i].e;
			copt[col]++;
		}
	}
}


int main()
{
	int s[42]={0,12,9,0,0,0,0,0,0,0,0,0,0,0,0,0,-3,0,0,0,0,14,0,0,0,24,0,0,0,0,0,0,18,0,0,0,0,0,15,0,0,-7};
	tsmat a,k;
	//cjsyz(&a);
	cjsyz1(&a,s,6,7);
	psyz(&a);
	syzzz(&a,&k);
	psyz(&k);
	return 0;
}
