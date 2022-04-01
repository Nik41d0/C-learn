#include<stdio.h>
#include<stdlib.h>
typedef struct bitnode
{
	int data;
	struct bitnode *lchild,*rchild;
}bitnode,*bitree;
int a[]={1,2,4,5,0,0,0,6,7,0,0,0,3,8,0,0,9,0,0},a_i=0;
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
typedef struct
{
	bitree data[60];
	int bz[60];
	int top;
}stackh;
void pushh(stackh *st,bitree tp,int bz)
{
	if(st->top==60-1)
		printf("overflow");
	else
	{
		st->top++;
		st->data[st->top]=tp;
		st->bz[st->top]=bz;
	}
}
void poph(stackh *st,bitree *tp,int *bz)
{
	if(st->top==-1)
		printf("underflow");
	else
	{
		*tp=st->data[st->top];
		*bz=st->bz[st->top];
		st->top--;
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
void blhfd(bitree t)
{
	stackh s;
	int tag;
	s.top=-1;
	while((t!=NULL)||s.top!=-1)
	{
		if(t!=NULL)
		{
			tag=0;
			pushh(&s,t,tag);
			t=t->lchild;
		}
		else
		{
			poph(&s,&t,&tag);
			if(tag==0)
			{
				tag=1;
				pushh(&s,t,tag);
				t=t->rchild;
			}
			else
			{
				printf("%d ",t->data);
				t=NULL;
			}
		}
	}
}
void blh(bitree t)
{
	if(t)
	{
		blh(t->lchild);
		blh(t->rchild);
		printf("%d ",t->data);
	}
}
int main()
{
	bitnode *t=NULL;
	create_sz(&t);
	printf("非递归后序遍历:");
	blhfd(t);
	printf("\n");
	printf("递归后序遍 :");
	blh(t);
	printf("\n");
	
	freetree(t);
	return 0;
}
