#include<stdio.h>
#define M 10
#define N 10
#define MaxSize (M-2)*(N-2)


struct
{
	int x,y;
	int pre;
}Que[MaxSize];


void printpath(int front)
{
	int k=front,j,ns=0;
	do
	{
		j=k;
		k=Que[k].pre;
		Que[j].pre=-1;
	}while(k!=0);
	printf("路径如下:\n");
	k=0;
	while(k<=front)
	{
		if(Que[k].pre==-1)
		{
			ns++;
			printf("%d %d,",Que[k].x,Que[k].y);
			if(ns%7==0)
				printf("\n");
		}
		k++;
	}
}


void MazePath(int mg[M][N],int x1,int y1,int x2,int y2)
{
	int front=-1,rear=0;
	int x,y,find=0,di;
	Que[rear].y=y1;
	Que[rear].x=x1;
	Que[rear].pre=-1;
	mg[y1][x1]=2;
	while(front!=rear&&!find)
	{
		front++;
		y=Que[front].y;
		x=Que[front].x;
		if(x==x2&&y==y2)
		{
			find=1;
			printf("success!\n");
			printpath(front);
			break;
		}
		for(di=1;di<=4;di++)
		{
			switch(di)
			{

				case 1:x=Que[front].x+1;y=Que[front].y; break;
			   	case 2:x=Que[front].x;y=Que[front].y+1; break;
			   	case 3:x=Que[front].x-1;y=Que[front].y; break;
			   	case 4:x=Que[front].x;y=Que[front].y-1; break;
			}
			if(mg[y][x]==0)
			{
				rear++;
				Que[rear].x=x;
				Que[rear].y=y;
				Que[rear].pre=front;
				mg[y][x]=2;
			}
		}
	}
	if(!find)
		printf("no success!\n");
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
	for(i=0;i<=M-1;i++)
	{
		for(j=0;j<=N-1;j++)
		{
			if(maze[i][j]==0) printf("■");
			else
				printf("□");
		}
		printf("\n");
	}
	MazePath(maze,1,1,8,8);
	return 0;
}

