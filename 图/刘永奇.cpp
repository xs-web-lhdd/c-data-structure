#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
#define MVNum 100
#define ERROR 0
#define OK 1
#define OVERFLOW -1
typedef int Status;

//边结点 
typedef struct ArcNode{
	int adjvex;
	struct ArcNode *nextarc;//指向下一条边的指针 
}ArcNode,*Arc;

//顶点信息 
typedef struct VNode{
	char data;
	int indegree;
	ArcNode *firstarc;		//指向第一条依附顶点的边的指针 
}VNode,AdjList[MVNum];		//AdjList 表示邻接表类型 

typedef struct{    			//邻接表 
	AdjList vertices;
	int vexnum,arcnum;		//图的当前顶点数和边数 
}Graph;

//查询c在G中位置，返回该位置的下标 
int LocateVex(Graph G,char c){
	int i;
	for(i=0;i<G.vexnum;i++)
		if(G.vertices[i].data==c)
			return i;
}

//邻接表的信息 
void print(Graph G){
	int i;
	Arc p;p=new ArcNode;
	printf("图的邻接表");
	for(i=0;i<G.vexnum;i++){
		printf("\n%d %4c",i,G.vertices[i].data);
		p=G.vertices[i].firstarc;
		while(p!=NULL){
			printf("-->%d",p->adjvex);
			p=p->nextarc;
		}
	}
	printf("\n");
}

//采用邻接表表示法，创建有向图 
Status CreatDG(Graph &G){
	int i,j,k;
	char c1,c2;
	printf("顶点数(均用回车结束) ");
	scanf("%d",&G.vexnum);		//输入总顶点数
	printf("边 数	");
	scanf("%d",&G.arcnum);		//输入总边数
	printf("输入各点\n");
	getchar();
	for(i=0;i<G.vexnum;++i){		//输入各点 
		scanf("%c",&G.vertices[i].data);		//输入顶点值 
		G.vertices[i].indegree=0;			//初始化入度为0 
		G.vertices[i].firstarc=NULL; 		//初始化表头结点的指针域为NULL 
	}
	printf("输入各有向边\n");
	for(k=0;k<G.arcnum;k++){
		getchar(); 
		printf("第%d条边的两端点下标",k+1);
		scanf("%c%c",&c1,&c2);		//输入有向边,c1指向c2 
		i=LocateVex(G,c1); j=LocateVex(G,c2);
		//确定v1和v2在G中位置,即顶点在G.vertices中的序号
		Arc p1;
		p1=new ArcNode; 
		p1->adjvex=j;
		p1->nextarc=G.vertices[i].firstarc;
		G.vertices[i].firstarc=p1;	//将新结点*p1插入顶点v1的边表头部 
		G.vertices[j].indegree++;	//v2入度+1 
	}
	return OK;
}

//返回v的第一个邻接点的下标,无邻接点返回-1
int FirstAdjVex(Graph G,int v){
	if(!G.vertices[v].firstarc)
		return G.vertices[v].firstarc->adjvex;
	else return -1;
}

//返回v相对于w的下一个邻接点的下标,没有则返回-1 
int NextAdjVex(Graph G,int v,int w){
	Arc p;
	p=new ArcNode;
	if(w!=G.vertices[v].firstarc->adjvex)
		p=G.vertices[v].firstarc;
	while(w!=p->adjvex){
		p=p->nextarc;
	}
	if(!p->nextarc)	return p->nextarc->adjvex;
	else return -1;
}

int visited[MVNum];				//访问标志数组，初值为"false"

//采用邻接表表示图的深度优先遍历
void DFS(Graph G,int v){		//从第v个点出发深度优先遍历图G 
	Arc p;
	p=new ArcNode;
	printf("%3c",G.vertices[v].data);
	visited[v]=1;
	p=G.vertices[v].firstarc;
	while(p!=NULL){
		if(!visited[p->adjvex]) DFS(G,p->adjvex);
		p=p->nextarc;
	}
}

//深度优先搜索遍历非连通图 
void DFSTraverse(Graph G){
	int v;char c;
	for(v=0;v<G.vexnum;v++) visited[v]=0;//访问标志数组初始化 
	getchar();
	printf("从哪个点开始深度优先遍历");
	scanf("%c",&c);
	v=LocateVex(G,c);
	DFS(G,v); 
	for(v=0;v<G.vexnum;v++)
		if(!visited[v]) DFS(G,v);
}

typedef struct{
	int *base;
	int front;
	int rear;
}SqQueue;

//初始化队列 
int InitQueue(SqQueue &Q){
	Q.base=(int*)malloc(MAXSIZE*sizeof(int));
	if(!Q.base) return 0;
	Q.rear=Q.front;
}

//入队 
int EnQueue(SqQueue &Q,int e){
	if((Q.rear+1)%MAXSIZE==Q.front) return 0;
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXSIZE;
	return 1;
}

//出队 
int DeQueue(SqQueue &Q,int &e){
	if(Q.rear==Q.front) return 0;
	e=Q.base[Q.front];
	Q.front=(Q.front+1%MAXSIZE);
	return 1;
}

//判断队列是否为空
int QueueEmpty(SqQueue Q){
	if(Q.rear==Q.front) return 1;
	else return 0;
}

SqQueue Q;
//广度优先搜索遍历连通图 
void BFS(Graph G,int k){
	int i;
	Arc p;
	p=new ArcNode;
	InitQueue(Q);
	printf("%3c",G.vertices[k].data);
	visited[k]=1;
	EnQueue(Q,k);
	while(QueueEmpty(Q)==0){
		DeQueue(Q,i);
		p=G.vertices[i].firstarc;
		while(p!=NULL){
			if(visited[p->adjvex]==0){
				printf("%3c",G.vertices[p->adjvex].data);
				visited[p->adjvex]=1;
				EnQueue(Q,p->adjvex);
			}
			p=p->nextarc;
		}
	}
}

void BFSTraverse(Graph G){
	int v;char c;
	for(v=0;v<G.vexnum;v++) visited[v]=0;
	getchar();
	printf("\n从哪个点开始广度优先遍历");
	scanf("%c",&c);
	v=LocateVex(G,c);
	BFS(G,v);
	for(v=0;v<G.vexnum;v++)
		if(!visited[v]) BFS(G,v);
}

typedef struct{//定义顺序栈
    int *base;
    int *top;
    int stacksize;
}SqStack;


Status Push(SqStack &S,int e)//入栈
{
    if(S.top-S.base == S.stacksize)  //判断栈满
        return ERROR;
    *S.top++ = e;                    //元素e压入栈顶，栈顶指针上移一位;
    return OK;
 }
Status Pop(SqStack &S, int &e){//出栈
    if(S.top == S.base)   return ERROR;
    e = *--S.top;
    return OK;
}

void GetTop(SqStack S,int &e){//取栈顶元素
    if(S.top != S.base)
	e=*(S.top - 1);
}

Status StackEmpty(SqStack S){//判断栈空 
    if(S.top - S.base == 0)    return OK;
    else return ERROR;
}

Status InitStack(SqStack &S){//创建顺序栈 
    S.base =new int[MAXSIZE];
    if(!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}

//拓扑排序 
Status TopologicalSort(Graph G){
	printf("\n拓扑排序\n");
	SqStack S;
	InitStack(S);
	int i,topo[MVNum];
	for(i=0;i<G.vexnum;i++){ 
		if(!G.vertices[i].indegree){
			Push(S,i);
			printf("%3c",G.vertices[i].data);
		}
	}
	int m=0,k;
	Arc p;	p=new ArcNode;
	while(!StackEmpty(S)){
		Pop(S,i);
		topo[m]=i;
		m++;
		p=G.vertices[i].firstarc;
		while(p!=NULL){
			k=p->adjvex;
			--G.vertices[k].indegree;
			if(!G.vertices[k].indegree){
				Push(S,k);
				printf("%3c",G.vertices[k].data);
			}
			p=p->nextarc;
		}
	}
	if(m<G.vexnum) return ERROR;
	else return OK;
}

int main(){
	Graph G;
	CreatDG(G);
	print(G);
	char v;int x;
	DFSTraverse(G);
	BFSTraverse(G);
	x=TopologicalSort(G);
	if(!x) printf("有向图有回路");
	printf("\n");
	system("pause");
	return 0;
}
