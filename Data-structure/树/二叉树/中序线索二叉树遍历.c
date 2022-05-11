#include<stdio.h>
#include<stdlib.h>

typedef struct bithrnode
{
	int data;
	int ltag,rtag;
	struct bithrnode *lchild,*rchild;
}bithrnode,*bithree;

int a[20]={1,2,4,0,0,5,0,0,3,6,0,0,7,0,0},a_i=0;
void create(bithree *T)   // 左右孩子线索标志均设置为 0
{
	if(a[a_i]==0)
	{
		(*T)=NULL;
		a_i++;
	}
	else
	{
		(*T)=(bithrnode *)malloc(sizeof(bithrnode));
		(*T)->data=a[a_i];
		a_i++;
		(*T)->ltag=0;
		(*T)->rtag=0;
		create(&(*T)->lchild);
		create(&(*T)->rchild);
	}
}


bithree pre;  // 全局变量，只想最前一节点
void inthreading(bithree p) // 中序线索化
{
	if(p!=NULL)
	{
		inthreading(p->lchild); // 递归处理左子树
		if(p->lchild==NULL)
		{
			p->ltag=1;
			p->lchild=pre;
		}
		if(pre->rchild==NULL)
		{
			pre->rtag=1;
			pre->rchild=p;
		}
		pre=p;
		inthreading(p->rchild);
	}
}


void blzxs(bithree T) // 正序中序遍历二叉树
{
	bithree p=T->lchild;
	while(p!=T)
	{
		while(p->ltag==0)
			p=p->lchild;
		printf("%d ",p->data);
		while(p->rtag==1&&p->rchild!=T)
		{
			p=p->rchild;
			printf("%d ",p->data);
		}
		p=p->rchild;
	}
}

void blzxs_nx(bithree T)  // 逆序
{
	bithree p=T->rchild;
	while(p!=T)
	{
		printf("%d ",p->data);
		if(p->ltag==1)
			p=p->lchild;
		else
		{
			p=p->lchild;
			while(p->rtag==0)
				p=p->rchild;
  		}
	}
}

void blz(bithree t)
{
	if(t)
	{
		blz(t->lchild);
		printf("%d ",t->data);
		blz(t->rchild);
	}
}



int main()
{
	bithree t=NULL,s=NULL;
	create(&t);
	blz(t);
	printf("\n");
	s=(bithree)malloc(sizeof(bithrnode));   // 附加头节点
	s->ltag=0;
	s->rtag=1;
	s->rchild=s;
	if(t==NULL)
		s->lchild=s;
	else
	{
		s->lchild=t;      // 左孩子指向二叉树 t 的根
		pre=s;		//  pre 前一节点指向新创建的附加节点 s
		inthreading(t);   
		pre->rchild=s;      // t 树处理最后一节点的右子树指向附加节点
		pre->rtag=1;		
		s->rchild=pre;	   // 附加节点的右孩子指向最后处理节点
	}
	blzxs(s);
	printf("\n");
	blzxs_nx(s);
	return 0;
}
/*

pre=inthreading_loc(t,pre);    //局部变量添加线索
bithree inthreading_loc(bithree t,bithree pre)
{
	if(t)
	{
		pre=inthreading_loc(t->lchild,pre);
		if(t->lchild==NULL)
		{
			t->ltag=1;
			t->lchild=pre;
		}
		else
			t->ltag=0;
		if(pre!=NULL&&pre->rchild==NULL)
		{
			pre->rchild=t;
			pre->rtag=1;
		}
		else if(pre!=NULL)
			pre->rtag=0;
		pre=t;
		pre=inthreading_loc(t->rchild,pre);
	}
	return pre;
}

*/
