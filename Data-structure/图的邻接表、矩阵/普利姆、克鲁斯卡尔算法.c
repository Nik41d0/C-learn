#include<stdio.h>
#include<stdlib.h>
#define VEXNUM 6
#define ARCNUM 10
#define INF 9999 


struct Graph    // 通用图形定义，创建图形的邻接矩阵和邻接表(全局变量)
{
	int vexnum,arcnum,kind;     // 顶点数、边数、图形类:1234-无向图、有向图、无向网、有向网
	char vexs[VEXNUM+1];        // 定点字符数组(+1 是'\0')
	int arcs[30];       // 边起止点下标和权值数组
}graph={6,10,4,"abcdef",{0,1,2,0,2,5,1,2,1,1,3,3,2,3,3,2,4,4,2,5,1,3,4,1,3,5,4,4,5,1}};
// 6顶点、10条边、有向网、顶点依次为abcdef、a-b:2;a-c:5;b-c:1;b-d:3;c-d:3;c-e:4;c-f:1;d-e:1;d-f:4;e-f:1;
typedef struct MGraph_Mat   // 图的邻接矩阵存储数据定义
{
	int vexnum,arcnum;  	// 顶点数、边数
	char vexs[VEXNUM];      // 顶点数组
	int arcs[VEXNUM][VEXNUM];       // 邻接矩阵
	int kind;       // 图类型
}MGraph_Mat;


void create_Mat(MGraph_Mat *g)      // 创建图的邻接矩阵
{
	int i,j;
	g->vexnum=graph.vexnum; // 顶点数
	g->arcnum=graph.arcnum; // 边数
	g->kind=graph.kind; // 图类型
	
	for(i=0;i<=g->vexnum-1;i++)
		g->vexs[i]=graph.vexs[i];	// 逐个赋值顶点字符
		   
	for(i=1;i<=g->vexnum;i++)
	for(j=1;j<=g->vexnum;j++)
	{
		if(g->kind==1||g->kind==2)  // 如果是无向图或有向图
			g->arcs[i-1][j-1]=0;    // 邻接矩阵全部初始化0
		else
			g->arcs[i-1][j-1]=INF;  // 邻接矩阵全部初始无穷
	}
	for(i=0;i<=g->arcnum-1;i++)
	{
		if(g->kind==1)  // 如果是无向图，一条边处理矩阵两个元素，放1
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=1;
			g->arcs[graph.arcs[i*3+1]][graph.arcs[i*3]]=1;  // 对称点
		}
		else if(g->kind==2)     // 如果是有向图，一条边处理矩阵一个元素，放1
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=1;
		else if(g->kind==3)     // 如果是无向图，一条边处理矩阵两个元素，放权值
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=graph.arcs[i*3+2];
			g->arcs[graph.arcs[i*3+1]][graph.arcs[i*3]]=graph.arcs[i*3+2];  // 对称点
		}
		else if(g->kind==4)		// 如果是有向图，一条边处理矩阵一个元素，放权值
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=graph.arcs[i*3+2];
	}
}


void print_Mat(MGraph_Mat g)    // 显示邻接矩阵
{
	int i,j;
	printf("   ");
	for(i=0;i<=g.vexnum-1;i++)
		printf("%3c",g.vexs[i]);    // 显示第一行，各节点字符
	printf("\n");
	for(i=0;i<=g.vexnum-1;i++)  // 各行
	{
		printf("  %c  ",g.vexs[i]); // 先显示字符
		for(j=0;j<=g.vexnum-1;j++)  // 各列
		{
			if(g.kind==1||g.kind==2)    // 如果是图
				printf("%d  ",g.arcs[i][j]);    // 显示1、0
			else    // 如果是网
			{
				if(g.arcs[i][j]==INF)
					printf("∞ "); 	// 显示无穷
				else
					printf("%d  ",g.arcs[i][j]);    // 或权值
			}
		}
		printf("\n");
 	}
}


typedef struct arcnode  // 邻接表-边节点
{
	int adjvex,weight;  // 邻接边下标、权值
	struct arcnode* nextarc;    // 下一边表指针
}arcnode;
struct vexnode      // 顶点节点
{
	char vexdata;   // 顶点字符数据
	arcnode *firstarc;  // 第一个边表指针
};
typedef struct MGraph_Adj   // 图的邻接表存储数据定义
{
	int vexnum,arcnum;  // 顶点数、边数
	struct vexnode vexarr[VEXNUM];  // 定点节点数组
	int kind;       // 图类型
}MGraph_Adj;


void create_Adj(MGraph_Adj *g)      // 根据全局通用图形定义graph，创建图的邻接表
{
	int i;
	struct arcnode *p=NULL;
	g->vexnum=graph.vexnum; // 顶点数
	g->arcnum=graph.arcnum; // 边数
	g->kind=graph.kind; // 图类型
	for(i=0;i<=g->vexnum-1;i++)
	{
		g->vexarr[i].vexdata=graph.vexs[i];     // 逐个顶点赋值
		g->vexarr[i].firstarc=NULL;     // 第一条边初始值置空
	}
	for(i=0;i<=g->arcnum-1;i++)     // 逐条边创建边表节点
	{
		p=(struct arcnode *)(malloc(sizeof(struct arcnode)));   // 申请边表空间
		p->adjvex=graph.arcs[i*3+1];    // 边节点-边下表
		p->weight=graph.arcs[i*3+2];    // 边顶点-权值
		p->nextarc=g->vexarr[graph.arcs[i*3]].firstarc;
		g->vexarr[graph.arcs[i*3]].firstarc=p;  // 将p 节点插入在指定节点之后-前插
		if(g->kind==1||g->kind==3)      // 如果是无向图或无向网，需在创建一节点
		{
			p=(struct arcnode *)(malloc(sizeof(struct arcnode)));
			p->adjvex=graph.arcs[i*3];      // 边节点-边下标
			p->weight=graph.arcs[i*3+2];    // 边节点-权值
			p->nextarc=g->vexarr[graph.arcs[i*3+1]].firstarc;
			g->vexarr[graph.arcs[i*3+1]].firstarc=p;    // 将p节点插入在指定顶点之后
		}
	}
}


void print_Adj(MGraph_Adj g)    // 显示邻接表
{
	int i;
	struct arcnode *p=NULL;
	printf("\n\n");
	for(i=0;i<=g.vexnum-1;i++)      // 处理各顶点
	{
		printf("  %d %c",i,g.vexarr[i].vexdata);    // 下标、顶点字符
		p=g.vexarr[i].firstarc;     // p 指向第一个边表节点
		while(p)    // 逐个边表示
		{
			if(g.kind==1||g.kind==2)    // 如果是图只显示边序号
				printf("->%d",p->adjvex);
			else    // 如果是网，同时显示边序号、权值
				printf("->%d 权:%d|",p->adjvex,p->weight);
			p=p->nextarc;   // 下一边表
		}
		printf("\n");
	}
}


int prim_Mat(MGraph_Mat g,int v)    // 图矩阵g，下标v点开始
{
	int lowcost[VEXNUM];    // 已选入T点到其他各点 权值数组
	int mst[VEXNUM];    // 已选入T点到其他各点 下标数组
	int i,j,min,minid,sum=0;
	printf("邻接矩阵的普利姆算法为:");
	for(i=0;i<=g.vexnum-1;i++)  // 选v点如T
	{
		lowcost[i]=g.arcs[v][i];    // 各顶点到v点距离(lowcost[i])
		mst[i]=v;   // 各点到v点(i--mst[i])
	}
	for(i=1;i<=g.vexnum-1;i++)  // 循环选点-顶点个数减1次
	{
		min=INF;    // 最短距离初始化，为选最短作准备
		minid=v;    // 最小点下标初始化
		for(j=0;j<=g.vexnum-1;j++)  // 从权值数组找最小的
			if(lowcost[j]<min&&lowcost[j]!=0)   // 有边且更小，则更新
			{
				min=lowcost[j]; // 最小权值
				minid=j;    // 最小权值下标
			}
		printf("\n%d->%d=%d",mst[minid],minid,min);
		sum+=min;   // 最小权值累加
		lowcost[minid]=0;   // 将找到的最小边从最短距离数组删除
		for(j=1+v;j<=g.vexnum-1+v;j++)  // minid点入T，不包括v
		// 从新入T点minid里，更新最小权值数组及下标
			if(g.arcs[minid][j%g.vexnum]<lowcost[j%g.vexnum])
			{
				lowcost[j%g.vexnum]=g.arcs[minid][j%g.vexnum];
				// 从T内各点到其他各点最小权值数组
				mst[j%g.vexnum]=minid;  // 从T内各点到其他个点最小权值对应的下标数组
			}
	}
	return sum; // 最小生成树权值
}

int prim_Adj(MGraph_Adj g,int v)    // 图g邻接表，v下标点
{
	arcnode *p=NULL;
	int lowcost[VEXNUM];
	int mst[VEXNUM];
	int i,j,min,minid,sum=0;
	printf("邻接表的普利姆算法为:");
	for(i=0;i<=g.vexnum-1;i++)
	{
		lowcost[i]=INF; // 各点到v的距离(lowcoast[i])，全部初始化为无穷
		mst[i]=v;   // 各顶点到v点(i--mst[i])
	}
	p=g.vexarr[v].firstarc;
	while(p)
	{
		lowcost[p->adjvex]=p->weight;   // 有边的更新距离
		p=p->nextarc;
	}
	for(i=1;i<=g.vexnum-1;i++)  // 循环选点-顶点个数减1
	{
		min=INF;
		minid=v;
		for(j=0;j<=g.vexnum-1;j++)  // 从权值数组里找最小的
			if(lowcost[j]<min&&lowcost[j]!=0)
			{
				min=lowcost[j]; // 最小权值
				minid=j;    // 最小权值下标
			}
		printf("\n%d->%d=%d",mst[minid],minid,min); // 找到的最小权值点，点-点:距离
		sum+=min;   // 最小权值累加
		lowcost[minid]=0;   // 将找到的最小边从最短距离数组删除
		p=g.vexarr[minid].firstarc; // minid点入T
		while(p)    // 转到minid到其他各点
		{
			if((p->weight<lowcost[p->adjvex])&&(p->adjvex!=mst[p->adjvex]))
			// 如果权值更小，且不是相同重复边
			{
				lowcost[p->adjvex]=p->weight;   // 更新最小权值
				mst[p->adjvex]=minid;   // 更新最短权值下标
			}
			p=p->nextarc;
		}
	}
	return sum;
}


typedef struct Edge
{
	int u;  // 边的起始顶点
	int v;  // 边的起始终点
	int w;  // 边的权值
}Edge;  // 边类型-用于克鲁斯卡尔存储边/边排序/选边

void Bubblesort(Edge R[],int e)
// 冒泡排序，对数组R中e条边按权值递增排序，为克鲁斯卡尔选边准备
{
	Edge temp;
	int i,j,swap;
	for(i=0;i<=e-2;i++) // 进行e-1趟排序
	{
		swap=0;
		for(j=0;j<=e-2-i;j++)
			if(R[j].w>R[j+1].w) // 若前一元素比后一元素大
			{
				temp=R[j];
				R[j]=R[j+1];
				R[j+1]=temp;
				swap=1; // 交换标志
			}
		if(swap==0)
			break;  // 本次比较中未出现交换规则交换则结束排序
	}
}


int krskl_Mat(MGraph_Mat g) // 在顶点为n的连接图中构造最小生成树，g邻接矩阵
{
	int i,j,v1,u1,sn1,sn2,k=0,sum=0;
	int vest[VEXNUM];   // 集合数字vest判断两顶点间是否连通
	Edge E[ARCNUM]; // E为边数组
	printf("\n邻接矩阵的克鲁斯卡尔算法为:");
	for(i=0;i<=g.vexnum-1;i++)
		for(j=0;j<=i-1;j++) // 无向图对称，只处理左下三角
			if(g.arcs[i][j]!=INF)   // 若有边
			{
				E[k].u=i;
				E[k].v=j;
				E[k].w=g.arcs[i][j];
				k++;
			}
	Bubblesort(E,k);    // 用冒泡排序对数组E中的k条边按权值递增排序
	for(i=0;i<g.vexnum;i++) // 初始化辅助数组
		vest[i]=i;  // 给每个顶点之置不同连通分量编号，即初始时有n个连通分量
	k=1;    // 表述当前构造的第n条边，初始值为1
	j=0;    // E中元素的下标，初始值为0
	while(k<=g.vexnum-1)    // 循环产生最小生成树的n-1条边，循环n-1次
	{
		u1=E[j].u;
		v1=E[j].v;  // 取一条边的头尾顶点
		sn1=vest[u1];
		sn2=vest[v1];   // 分别取到这两个顶点所属的集合编号
		if(sn1!=sn2)    // 两顶点分属于不同集合则该边为最小生成树的一条边
		{
			printf("\n%d->%d=%d",u1,v1,E[j].w);
			sum+=E[j].w;    // 最小权值累加
			k++;    // 生成的边数+1
			for(i=0;i<=g.vexnum;i++)    // 两个集合统一编号，合并成一个集合
				if(vest[i]==sn2)    // 集合编号sn2的第i号边其他编号改为sn1
					vest[i]=sn1;
		}   // 若属于同一集合不处理
		j++;    // 扫描下一条最小边
	}
	return sum;
}

int krskl_Adj(MGraph_Adj g)
{
	int i,j,v1,u1,sn1,sn2,k=0,sum=0;
	int vest[VEXNUM];   // 数组vest用于判断两顶点之间是否连通
	Edge E[ARCNUM]; // E为边数组
	arcnode *p=NULL;
	printf("\n邻接表的克鲁斯卡尔算法为:");
	for(i=0;i<=g.vexnum-1;i++)  // 循环顶点数
	{
		p=g.vexarr[i].firstarc;
		while(p)    // 循环边表
		{
			for(j=0;j<=k-1;j++) // 循环已经加入边表的各边
				if(E[j].u==p->adjvex&&E[j].v==i)    // 查找该边是否加过
					break;  // 若加过则跳出
			if(j==k)
			{
				E[k].u=i;
				E[k].v=p->adjvex;
				E[k].w=p->weight;
				k++;    // 边表加入边个数
			}
			p=p->nextarc;
		}
	}
	Bubblesort(E,k);    // 用冒泡排序对数组E中的k条边按权值递增排序
	for(i=0;i<g.vexnum;i++) // 初始化辅助数组
		vest[i]=i;  // 给每个顶点置不同连通分量，即初始时有n个连通分量
	k=1;    // k表示当前构造生成树第n条边，初始值为1
	j=0;    // j为数组E中元素的下标，初始值为0
	while(k<g.vexnum)
	{
		u1=E[j].u;
		v1=E[j].v;
		sn1=vest[u1];   // 分别得到这两个顶点所属的集合编号
		sn2=vest[v1];
		if(sn1!=sn2)    // 两顶点分属于不同不同集合则该边为最小生成树的一条边
		{
			printf("\n%d->%d=%d",u1,v1,E[j].w);
			sum+=E[j].w;
			k++;    // 生成的边数+1
			for(i=0;i<g.vexnum;i++) // 两个集合统一编号
				if(vest[i]==sn2)    // 集合编号sn2的第i号边其他号改为sn1
					vest[i]=sn1;
		}
		j++;    // 扫描下一条边
	}
	return sum;
}


int main()
{
	MGraph_Mat g;
	MGraph_Adj g1;
	create_Mat(&g);
	print_Mat(g);
	int sq;
	
	sq=prim_Mat(g,0);
	printf("\n其生成树的权值和为:%d",sq);
	
	sq=krskl_Mat(g);
	printf("\n其生成树的权值和为:%d",sq);
	
	create_Adj(&g1);
	print_Adj(g1);
	
	sq=prim_Adj(g1,0);
	printf("\n其生成树的权值和为:%d",sq);

	sq=krskl_Adj(g1);
	printf("\n其生成树的权值和为:%d",sq)
	
	return 0;
}
