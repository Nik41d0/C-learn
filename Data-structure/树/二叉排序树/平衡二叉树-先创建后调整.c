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
BSTNode *IfBalance(BSTNode *root,int *h,int *hc)	// 判断是否为平衡二叉树，若不平衡返回最小不平衡的根，h-高度，hc-平衡因子
{
	if(bz==1)   // 若找到最小不平衡子树，则直接返回
		return NULL;
	if(root!=NULL)  // 若传入子树根root不空
	{
		int lh,rh,lnhc,rnhc;    // lh-左子树高度，rh-右子树高度，lnhc-左子树平衡因子，rnhc-右子树平衡因子
		BSTNode *phfl=IfBalance(root->lchild,&lh,&lnhc);
		BSTNode *phfr=IfBalance(root->rchild,&rh,&rnhc);
		// 先处理左右子树，相当于后序遍历
		*h=lh>rh?lh+1:rh+1; // 当前树高度，用于返回上一层调用函数
		*hc=lh-rh;
		if(phfl)    // 若左子树phfl不平衡
		{
			if(bz==0)   // 若没找到最小不平衡子树
			{
				fat=root;   // 保存最小不平衡子树(根)的父亲结点
				bz=1;   // 标记找到最小不平衡子树
			}
			*hc=lnhc;   // 向上返回最小子树的平衡因子
			return phfl;    // 向上返回最小子树(根)的指针
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


void Bbt_Adjust(BSTNode **bst,BSTNode *pa,int hc)	// 平衡二叉树调整，bst-整个树的根，pa-最小不平衡子树的根，hc-不平衡因子
{
	BSTNode *pb=NULL,*pc=NULL;
	if(hc==2)   // LL型或LR型
	{
		pb=pa->lchild;
		if(qgd(pb->lchild)-qgd(pb->rchild)==-1) // LR型
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
		else    // LL型
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
	else if(hc==-2) // RR型或RL型
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
	//int a[12]={7,6,9,8,12,10}; //RR-根
	int a[12]={5,2,7,6,9,12,1,3,4,8,10,11},h,hc; // RR-非根
	//int a[12]={7,6,19,11,22,12},h,hc; // RL-根
	//int a[12]={5,3,2,4,1,7,6,19,11,12,22},h,hc;   // RL-非根
	//int a[12]={27,19,11,22,12,32},h,hc;   // LL-根
	//int a[12]={50,60,27,19,11,22,12,32},h,hc; // LL-非根
	//int a[12]={27,19,11,22,32,23},h,hc;   // LR-根
	//int a[12]={50,60,27,19,11,22,32,23},h,hc; LR-非根
	int ys=1;
	BSTNode *bst=NULL,*p=NULL;
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
