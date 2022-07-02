#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 999999

typedef struct node
{
	char c;   // 字符
	int qz;   // 权值
	char bm[20];    // 编码
	struct node *lchild,*rchild,*next,*nt;
  // 哈夫曼树左右孩子指针，nt 为叶子链表下一节点指针，next 哈夫曼树创建过程中合并链表下一节点指针
}hnode;

hnode *Initialization();	// 初始化二叉树
void Create(hnode *hd);		// 创建哈夫曼树
void Encode(hnode *hd,char cc[20],int t); // 哈夫曼编码
void Decode(hnode *hd);		// 哈夫曼解码	
void Write_File(hnode *p);  // 将编码写入文件CodeFile
void CodePrin(char b[]);	// 将编码写入文件CodePrin，每行50个代码
void Print(hnode *p);		// 将上述代码于终端显示
void print_hnode(hnode *p); // 打印哈夫曼树的字符、权值和编码
void bin_save();			// 以二进制形式保存哈夫曼编码
void FreeTree(hnode *t);    // 释放二叉树节点空间
void Menu_List(int *m);     // 菜单列表

hnode *Initialization()	
{	
	char a[MAX];
	FILE *fp=fopen("1.txt","r");
	if(fp==NULL)
	{
		printf("打开文件失败!请确认是否存在名为1.txt的文件");
		exit(1);
	}
	fgets(a,MAX+1,fp);
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
	fclose(fp);
	printf("已从文件中读取\n");
	return hd;
}

int flag1=0;
void Create(hnode *hd)
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
	flag1=1;
}

void Encode(hnode *hd,char cc[20],int t)
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
		Encode(hd->lchild,hd->bm,0);
		Encode(hd->rchild,hd->bm,1);
	}
}

void Decode(hnode *hd)
{
	system("cls");
	char b[MAX];
	hnode *p=hd;
	FILE *fp=fopen("CodeFile","r");
	if(fp==NULL)
	{
		printf("打开文件失败!");
		return ;
	}
	fgets(b,MAX+1,fp);
	printf("已读取文件CodeFile中的哈夫曼编码\n");
	fclose(fp);
	hd=p;
	printf("哈夫曼编码为:%s\n",b);
	printf("译码为:");
	while(hd)
	{
		printf("%c",hd->c);
		hd=hd->nt;
	}	
	printf("\n");
	system("pause");
}

void Write_File(hnode *p)
{
	char option;
	FILE *fp=fopen("CodeFile","r");
	if(fp==NULL)
	{
		fclose(fp);
		printf("此文件不存在,是否创建?(Y or N)");
		getchar();
		scanf("%c",&option);
		if(option=='n'||option=='N')
		{
			printf("写入文件失败\n");
			return ;
		}
		else if(option=='y'||option=='Y')
		{
			fp=fopen("CodeFile","w");
			printf("文件创建成功!\n");
			while(p!=NULL)
			{
				fputs(p->bm,fp);
				p=p->nt;	
			}
			fclose(fp);
		}
		else
		{
			printf("没有这个选项呦(笑)\n");
			return ;
		}
	}
	else
	{
		fclose(fp);	
		getchar();
		printf("文件已存在,是否将其覆盖(Y or N)?");
		scanf("%c",&option);
		if(option=='n'||option=='N')
		{
			printf("覆盖文件失败!\n");
			return ;
		}
		else if(option=='y'||option=='Y')
		{
			fp=fopen("CodeFile","w");
			while(p!=NULL)
			{
				fputs(p->bm,fp);
				p=p->nt;	
			}
			fclose(fp);
			printf("文件覆盖成功!\n");
		}
		else
		{
			printf("没有这个选项呦(笑)\n");
			return ;
		}
	}
}

void CodePrin(char b[])
{	
	char option;
	FILE *fp;
	int i=1;
	getchar();
	printf("是否将以上代码保存至文件CodePrin中?(Y or N)");
	scanf("%c",&option);
	if(option=='n'||option=='N')
	{
		printf("保存文件失败!\n");
		return ;
	}
	else if(option=='Y'||option=='y')
	{
		fp=fopen("CodePrin","w");
		if(fp==NULL)
		{
			printf("文件打开失败!");
			return ;
		}
		else
		{
			while(b[i-1]!='\0')
			{
				fputc(b[i-1],fp);
				if(i%50==0)
					fprintf(fp,"\n");
				i++;
			}
			printf("保存成功!\n");
		}	
		fclose(fp);
	}
	else 
	{
		printf("没有这个选项呦(笑)\n");
		return ;
	}
}

void print_hnode(hnode *p)
{
	printf("%-8s%-8s%-8s\n" ,"字符","权值" , "编码");
	while(p!=NULL)
	{
		printf("%-8c%-8d%-8s\n",p->c,p->qz,p->bm);
		p=p->nt;	
	}
}

int flag2=0;
void Print(hnode *p)
{
	char b[1000];
	int i=1;
	if(strlen(p->bm)==0)
	{
		printf("请先进行哈夫曼编码!\n");
		return ;
	}
	else
	{
		while(p!=NULL&&flag2==0)
		{
			strcat(b,p->bm);
			p=p->nt;		
		}
		flag2=1;	
		while(b[i-1]!='\0')
		{
			printf("%c",b[i-1]);
			if(i%50==0)
				printf("\n");
			i++;
		}
		printf("\n");
		CodePrin(b);	
	}
}

void bin_save()
{
	int i=0;
	char b[MAX];
	FILE *fp_out=fopen("CodeFile","r");
	FILE *fp_bin=fopen("binout","wb");
	if(fp_out==NULL||fp_bin==NULL)
	{
		printf("文件打开失败!\n");
		return ;
	}
	fgets(b,MAX+1,fp_out);
	i=fread(b,sizeof(char),1,fp_bin);
	while(b[i]!='\0')
	{
		fwrite(&b[i],sizeof(char),1,fp_bin);
		i++;
	}
	printf("以二进制形式写入文件成功!\n");
	fclose(fp_bin);
	fclose(fp_out);
}

void FreeTree(hnode *t)   // 释放二叉树节点空间
{
	if(t!=NULL)
	{
		FreeTree(t->lchild);
		FreeTree(t->rchild);
		free(t);
	}
}

void Menu_List(int *m)
{
	printf("\t\t_______________________________________\n");	
	printf("\t\t|         哈夫曼哈夫曼编/译码器       |\n");
	printf("\t\t|*************************************|\n");	
	printf("\t\t|-------------------------------------|\n");
	printf("\t\t|       初始化二叉树请按1             |\n");
	printf("\t\t|-------------------------------------|\n");
	printf("\t\t|   	  编码哈夫曼树请按2              |\n");
	printf("\t\t|-------------------------------------|\n");
	printf("\t\t|   	  打印代码文件请按3             |\n");
	printf("\t\t|-------------------------------------|\n");
	printf("\t\t|   	  译码请按4(半成                |\n");
	printf("\t\t|-------------------------------------|\n");
	printf("\t\t|   	  二进制保存CodeFile请按5       |\n");
	printf("\t\t|-------------------------------------|\n");	
	printf("\t\t|   	  退出请按0                     |\n");
	printf("\t\t|-------------------------------------|\n");
	printf("\t\t|*************************************|\n\n");		
	printf("请输入:");
	scanf("%d",m);
	if(*m<0||*m>=6)
	{
		printf("无该选项,请重试!\n\n");
		return ;
	}
}


int main()
{	
	int m; 
	hnode *head,*p,*hd=(hnode *)malloc(sizeof(hnode));
	while(1)
	{
		Menu_List(&m);
		switch(m)
		{
			case 1:	
				head=Initialization();
				hd->nt=head->nt;
				p=hd->nt;
				break;	
			case 2:
				if(p==NULL)
				{
					printf("二叉树为空,请重试!\n");
					break;
				}
				else
				{
					if(flag1==0)
					{
						Create(head);
						Encode(head->next,head->bm,-1);
					}
					print_hnode(p);
					Write_File(p);					
				}	
				break;
			
			case 3:
				if(hd->nt==NULL)
				{
					printf("二叉树为空,请重试!\n");
					break;
				}
				else	
					Print(p);
				break;
			case 4:
				if(flag1==0)
				{
					printf("请先进行哈夫曼编码!\n");
					break;
				}
				Decode(hd->nt);
				break;
			case 5:
				bin_save();
				break;
			case 0:
				printf("已退出!");
				FreeTree(head->next);
				free(head);			
				free(hd);
				exit(1);	
		}
	}
    return 0;
}
