#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	char data;
	struct node *next;
}listnode;


listnode* INITLIST()
{
	listnode *hd=(listnode *)malloc(sizeof(listnode));
	hd->next=NULL;
	return hd;
}


void CREALISTWCSZ(listnode *hd,char a[])
{
	int i=0;
	listnode *r=hd;
	while(a[i]!='\0')
	{
		listnode *p=(listnode *)malloc(sizeof(listnode));
		p->data=a[i];
		p->next=NULL;
		r->next=p;
		r=p;
		i++;
	}
}


void PRINTLSIT(listnode *hd)
{
	listnode *p=hd->next;
	while(p!=NULL)
	{
		printf("%c",p->data);
		p=p->next;
	}
	printf("\n");
}


void FREELIST(listnode *hd)
{
	while(hd->next!=NULL)
	{
		listnode *p=hd->next;
		hd->next=p->next;
		free(p);
	}
	free(hd);
}


void fun(listnode *hd,listnode *hdb,listnode *hdc)
{
	listnode *p=hd,*rb=hdb,*rc=hdc,*q=NULL;
	while(p->next!=NULL)
	{
		if(p->next->data>='A'&&p->next->data<='Z')
		{
			q=p->next;
			p->next=q->next;
			q->next=NULL;
			rb->next=q;
			rb=rb->next;
		}
		if(p->next->data>='a'&&p->next->data<='z')
		{
			q=p->next;
			p->next=q->next;
			q->next=NULL;
			rc->next=q;
			rc=rc->next;
		}
		if(p->next->data>='0'&&p->next->data<='9')
		{
			p=p->next;
		}
	}
}


int main()
{
	listnode *hd=NULL,*hdb=NULL,*hdc=NULL;
	hd=INITLIST();
	hdb=INITLIST();
	hdc=INITLIST();
	CREALISTWCSZ(hd,"hdfjjJDDALKD846115");
	PRINTLSIT(hd);
	fun(hd,hdb,hdc);
	PRINTLSIT(hd);
	PRINTLSIT(hdb);
	PRINTLSIT(hdc);
	FREELIST(hd);
	FREELIST(hdb);
	FREELIST(hdc);
	return 0;
	
}
