#include<stdio.h>
#include<string.h>
void scan();
void search();
void print();
void aver80();
void put();
void xiugai();
struct stu 
{
	char  num[20];
	char nam[20];
	int s[4];
	float aver;
} w[200];
int i,n,m;
int menu() 
{
	printf("\t学生基本信息录入请按1\n");
	printf("\t学生基本信息输出请按2\n");
	printf("\t按学号查询学生信息请按3\n");
	printf("\t输出平均分大于80的同学信息请按4\n");
	printf("\t按学号修改某学生信息请按5\n");
	printf("\t学生成绩保存请按6\n");
	printf("\t退出请按0\n");    
	printf("请输入:");
	scanf("%d", &m);
	return m;
}
int main() 
{
	int m;
	while (1) 
	{
		m = menu();
		switch (m)
		{
			case 0:
				return 0;
			case 1:
				scan();
				break;
			case 2:
				print();
				break;
			case 3:
				search();
				break;
			case 4:
				aver80();
				break;
			case 5:
				xiugai();
				break;
			case 6:
                put();			
				break;
		}
	}
	return 0;
}
void scan() 
{
	printf("请输入共有几名学生:");
	scanf("%d", &n);
	for (i = 0; i < n; i++) 
	{
		printf("请输入第%d位学生的基本信息", i + 1);
		printf("(学号、姓名和三门成绩之间以空格间隔即可):");
		scanf("%s %s", w[i].num,w[i].nam);
		scanf(" %d %d %d",&w[i].s[0],&w[i].s[1],&w[i].s[2]);
	}
}
void print() 
{
	printf("%-15s%-12s", "学生学号", "学生姓名");
	printf("%-8s%-8s%-8s%-8s", "高数", "计算机", "英语", "总分");
	printf("%-8s\n","平均分");
	for (i = 0; i < n; i++)
	{
		w[i].s[3] = w[i].s[0] + w[i].s[1] + w[i].s[2];
		w[i].aver =  w[i].s[3] / 3.0;
		printf("%-15s%-12s%-8d%-8d",w[i].num,w[i].nam,w[i].s[0],w[i].s[1]);
		printf("%-8d%-8d%-8.2f\n",w[i].s[2],w[i].s[3],w[i].aver);
	}
	printf("\n");
}
void put()
{
	char a,c[20];
	int j;
	FILE *fp;
	print();
	getchar();
	printf("是否要将此数据存到文件中?(y or n)\n");
	scanf("%c",&a);
	if(a=='y'||a=='Y')
		{
			printf("请输入要保存数据的文件名:");
			scanf("%s",c);
			fp=fopen(c,"w");
			if(fp!=NULL)
				{for(i=0;i<n;i++)
					{
						fprintf(fp,"%s ",w[i].num);
						fprintf(fp,"%s ",w[i].nam);
						for(j=0;j<4;j++)
						fprintf(fp,"%d ",w[i].s[j]);
						fprintf(fp,"%0.2f   ",w[i].aver);
					}	
				
				printf("保存成功\n");
				}
			else 
				printf("文件保存失败!\n");
			fclose(fp);	
		}
	if(a=='N'||a=='n')
		return ;
}
void search() 
{
	int f=0;
	char b[20];
	printf("请输入要查找学生的学号:");
	scanf("%s", b);
	for (i = 0; i < n; i++)
		if (strcmp(b,w[i].num)==0) 
		{
			f = 1;
			if (f == 1) 
			{
				printf("%-15s%-12s", "学生学号", "学生姓名");
				printf("%-8s%-8s%-8s%-8s", "高数", "计算机", "英语", "总分");
				printf("%-8s\n", "平均分");
				printf("%-15s%-12s%-8d%-8d",w[i].num,w[i].nam,w[i].s[0],w[i].s[1]);
				printf("%-8d%-8d%-8.2f\n", w[i].s[2], w[i].s[3], w[i].aver);
			}
		}
	if(f==0) printf("查无结果!\n");
}
void aver80()
{
	printf("%-15s%-12s", "学生学号", "学生姓名");
	printf("%-8s%-8s%-8s%-8s%-8s\n", "高数", "计算机", "英语", "总分", "平均分");
	for (i = 0; i < n; i++)
		if (w[i].aver > 80)
		{
			printf("%-15s%-12s%-8d%-8d", w[i].num, w[i].nam, w[i].s[0], w[i].s[1]);
			printf("%-8d%-8d%-8.2f\n",w[i].s[2], w[i].s[3], w[i].aver);
		}
}
void xiugai()
{
	char x[20],a;
	int flag=0;
	printf("请输入要修改学生的学号:");
	scanf("%s",x);
	getchar();
	for(i=0;i<n;i++)
	if(strcmp(x,w[i].num)==0) flag=1;
	if(flag==1)
	{
		printf("请输入要修改的信息(m (高数)or e(英语) or c(计算机)):");
		scanf("%c",&a);
		for(i=0;i<n;i++)
		{
			if(strcmp(x,w[i].num)==0)
			switch(a)
			{
					
				case 'm':
					printf("请输入数学成绩:");
					scanf("%d",&w[i].s[0]);
					break;
				case 'e':
					printf("请输入英语成绩:");
					scanf("%d",&w[i].s[1]);
					break;
				case 'c':
					printf("请输入计算机成绩:");
					scanf("%d",&w[i].s[2]);
					break;		
			}
		}	 
	}
	if(flag==0)
		{
			printf("无该学生,请重试\n");
			return ;
		}
	printf("%-15s%-12s", "学生学号", "学生姓名");	
	printf("%-8s%-8s%-8s%-8s", "高数", "计算机", "英语", "总分");
	printf("%-8s\n", "平均分");
	for(i=0;i<n;i++)
	{
		w[i].s[3] = w[i].s[0] + w[i].s[1] + w[i].s[2];
		w[i].aver = w[i].s[3] / 3.0;
		printf("%-15s%-12s%-8d%-8d",w[i].num,w[i].nam,w[i].s[0],w[i].s[1]);
		printf("%-8d%-8d%-8.2f\n",w[i].s[2],w[i].s[3],w[i].aver);
	}
}
