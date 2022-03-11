// 用循环链表存储实现猴子选大王游戏,比如20个猴，数到7出圈，或100个猴子数到15出圈。

#include<stdio.h>
#include<stdlib.h>


typedef struct node
{
	int data;
	struct node *next;
}LinkList;


LinkList* INITLIST()
{
	LinkList *hd=(LinkList *)malloc(sizeof(LinkList));
	hd->next=hd;
	return hd;
}


void CREALIST(LinkList *hd,int n)
{
	int i;
	LinkList *r=hd;
	for(i=1;i<=n;i++)
	{
		LinkList *p=(LinkList *)malloc(sizeof(LinkList));
		p->data=i;
		p->next=r->next;
		r->next=p;
		r=p;
	}
}


void PRINTLIST(LinkList *hd)
{
	LinkList *p=hd->next;
	while(p!=hd)
	{
		printf("%d ",p->data);
		p=p->next;
	}
}


void CQPRINT(LinkList *hd,int m)
{
	int i=1;
	LinkList *p=hd,*r=NULL;
	while(hd->next!=hd)
	{
		p=p->next;
		if(p->next==hd)  p=p->next;
		i++;
		if(i==m)
		{
			r=p->next;
			p->next=r->next;
			printf("%d ",r->data);
			free(r);
			i=1;
			if(p->next==hd) p=p->next;
		}
	}
}


void FREELIST(LinkList *hd)
{
	while(hd->next!=hd)
	{
		LinkList *p=hd->next;
		hd->next=p->next;
		free(p);
	}
	free(hd);
}


int main()
{
	LinkList *hd=INITLIST();
	CREALIST(hd,20);
	PRINTLIST(hd);
	printf("\n");
	CQPRINT(hd,7);
	FREELIST(hd);
	return 0;
}
