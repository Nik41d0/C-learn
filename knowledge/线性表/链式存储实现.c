#include<stdio.h>
#include<stdlib.h>


typedef struct node
{
	int data;
	struct node *next;
}LinkList;


LinkList* INITLIST()       //  初始化链表
{
	LinkList *hd=(LinkList *)malloc(sizeof(LinkList));
	hd->next=NULL;
	return hd;
}


void CREALIST(LinkList *hd)   //  前插
{
	int dt;
	scanf("%d",&dt);
	while(dt!=-1)
	{
		LinkList *p=(LinkList *)malloc(sizeof(LinkList));
		p->data=dt;
		p->next=hd->next;
		hd->next=p;
		scanf("%d",&dt);
	}
}
void CREALIST1(LinkList *hd)     //   尾插
{
	int dt;
	LinkList *r=hd;
	scanf("%d",&dt);
	while(dt!=-1)
	{
		LinkList *p=(LinkList *)malloc(sizeof(LinkList));
		p->data=dt;
		p->next=NULL;
		r->next=p;
		scanf("%d",&dt);
	}
}


void PRINTLIST(LinkList *hd)
{
	LinkList *p=hd->next;
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
}


void FREELIST(LinkList *hd)
{
	while(hd->next!=NULL)
	{
		LinkList *p=hd->next;
		hd->next=p->next;
		free(p);
	}
	free(hd);
}


int Getelem(LinkList *hd,int i,int *e)
{
	int j=1;
	LinkList *p=hd->next;
	while(p!=NULL&&j<i)
	{
		p=p->next;
		j++;
	}
	if(p!=NULL&&j==i)
	{
		*e=p->data;
		return 1;
	}
	return 0;
}
int Getelem1(LinkList *hd,int i, int *e)
{
	int j=1;
	LinkList *p=hd;
	while(p->next!=NULL&&j<i)
	{
		p=p->next;
		j++;
	}
	if(p->next!=NULL&&j==i)
	{
		LinkList *q=p->next;
		p->next=q->next;
		*e=q->data;
		free(q);
		return 1;
	}
	return 0;
}


int Lenght(LinkList *hd)       //  求链表元素个数
{
	int i=0;
	LinkList *p=hd->next;
	while(p!=NULL)
	{
		i++;
		p=p->next;
	}
	return i;
}


int locatelem(LinkList *hd,int e)         //  求元素 e 的位置
{
	LinkList *p=hd->next;
	int i=1;
	while(p!=NULL)
	{
		if(p->data==e) break;
		else p=p->next;
		i++;
	}
	if(p!=NULL) return i;
	else return 0;
}


void insertelem(LinkList *hd,int i,int e)
{
	int j=1;
	LinkList *q=(LinkList *)malloc(sizeof(LinkList)),*p=hd;
	q->data=e;
	while(j<i&&p->next!=NULL)
	{
		p=p->next;
		j++;
	}
	q->next=p->next;
	p->next=q;
}


int main()
{
	int e;
	LinkList *head=NULL;
	head=INITLIST();
	CREALIST(head);
	PRINTLIST(head);
	Getelem(head,5,&e);
	insertelem(head,1,e);
	PRINTLIST(head);
	FREELIST(head);
	return 0;
}
