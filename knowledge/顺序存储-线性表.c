#include<stdio.h>
#include<stdlib.h>
#define LIST_SIZE 100  // 线性表的厨师长度
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

int Listinsert_LL(LinkList *l,int k,int e)  // 在线性表中在第k位置插入一个数e
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
void ClearList(LinkList *l)  // 伪清空，仅是吧空间个数设为0
{
	l->length=0;
}

int ListEmpty(LinkList *l)
{
	if(l->length==0)
		return 1;
	else
		return 0;
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

void ListDelete(LinkList *l,int k,int *e)  //  将第k个数删除
{
	int i;
	*e=l->p[k-1];
	for(i=k;i<l->length;i++)
		l->p[i-1]=l->p[i];
	l->length--;
}

int  main()
{
	LinkList a;
	int m;
	Initlist_LL(&a);
	for(m=1;m<=20;m++)
		Listinsert_LL(&a,m,m*m);
	PrintList(&a);
	ListDelete(&a,19,&m);
	printf("%d\n",m);
	PrintList(&a);
	DestroyList(&a);
	return 0;
}
