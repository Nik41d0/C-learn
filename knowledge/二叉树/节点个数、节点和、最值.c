#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct bitnode
{
	int data;
	struct bitnode *lchild,*rchild;
}bitnode;
int a[17]={14,5,26,0,0,8,0,0},a_i=0;


void create_sz(bitnode **T)
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


void blx(bitnode *t)
{
	if(t)
	{
		printf("%d ",t->data);
		blx(t->lchild);
		blx(t->rchild);
	}
}


void freetree(bitnode *t)
{
	if(t!=NULL)
	{
		freetree(t->lchild);
		freetree(t->rchild);
		free(t);
	}
}


int qgs(bitnode *t)
{
	int x,l,r;
	if(t!=NULL)
	{
		l=qgs(t->lchild);
		r=qgs(t->rchild);
		x=l+r+1;
	}
	else
		x=0;
	return x;
}
int num=0;
void qgs1(bitnode *t)
{
	if(t!=NULL)
	{
		num++;
		qgs1(t->lchild);
		qgs1(t->rchild);
	}
}
void qgs2(bitnode *t,int *p)
{
	if(t!=NULL)
	{
		(*p)++;
		qgs2(t->lchild,p);
		qgs2(t->rchild,p);
	}
}


int qh(bitnode *t)
{
	int x,l,r;
	if(t!=NULL)
	{
		l=qh(t->lchild);
		r=qh(t->rchild);
		x=l+r+t->data;
	}
	else
		x=0;
	return x;
}
int he=0;
void qh1(bitnode *t)
{
	if(t!=NULL)
	{
		he+=t->data;
		qh1(t->lchild);
		qh1(t->rchild);
	}
}
void qh2(bitnode *t,int *p)
{
	if(t!=NULL)
	{
		(*p)+=t->data;
		qh2(t->lchild,p);
		qh2(t->rchild,p);
	}
}


int max,min;
void qmaxmin(bitnode *t)
{
	if(t!=NULL)
	{
		if(t->data>max)
			max=t->data;
		else if(t->data<min)
			min=t->data;
		qmaxmin(t->lchild);
		qmaxmin(t->rchild);
	}
}


int main()
{
	int gs=0,s=0;
	bitnode *t=NULL;
	create_sz(&t);
	printf("先序遍历:");
	blx(t);
	printf("\n");
	printf("%d\n",qgs(t));
	qgs1(t);
	printf("%d\n",num);
	qgs2(t,&gs);
	printf("%d\n",gs);
	printf("%d\n",qh(t));
	qh1(t);
	printf("%d\n",he);
	qh2(t,&s);
	printf("%d\n",s);
	if(t!=NULL)
	{
		max=t->data;
		min=t->data;
		qmaxmin(t);
		printf("最大值:%d\n最小值:%d\n",max,min);
	}
	else
		printf("树为空!\n");
	freetree(t);
	return 0;
}
