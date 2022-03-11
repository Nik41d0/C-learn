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
	hd->next=NULL;
	return hd;
}


void CREALIST(LinkList *hd)
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
void CREALIST1(LinkList *hd)
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


int Lenght(LinkList *hd)
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


int locatelem(LinkList *hd,int e)
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


void Qbingji(LinkList *la,LinkList *lb)
{
	LinkList *pb=lb->next,*pa=NULL;
	while(pb!=NULL)
	{
		lb->next=pb->next;
		pa=la->next;
		while(pa!=NULL)
		{
			if(pb->data==pa->data) break;
			pa=pa->next;
		}
		if(pa==NULL)
		{
			pb->next=la->next;
			la->next=pb;
		}
		else
			free(pb);
		pb=lb->next;
		
	}
}
void Qbingji1(LinkList *la,LinkList *lb)
{
	int length_a=Lenght(la),length_b=Lenght(lb),i,e;
	for(i=1;i<=length_b;i++)
	{
		Getelem(lb,i,&e);
		if(locatelem(la,e)==0)
			insertelem(la,++length_a,e);
	}
}


int main()
{
	int i;
	LinkList *hd1=NULL,*hd2=NULL;
	hd1=INITLIST();
	hd2=INITLIST();
	for(i=1;i<=25;i++)
		insertelem(hd1,i,i);
	PRINTLIST(hd1);
	for(i=1;i<=13;i++)
		insertelem(hd2,i,i*i);
	PRINTLIST(hd2);
	Qbingji1(hd1,hd2);
	PRINTLIST(hd1);
	return 0;
}
