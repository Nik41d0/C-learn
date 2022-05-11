#include<stdio.h>
#include<stdlib.h>


typedef struct bitnode
{
	int data;
	struct bitnode *lchild,*rchild;
}bitnode;

int n;
int a[17]={1,2,3,0,0,7,0,0,8,0,0},a_i=0;
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
	if(t&&n>=1)
	{
		printf("%d ",t->data);
		n--;
		blx(t->lchild);
		blx(t->rchild);
	}
}
void blz(bitnode *t)
{
	if(t)
	{
		blz(t->lchild);
		if(n>=1)
		{
			printf("%d ",t->data);
			n--;
		}
		blz(t->rchild);
	}
}
void blh(bitnode *t)
{
	if(t)
	{
		blh(t->lchild);
		blh(t->rchild);
		if(n>=1)
		{
			printf("%d ",t->data);
			n--;
		}
		
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


void swap(bitnode *t)
{
	if(t)
	{
		bitnode *temp=t->lchild;
		t->lchild=t->rchild;
		t->rchild=temp;
		swap(t->lchild);
		swap(t->rchild);
	}
}


int main()
{
	bitnode *t=NULL;
	create_sz(&t);
	printf("先序遍历:");
	n=3;
	blx(t);
	printf("\n");
	printf("中序遍历:");
	n=3;
	blz(t);
	printf("\n");
	printf("后序遍历:");
	n=3;
	blh(t);
	printf("\n");
	printf("交换后:\n");
	swap(t);
	printf("先序遍历:");
	n=5;
	blx(t);
	printf("\n");
	printf("中序遍历:");
	n=5;
	blz(t);
	printf("\n");
	printf("后序遍历:");
	n=5;
	blh(t);
	freetree(t);
	return 0;
}
