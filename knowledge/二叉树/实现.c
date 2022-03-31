#include<stdio.h>
#include<stdlib.h>
typedef struct bitnode
{
	int data;
	struct bitnode *lchild,*rchild;
}bitnode;

void create(bitnode **T)
{
	int d;
	scanf("%d",&d);
	if(d==0) (*T)=NULL;
	else
	{
		(*T)=(bitnode *)malloc(sizeof(bitnode));
		(*T)->data=d;
		create(&(*T)->lchild);
		create(&(*T)->rchild);
	}
}
bitnode *create1()
{
	int d;
	bitnode *T;
	scanf("%d",&d);
	if(d==0) T=NULL;
	else
	{
		T=(bitnode *)malloc(sizeof(bitnode));
		T->data=d;
		T->lchild=create1();
		T->rchild=create1();
	}
	return T;
}
int a[17]={1,2,0,0,3,0,0},a_i=0;
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
void blz(bitnode *t)
{
	if(t)
	{
		blx(t->lchild);
		printf("%d ",t->data);
		blx(t->rchild);
	}
}
void blh(bitnode *t)
{
	if(t)
	{
		blx(t->lchild);
		blx(t->rchild);
		printf("%d ",t->data);
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


int main()
{
	bitnode *t=NULL;
	t=create1();
	//create(&t);
	//create_sz(&t);
	printf("先序遍历:");
	blx(t);
	printf("\n");
	printf("中序遍历:");
	blz(t);
	printf("\n");
	printf("后序遍历:");
	blh(t);
	
	freetree(t);
	return 0;
}
