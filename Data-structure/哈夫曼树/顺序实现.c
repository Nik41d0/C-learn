#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 999999
	
typedef struct node	// 定义哈夫曼树节点的结构
{
	char c;
	int qz;
	char bm[30];
	int lchild,rchild,bz;
	// bz 为 1 时表示在权值数列中，为 0 时则表示不在权数列中
	// lchild、rchild 存储节点左右孩子在数组中的下标
}snode;
typedef struct sz	// 定义数组存储的哈夫曼树
{
	snode *arr;	// 指向节点数组的指针
	int num_yz;	// 哈夫曼树叶子节点个数
}hfms;
typedef struct cnode	// 定义链表存储的节点
{
	char c;
	int qz;
	struct cnode *next;
}hcnode;	

void tjzf(char *a,hfms *s)	// 将字符串 a 添加到哈夫曼树节点数组
{
	int i=0;
	hcnode *hd=(hcnode *)malloc(sizeof(hcnode)),*p;
	hd->next=NULL;
	while(a[i]!='\0')	// 统计 a 中字符，创建链表存储字符并计算权值
	{
		p=hd->next;
		while(p!=NULL)
		{	
			// 当链表中存在存储字符 a[i] 的节点，则该节点的 qz+1
			if(p->c==a[i])
			{
				p->qz++;
				break;
			}
			p=p->next;
		}
		if(p==NULL)
		{	
			// 若 p 为空，即当前链表中无存储字符 a[i] 的节点
			// 则开辟一个空间 t ，将 a[i] 存入 t->c qz=1
			hcnode *t=(hcnode *)malloc(sizeof(hcnode));
			t->c=a[i];
			t->qz=1;
			t->next=hd->next; 	// 前插法将 t 插入链表
			hd->next=t;
		}
		i++;
	}
	i=0;
	p=hd->next;
	while(p!=NULL)	// 计算链表长度
	{
		i++;
		p=p->next;
	}
	s->num_yz=i;	// 哈夫曼树叶子节点数 = 链表长度
	s->arr=(snode *)malloc(sizeof(snode)*(s->num_yz*2-1));
	// 开辟空间，空间大小/节点个数为：2*n0-1
	p=hd->next;
	i=0;
	while(p!=NULL)
	{
		// 将链表中个节点的数据存入数组中
		s->arr[i].c=p->c;
		s->arr[i].qz=p->qz;
		strcpy(s->arr[i].bm,"");
		s->arr[i].lchild=-1;	
		s->arr[i].rchild=-1;
		s->arr[i].bz=1; 	// 权在数列中
		p=p->next;
		i++;
	}
	for(;i<s->num_yz*2-1;i++)	// 对剩余节点初始化
	{
		s->arr[i].c='\0';
		s->arr[i].qz=0;
		strcpy(s->arr[i].bm,"");
		s->arr[i].lchild=-1;
		s->arr[i].rchild=-1;
		s->arr[i].bz=0;		// 权不在数列中
	}
	p=hd->next;
	while(p!=NULL)
	{
		hd->next=p->next;
		free(p);
		p=hd->next;
	}
	free(hd);
}


void js(hfms s)		// 创建哈夫曼树
{
	int i,min1xb,min2xb,minxb,minz,k;
	for(k=s.num_yz;k<s.num_yz*2-1;k++)
	{
	// 对未存储字符的节点存入数据，权值越大，在数组中位置越靠后
		minxb=-1;
		minz=MAX;
		for(i=0;i<s.num_yz*2-1;i++)
			if(s.arr[i].bz==1&&s.arr[i].qz<minz)
			{
				minz=s.arr[i].qz;	// 将权数列中最小权值赋值 minz
				minxb=i;		// 将权数列中最小权值所属的下标赋值 minb
			}
		min1xb=minxb;
		s.arr[min1xb].bz=0;	// 将最小权值所属元素移除
		minxb=-1;
		minz=MAX;
		for(i=0;i<s.num_yz*2-1;i++)
			if(s.arr[i].bz==1&&s.arr[i].qz<minz)
			{
				minz=s.arr[i].qz;
				minxb=i;
			}
		min2xb=minxb;
		s.arr[min2xb].bz=0;
		s.arr[k].qz=s.arr[min1xb].qz+s.arr[min2xb].qz;
		s.arr[k].bz=1;		// 将该节点添加进权数列
		s.arr[k].lchild=min1xb;
		s.arr[k].rchild=min2xb;
	}
}


void bm(hfms s,int xb,char cc[30],int t)	// 先序遍历进行编码
{	
	if(t==0)	// 若该节点为父亲节点的左孩子
	{
		// 先将父亲节点 bm 赋给该节点 bm，后再该节点的 bm 后加 0
		strcat(s.arr[xb].bm,cc);
		strcat(s.arr[xb].bm,"0");
	}
	else if(t==1)		// 若该节点为父亲节点的右孩子
	{
		strcat(s.arr[xb].bm,cc);
		strcat(s.arr[xb].bm,"1");
	}
	if(s.arr[xb].lchild!=-1)	// 若左孩子存在，则传入编码 0
		bm(s,s.arr[xb].lchild,s.arr[xb].bm,0);
	if(s.arr[xb].rchild!=-1)	// 若右孩子存在，则传入编码 1
		bm(s,s.arr[xb].rchild,s.arr[xb].bm,1);
}


int main()
{
	int i;
	char a[200]="jdawlkjfajowiadjoawjfaoiwfjawiwafawf";
	hfms s;
	tjzf(a,&s);
	js(s);
	bm(s,s.num_yz*2-1-1,"",-1);
	for(i=0;i<=s.num_yz-1;i++)
		printf("%c:%d:%s\n",s.arr[i].c,s.arr[i].qz,s.arr[i].bm);
	free(s.arr);
    return 0;
}
