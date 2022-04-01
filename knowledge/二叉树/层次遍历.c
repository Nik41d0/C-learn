#include<stdio.h>
#include<stdlib.h>
#define MAX 40

typedef struct bitnode
{
	int data;
	struct bitnode *lchild,*rchild;
}bitnode,*bitree;   


int a[17]={1,2,3,0,0,7,0,0,8,0,0},a_i=0;
void create_sz(bitree *T)
{
	if(a[a_i]==0)
	{
		(*T)=NULL;
		a_i++;
	}
	else
	{
		(*T)=(bitnode *)malloc(sizeof(bitnode));
		(*T)->data=a[a_i];
		a_i++;
		create_sz(&(*T)->lchild);
		create_sz(&(*T)->rchild);
	}
}


void ccbl(bitree t)    //  bitree 相当于 *bitnode,下同
{
	bitnode *d1[MAX],*p=NULL;
	int f=0,r=0;
	if(t!=NULL)
	{
		d1[r]=t;
		r++;
	}
	while(f!=r)
	{
		p=d1[f];
		f++;
		printf("%d ",p->data);
		if(p->lchild!=NULL)
		{
			d1[r]=p->lchild;
			r++;
		}
		if(p->rchild!=NULL)
		{
			d1[r]=p->rchild;
			r++;
		}
	}
}


void freetree(bitree t)
{
	if(t!=NULL)
	{
		freetree(t->lchild);
		freetree(t->rchild);
		free(t);
	}
}


int main()
{
	bitnode *t=NULL;
	create_sz(&t);
	ccbl(t);
	printf("\n");
	freetree(t);
	return 0;
}
