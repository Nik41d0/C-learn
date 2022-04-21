#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	char c;   // 字符
	int qz;   // 权值
	char bm[30];    // 编码
	struct node *lchild,*rchild,*next,*nt;
  // 哈夫曼树左右孩子指针，nt 为叶子链表下一节点指针，next 哈夫曼树创建过程中合并链表下一节点指针
}hnode;


hnode *tjzf(char *a)    // 统计字符
{
	hnode *hd=(hnode *)malloc(sizeof(hnode));
	int i=0;
	hd->next=NULL;
	hd->lchild=NULL;
	hd->rchild=NULL;
	hd->nt=NULL;
	while(a[i]!='\0')
	{
		hnode *p=hd->next;
		while(p!=NULL)
		{
			if(p->c==a[i])    // 若在叶子链表中找到字符
			{
				p->qz++;      // 权值+1
				break;
			}
			p=p->next;
		}
		if(p==NULL)     // 若没找到字符，叶子链表加一个新节点
		{
			hnode *t=(hnode *)malloc(sizeof(hnode));
			t->c=a[i];
			t->qz=1;      // 初始权值设为 1
			t->lchild=NULL;
			t->rchild=NULL;
			t->bm[0]='\0';
			t->next=hd->next;
			hd->next=t;
			t->nt=hd->nt;
			hd->nt=t;
		}
		i++;
	}
	return hd;
}


void select(hnode *hd)
{
	while(hd->next->next!=NULL)
	{
		hnode *m=hd,*p=m->next,*min1,*min2;
		while(p->next!=NULL)    // 找第一最小权值节点
		{
			if(p->next->qz<m->next->qz)     // p 和 m 一直指向比较节点的前一节点
				m=p;
			p=p->next;
		}       // 循环后，m 指向最小节点的前一节点
		min1=m->next;       // min1 指向第一最小节点
		m->next=min1->next;     // 将最小节点摘除（不是删除）
		m=hd;
		p=m->next;
		while(p->next!=NULL)    // 找第二最小权值节点
		{
			if(p->next->qz<m->next->qz)     
				m=p;
			p=p->next;
		}
		min2=m->next;
		m->next=min2->next;  // 将第二小节点摘除
    
		m=(hnode *)malloc(sizeof(hnode));
		m->qz=min1->qz+min2->qz;    // 两最小权值合成一个新节点
		m->lchild=min1;
		m->rchild=min2;
		m->next=hd->next;
		m->bm[0]='\0';
		hd->next=m;
	}
}


void blx(hnode *hd,char cc[30],int t)     // 编码
{
	if(hd!=NULL)
	{
		if(t==0)
		{
			strcat(hd->bm,cc);
			strcat(hd->bm,"0");     // 左子树添加 0
		}
		else if(t==1)
		{
			strcat(hd->bm,cc);
			strcat(hd->bm,"1");   // 右子树添加 1
		}
		blx(hd->lchild,hd->bm,0);
		blx(hd->rchild,hd->bm,1);
	}
}


void freetree(hnode *t)   // 释放二叉树节点空间
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
	char a[200]="jdawlkjfajowiadjoawjfaoiwfjawiwafawf";
	hnode *head,*p,*hd=(hnode *)malloc(sizeof(hnode));
	head=tjzf(a);
	hd->nt=head->nt;
	select(head);
	blx(head->next,head->bm,-1);
	p=hd->nt;
	while(p!=NULL)
	{
		printf("%c:%d:%s\n",p->c,p->qz,p->bm);    // 打印各叶子节点的 字符、权值、编码
		p=p->nt;
	}
	freetree(head->next);
	free(head);
	free(hd);
    return 0;
}
