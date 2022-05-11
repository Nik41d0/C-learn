#include<stdio.h>
#include<stdlib.h>
#define M 10
#define N 10
#define stack_init_size 100
#define stackincrement 10


typedef struct
{
	int x,y;
}PostType;
typedef struct
{
	int ord;
	PostType seat;
	int di;
}SElemType;
typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}sqstack;


int initstack(sqstack *s)
{
	s->base=(SElemType *)malloc(stack_init_size*sizeof(SElemType));
	if(!s->base) return 0;
	s->top=s->base;
	s->stacksize=stack_init_size;
	return 1;
}


void destroy(sqstack *s)
{
	free(s->base);
}


int stackempty(sqstack *s)
{
	if(s->base==s->top) return 1;
	else
		return 0;
}


void stacktraverse(sqstack *s)
{
	SElemType *p;
	p=s->base;
	printf("\n输出栈:\n");
	while(p<s->top)
	{
		printf("%2d-(%d,%d)\t",p->ord,p->seat,p->seat.x);
		p++;
	}
}


int pop(sqstack *s,SElemType *e)
{
	if(s->top!=s->base)
	{
		*e=*(s->top-1);
		s->top--;
		return 1;
	}
	else
		return 0;
}


int push(sqstack *s,SElemType e)
{
	*(s->top)=e;
	s->top++;
	return 1;
}


int Pass(int maze[M][N],PostType c)
{
	if(maze[c.y][c.x]==0)
		return 1;
	else
		return 0;
}


void FootPrint(int maze[M][N],PostType c)
{
	maze[c.y][c.x]=2;
}


void MarkPrint(int maze[M][N],PostType c)
{
	maze[c.y][c.x]=3;
}


PostType NextPos(PostType c,int i)
{
	PostType cpos=c;
	switch(i)
	{
		case 1: cpos.x+=1;break;
		case 2: cpos.y+=1;break;
		case 3: cpos.x-=1;break;
		case 4: cpos.y-=1;break;
	}
	return cpos;
}


void MazePath(int mg[M][N])
{
	sqstack sq;
	int curstep;
	PostType curpos={1,1},end={8,8};
	SElemType e;
	initstack(&sq);
	curstep=1;
	do
	{
		if(Pass(mg,curpos))
		{
			FootPrint(mg,curpos);
			e.ord=curstep;
			e.seat=curpos;
			e.di=1;
			push(&sq,e);
			if(curpos.x==end.x&&curpos.y==end.y)
				break;
			else
			{
				curpos=NextPos(curpos,1);
				curstep++;
			}
		}
		else
		{
			if(!stackempty(&sq))
			{
				pop(&sq,&e);
				while(e.di==4&&!stackempty(&sq))
				{
					MarkPrint(mg,e.seat);
					pop(&sq,&e);
					curstep--;
				}
				if(e.di<4)
				{
					e.di++;
					push(&sq,e);
					curpos=NextPos(e.seat,e.di);
				}
			}
		}
	}while(!stackempty(&sq));
	if(!stackempty(&sq))
	{
		printf("scucess!");
		stacktraverse(&sq);
	}
	else
		printf("no success!");
	destroy(&sq);
}


int main()
{
	int i,j,maze[M][N]={
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,1,0,0,1},
		{1,0,1,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,1,1,0,1},
		{1,0,1,1,1,1,1,1,0,1},
		{1,0,1,0,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,1,1,1},
		{1,0,1,0,1,0,0,0,0,1},
		{1,0,0,0,1,0,1,1,0,1},
		{1,1,1,1,1,1,1,1,1,1}};
	for(i=0;i<=9;i++)
	{
		for(j=0;j<=9;j++)
		{
			if(maze[i][j]==0) printf("■");
			else
				printf("□");
		}
		printf("\n");
	}
	MazePath(maze);
	printf("\n");
	for(i=0;i<=0;i++)
	{
		for(j=0;j<=9;j++)
			printf("%2d",maze[i][j]);
		printf("\n");
	}
	for(i=0;i<=9;i++)
	{
		for(j=0;j<=9;j++)
		{
			if(maze[i][j]==0) printf("■");
			else if(maze[i][j]==1) printf("□");
			else if(maze[i][j]==2) printf("★");
			else if(maze[i][j]==3) printf("☆");
		}
		printf("\n");
	}
	return 0;
}

