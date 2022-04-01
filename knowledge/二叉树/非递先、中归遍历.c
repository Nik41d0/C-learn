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
	int top;
}stack;

void push(stack *st,bitree tp)
{
	if(st->top==60-1)
		printf("overflow");
	else
	{
		st->top++;
		st->data[st->top]=tp;
	}
}

bitree pop(stack *st)
{
	bitree p;
	if(st->top==-1)
	{
		printf("underflow");
		return 0;
	}
	else
	{
		p=st->data[st->top];
		st->top--;
		return p;
	}
}


void blxfd(bitree t)  //非递归先序
{
	stack s;
	s.top=-1;
	while((t!=NULL)||(s.top!=-1))
	{
		if(t!=NULL)
		{
			printf("%d ",t->data);
			push(&s,t);
			t=t->lchild;
		}
		else
		{
			t=pop(&s);
			t=t->rchild;
		}
	}
}
void blx(bitnode *t)     //递归先序
{
	if(t)
	{
		printf("%d ",t->data);
		blx(t->lchild);
		blx(t->rchild);
	}
}


void blzfd(bitree t)   // 非递归中序
{
	stack s;
	s.top=-1;
	while((t!=NULL)||(s.top!=-1))
	{
		if(t!=NULL)
		{
			push(&s,t);
			t=t->lchild;
		}
		else
		{
			t=pop(&s);
			printf("%d ",t->data);
			t=t->rchild;
		}
	}
}
void blz(bitnode *t)  //  递归中序
{
	if(t)
	{
		blz(t->lchild);
		printf("%d ",t->data);
		blz(t->rchild);
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
	printf("非递归先序遍历:");
	blxfd(t);
	printf("\n");
	printf("递归先序遍历:");
	blx(t);
	printf("\n");
	
	printf("非递归中序遍历:");
	blzfd(t);
	printf("\n");
	printf("递归中序遍历:");
	blz(t);
	printf("\n");
	freetree(t);
	return 0;
}
