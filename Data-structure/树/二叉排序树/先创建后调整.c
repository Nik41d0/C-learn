#include<stdio.h>
#include<stdlib.h>

typedef struct BSTNode  // 数据结点定义
{
	int data;
	struct BSTNode *lchild,*rchild;
}BSTNode;


struct BSTNode *CreateBST(int a[],int n)    // 根据数组a创建二叉排序树
{
	int i;
	BSTNode *root=(BSTNode *)malloc(sizeof(BSTNode)),*p=NULL,*pre=NULL;
	root->data=a[0];
	root->lchild=NULL;
	root->rchild=NULL;
	for(i=1;i<=n-1;i++)
	{
		p=root;
		while(p)
		{
			pre=p;  // 一直指向p的父亲结点
			if(a[i]<p->data)
				p=p->lchild;
			else if(a[i]>p->data)
				p=p->rchild;
			else
				break;  // 找的相等的break跳出、提前结束
		}
		if(!p)  // 若p等于空，没找到相等结点
		{
			p=(BSTNode *)malloc(sizeof(BSTNode));
			p->data=a[i];
			p->lchild=NULL;
			p->rchild=NULL;
			// 通过pre把p插入pre的左孩子或右孩子的位置
			if(a[i]<pre->data)
				pre->lchild=p;
			else
				pre->rchild=p;
		}
	}
	return root;
}


void InOrder(BSTNode *root) // 中序遍历
{
	if(root!=NULL)
	{
		InOrder(root->lchild);
		printf(" %d ",root->data);
		InOrder(root->rchild);
	}
}
void Fiorder(BSTNode *root) // 先序遍历
{
	if(root!=NULL)
	{
		printf(" %d ",root->data);
		Fiorder(root->lchild);
		Fiorder(root->rchild);
	}
}


void FreeBST(BSTNode *root) // 释放二叉排序树空间
{
	if(root!=NULL)
	{
		FreeBST(root->lchild);
		FreeBST(root->rchild);
		free(root);
	}
}
BSTNode *fat=NULL;
int bz=0;
BSTNode *IfBalance(BSTNode *root,int *h,int *hc)
{
	if(bz==1)
		return NULL;
	if(root!=NULL)
	{
		int lh,rh,lnhc,rnhc;
		BSTNode *phfl=IfBalance(root->lchild,&lh,&lnhc);
		BSTNode *phfr=IfBalance(root->rchild,&rh,&rnhc);
		*h=lh>rh?lh+1:rh+1;
		*hc=lh-rh;
		if(phfl)
		{
			if(bz==0)
			{
				fat=root;
				bz=1;
			}
			*hc=lnhc;
			return phfl;
		}
		else if(phfr)
		{
			if(bz==0)
			{
				fat=root;
				bz=1;
			}
			*hc=rnhc;
			return phfr;
		}
		else
		{
			if(*hc>=-1&&*hc<=1)
				return NULL;
			else
				return root;
		}
	}
	else
	{
		*h=0;
		*hc=0;
		return NULL;
	}
}
int qgd(BSTNode *t)
{
	if(t)
	{
		int k,r;
		k=qgd(t->lchild);
		r=qgd(t->rchild);
		if(k>r)
			return k+1;
		else
			return r+1;
	}
	else
		return 0;
}


void Bbt_Adjust(BSTNode **bst,BSTNode *pa,int hc)
{
	BSTNode *pb=NULL,*pc=NULL;
	if(hc==2)
	{
		pb=pa->lchild;
		if(qgd(pb->lchild)-qgd(pb->rchild)==-1)
		{
			pc=pb->rchild;
			pa->lchild=pc->rchild;
			pb->rchild=pc->lchild;
			pc->lchild=pb;
			pc->rchild=pa;
			if(pa==*bst)
				*bst=pc;
			else
			{
				if(fat->lchild==pa)
					fat->lchild=pc;
				else
					fat->rchild=pc;
			}
		}
		else
		{
			pa->lchild=pb->rchild;
			pb->rchild=pa;
			if(pa==*bst)
				*bst=pb;
			else
			{
				if(fat->lchild==pa)
					fat->lchild=pb;
				else
					fat->rchild=pb;
			}
		}
	}
	else if(hc==-2)
	{
		pb=pa->rchild;
		if(qgd(pb->lchild)-qgd(pb->rchild)==1)
		{
			pc=pb->lchild;
			pa->rchild=pc->lchild;
			pb->lchild=pc->rchild;
			pc->lchild=pa;
			pc->rchild=pb;
			if(pa==*bst)
				*bst=pc;
			else
			{
				if(fat->lchild==pa)
					fat->lchild=pc;
				else
					fat->rchild=pc;
			}
		}
		else
		{
			pa->rchild=pb->lchild;
			pb->lchild=pa;
			if(pa==*bst)
				*bst=pb;
			else
			{
				if(fat->lchild==pa)
					fat->lchild=pb;
				else
					fat->rchild=pb;
			}
		}
	}
}


int jdgs=0,zbjcs=0; // 结点个数，总比较次数
void qasl(BSTNode *t,int jdcs)  // jdcs-结点所在层
{
	if(t)
	{
		jdgs++; // 累计结点个数
		zbjcs+=jdcs;    // 总比较次数
		qasl(t->lchild,jdcs+1);
		qasl(t->rchild,jdcs+1);
	}
}

int gy(int a,int b)
{
	int i;
	for(i=a<b?a:b;i>=1;i--)
		if(a%i==0&&b%i==0)
			return i;
	return 1;
}

int main()
{
	int a[12]={5,2,7,6,9,12,1,3,4,8,10,11},h,hc; // RR-非根
	BSTNode *bst=NULL,*p=NULL;
	int ys=1;
	bst=CreateBST(a,12);
	InOrder(bst);
	printf("\n");
	Fiorder(bst);
	printf("\n");
	qasl(bst,1);
	ys=gy(zbjcs,jdgs);
	printf("\n平均比较次数为:%d/%d\n",zbjcs/ys,jdgs/ys);
	
	bz=0;
	p=IfBalance(bst,&h,&hc);
	while(p)
	{
		Bbt_Adjust(&bst,p,hc);
		bz=0;
		p=IfBalance(bst,&h,&hc);
	}
	InOrder(bst);
	printf("\n");
	Fiorder(bst);
	printf("\n");
	zbjcs=0,jdgs=0;
	qasl(bst,1);
	ys=gy(zbjcs,jdgs);
	printf("\n平均比较次数为:%d/%d",zbjcs/ys,jdgs/ys);

	FreeBST(bst);
	
	return 0;
}
