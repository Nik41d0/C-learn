#include<stdio.h>
#include<stdlib.h>
#define LIST_SIZE 100  // 线性表的初始长度
#define LIST_ADD 10     // 线性表的长度增量


typedef struct
{
	int *p;
	int length;  //  当前元素个数
	int listsize;  // 当前线性表的尺寸
}LinkList;


int Initlist_LL(LinkList *l)
{
	l->p=(int*)malloc(LIST_SIZE*sizeof(int)); // 申请空间
	if(!l->p)
		return 0;
	l->length =0;
	l->listsize=LIST_SIZE;
	return 1;
}

int Listinsert_LL(LinkList *l,int k,int e)  
{
	int *a,*b;
	if(k<1||k>l->length+1)
		return 0;
	if(l->length>=l->listsize)
	{
		int i,*newp=(int*)malloc((l->listsize+LIST_ADD)*sizeof(int));
		if(!newp)
			return 0;
		for(i=0;l->length;i++)
			newp[i]=l->p[i];
		free(l->p);
		l->p=newp;
	}
	b=&(l->p[k-1]);
	for(a=&l->p[l->length-1];a>=b;a--)
		*(a+1)=*a;
	*b=e;
	l->length++;
	return 1;
}


void DestroyList(LinkList *l) //清空线性表
{
	free(l->p);  //释放空间
}


void PrintList(LinkList *l)
{
	int i=0;
	while(i<l->length)
		printf("%d ",l->p[i++]);
	printf("\n");
}


int ListLength(LinkList *l)
{
	return l->length;
}


void Getp(LinkList *l,int i,int *e)
{
	*e=l->p[i-1];
}


int Locatp(LinkList *l,int e)
{
	int i;
	for(i=0;i<l->length;i++)
		if(l->p[i]==e)
			return i+1;
	return 0;
}


void Qbingji(LinkList *la,LinkList *lb)
{
	int length_a=ListLength(la),length_b=ListLength(lb),i,e;
	for(i=1;i<=length_b;i++)
	{
		Getp(lb,i,&e);
		if(Locatp(la,e)==0)
			Listinsert_LL(la,++length_a,e);
	}
}


void Qbingji1(LinkList *la,LinkList *lb)
{
	int i,j;
	for(i=0;i<lb->length;i++)
	{
		for(j=0;j<la->length;j++)
			if(la->p[j]==lb->p[i])
				break;
		if(j>=la->length)
		{
			la->p[la->length]=lb->p[i];
			la->length++;
		}
	}
}


void Qjiaoji(LinkList *la,LinkList *lb)
{
	int length_b=ListLength(lb),i,e;
	for(i=1;i<=length_b;i++)
	{
		Getp(lb,i,&e);
		if(Locatp(la,e)==0)
		{
			ListDelete(lb,i,&e);
			i--;
			length_b--;
		}
	}
}


void Qjiaoji1(LinkList *la,LinkList *lb)
{
	int i,j,k;
	for(i=0;i<lb->length;i++)
	{
		for(j=0;j<la->length;j++)
			if(la->p[j]==lb->p[i])
				break;
		if(j>=la->length)
		{
			for(k=j;k<=lb->length-2;k++)
				lb->p[k]=lb->p[k+1];
			lb->length--;
			i--;
		}
	}
}


int  main()
{
	LinkList la,lb;
	int i;
	Initlist_LL(&la);
	Initlist_LL(&lb);
	for(i=1;i<=20;i++)
		Listinsert_LL(&la,i,i);
	PrintList(&la);
	printf("\n");
	for(i=1;i<=8;i++)
		Listinsert_LL(&lb,i,2*i);
	PrintList(&lb);
	printf("\n");
	Qbingji(&la,&lb);
	//Qbingji(&la,&lb);
	PrintList(&la);
	printf("\n");
	DestroyList(&la);
	DestroyList(&lb);
	return 0;
}
