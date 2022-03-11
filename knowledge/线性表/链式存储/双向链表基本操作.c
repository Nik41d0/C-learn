#include<stdio.h>
#include<stdlib.h>


typedef struct node
{
	int data;
	struct node *prior,*next;
}LinkList;


LinkList* INITLIST()
{
	LinkList *hd=(LinkList *)malloc(sizeof(LinkList));
	hd->next=hd;
	hd->prior=hd;
	return hd;
}


void CREALIST(LinkList *hd,int n)
{
	int i;
	LinkList *r=hd;
	for(i=1;i<=n;i++)
	{
		LinkList *p=(LinkList *)malloc(sizeof(LinkList));
		p->data=2*i;
		p->next=r->next;
		p->prior=r;
		hd->prior=p;
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
	printf("\n");
	p=hd->prior;
	while(p!=hd)
	{
		printf("%d ",p->data);
		p=p->prior;
	}
	printf("\n");
}


LinkList* Locate(LinkList *hd,int e)
{
	LinkList *p=hd->next;
	while(p!=hd)
	{
		if(p->data==e)
			return p;
		p=p->next;
	}
	return NULL;
}


void DELETEp(LinkList *hd,LinkList *p)
{
	p->next->prior=p->prior;
	p->prior->next=p->next;
	free(p);
}


void DELETEph(LinkList *hd,LinkList *p)
{
	LinkList *r=p->next;
	p->next=r->next;
	r->next->prior=r->prior;
	free(r);
}

void DELETEpq(LinkList *hd,LinkList *p)
{
	LinkList *r=p->prior;
	p->prior=r->prior;
	r->prior->next=p;
	free(r);
}


void INSH(LinkList *p,int e)
{
	LinkList *r=(LinkList *)malloc(sizeof(LinkList));
	r->data=e;
	r->next=p->next;
	r->next->prior=r;
	p->next=r;
	r->prior=p;
}


void INSQ(LinkList *p,int e)
{
	LinkList *r=(LinkList *)malloc(sizeof(LinkList));
	r->data=e;
	r->next=p;
	r->prior=p->prior;
	r->prior->next=r;
	p->prior=r;
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
	LinkList *hd=INITLIST(),*p=NULL;
	CREALIST(hd,20);
	PRINTLIST(hd);
	
	p=Locate(hd,20);
	DELETEp(hd,p);
	PRINTLIST(hd);
	
	p=Locate(hd,12);
	DELETEph(hd,p);
	PRINTLIST(hd);
	
	p=Locate(hd,12);
	DELETEpq(hd,p);
	PRINTLIST(hd);

	p=Locate(hd,12);
	INSH(p,9);
	PRINTLIST(hd);
	
	p=Locate(hd,12);
	INSQ(p,11);
	PRINTLIST(hd);
	
	FREELIST(hd);
	return 0;
}
