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


void ClearList(LinkList *l)  // 伪清空，仅是吧空间个数设为0，但原先线性表中的元素并未删除
{
	l->length=0;
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
