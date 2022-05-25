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


void InsertBST(BSTNode **bst,int k) // 插入结点k
{
	if(bst==NULL)   // 若原树为空
	{
		*bst=(BSTNode *)malloc(sizeof(BSTNode));
		(*bst)->data=k;
		(*bst)->lchild=NULL;
		(*bst)->rchild=NULL;
	}
	else    // 若数不空
	{
		BSTNode *p=*bst,*pre=NULL;
		while(p)    // 循环找插入结点位置
		{
			pre=p;  // 记录父亲结点
			if(k<p->data)
				p=p->lchild;
			else if(k>p->data)
				p=p->rchild;
			else    // 若找到相等元素
				break;
		}
		if(!p)  // 若没找到相同结点，找到插入位置
		{
			p=(BSTNode *)malloc(sizeof(BSTNode));
			p->data=k;
			p->lchild=NULL;
			p->rchild=NULL;
			if(k<pre->data)
				pre->lchild=p;
			else
				pre->rchild=p;
		}
	}
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


BSTNode *SearchBST(BSTNode *bst,int key)    // 查找指定值
{
	BSTNode *p=bst;
	while(p)
	{
		if(key==p->data)
			return p;   // 找到定值结点，返回结点指针
		else if(key<p->data)
			p=p->lchild;
		else
			p=p->rchild;
	}
	return NULL;    // 查找失败
}


void DeleteBST(BSTNode **bst,int key)   // 删除指定结点
{
	BSTNode *p=*bst,*pre=*bst,*s=NULL,*spre=NULL;
	while(p)    // 循环找值为key的结点
	{
		if(key==p->data)    // 找到结点值为key的结点
			break;  // 提前跳出，p为找到结点的地址
		else if(key<p->data)
		{
			pre=p;  // pre一直指向p的父亲结点
			p=p->lchild;
		}
		else
		{
			pre=p;
			p=p->rchild;
		}
	}
	if(p)	// 若找到key结点
	{
		if(p->lchild==NULL&&p->rchild==NULL)    // 如果是叶子结点
		{
			if(p==*bst) // 若只有一个结点
				*bst=NULL;
			else if(p==pre->lchild)
				pre->lchild=NULL;
			else if(p==pre->rchild)
				pre->rchild=NULL;
		}
		else if(p->lchild!=NULL&&p->rchild==NULL)   // 若p结点右子树空而左子树存在
		{
			if(p==*bst) // 若只有一个结点
				*bst=p->lchild;
			else if(p==pre->lchild) // 若p不是根结点，且是父节点的左子树
				pre->lchild=p->lchild;
			else if(p==pre->rchild) // 若p不是根结点，且是父亲结点的右子树
				pre->rchild=p->lchild;
		}
		else if((p->lchild==NULL)&&(p->rchild!=NULL))	// 若p结点左子树空而左子树存在
		{
			if(p==*bst)
				*bst=p->rchild;
			else if(p==pre->lchild)
				pre->lchild=p->rchild;
			else if(p==pre->rchild)
				pre->rchild=p->rchild;
		}
		else    // 若p结点左右子树都不空
		{
			s=p->lchild;    // s指向p的左孩子结点
			if(s->rchild==NULL) // 若s没有右子树
			{
				if(p==*bst)
					*bst=s;
				else if(p==pre->lchild)
					pre->lchild=s;
				else if(p==pre->rchild)
					pre->rchild=s;
				s->rchild=p->rchild;
			}
			else    // 若s有右子树，找左子树最大值(最右边)替代
			{
				while(s->rchild)    // 循环使s指向左子树最大结点，s为spr右子树
				{
					spre=s;
					s=s->rchild;
				}// 右子树最右
				spre->rchild=s->lchild; // 摘除s结点
				if(p==*bst) // 若p为根结点
					*bst=s;
				else if(p==pre->lchild)
					pre->lchild=s;
				else if(p==pre->rchild)
					pre->rchild=s;
				s->lchild=p->lchild;    // s替代p位置
				s->rchild=p->rchild;
			}
		}
		free(p);
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


int main()
{
	int a[12]={5,2,7,6,9,12,1,3,4,8,10,11}; // RR-非根
	BSTNode *bst=NULL,*p=NULL;
	bst=CreateBST(a,12);
	InOrder(bst);
	printf("\n");

	InsertBST(&bst,16);
	InOrder(bst);
	printf("\n");

	p=SearchBST(bst,16);
	if(p)
		printf("\n找到了:%d\n",p->data);
	else
		printf("\n没找到!\n");

	DeleteBST(&bst,5);
	InOrder(bst);

	qasl(bst,1);
	printf("\n平均比较次数为:%d/%d",zbjcs,jdgs);
	FreeBST(bst);
	return 0;
}
