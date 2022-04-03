#include<stdio.h>
#include<stdlib.h>

typedef struct bitnode
{
	int data;
	struct bitnode *lchild,*rchild;
}bitnode;
int a[17]={14,55,26,0,1,10,0,0},a_i=0;


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


int qgd(bitnode *t)
{
	int x,l,r;
	if(t!=NULL)
	{
		l=qgd(t->lchild);
		r=qgd(t->rchild);
		if(l>r) x=l+1;
		else x=r+1;
	}
	else
		x=0;
	return x;
}


void copy(bitnode **T,bitnode **S)
{
	if((*T)!=NULL)
	{
		(*S)=(bitnode *)malloc(sizeof(bitnode));
		(*S)->data=(*T)->data;
		copy(&(*T)->lchild,&(*S)->lchild);
		copy(&(*T)->rchild,&(*S)->rchild);
	}
	else
		(*S)=NULL;
}


int qcs(bitnode *t,int n,int cc)
{
	if(t!=NULL)
	{
		if(t->data==n) return cc;
		else
		{
			int c1,c2;
			c1=qcs(t->lchild,n,cc+1);
			c2=qcs(t->rchild,n,cc+1);
			if(c1!=0) return c1;
			else if(c2!=0) return c2;
			else return 0;
		}
	}
	else
		return 0;
}


int main()
{
	int n;
	bitnode *t=NULL,*f=NULL;
	create_sz(&t);
	copy(&t,&f);
	printf("先序遍历为:\n");
	blx(t);
	printf("\n");
	blx(f);
	printf("\n高度:%d\n",qgd(t));
	printf("请输入要查的数:");
	scanf("%d",&n);
	printf("层次:%d\n",qcs(t,n,1));
	freetree(t);
	freetree(f);
	return 0;
}
