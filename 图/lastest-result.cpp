#include<bits/stdc++.h>

using namespace std;

#define MAXSIZE 100
// 最大顶点数 
#define MVNum 100
typedef char VerTexType;
typedef int OtherInfo;

// 定义一个全局变量 --- 记录顶点个数 
int allNum; 

// 边节点类型： 
typedef struct ArcNode
{
	// 该边所指向的顶点的位置	
	int adjvex;
	// 指向下一条边的指针
	struct ArcNode * nextarc;
	// 和边相关的信息
	OtherInfo info;	 
} ArcNode;

// 顶点类型： 
typedef struct VNode
{
	// 顶点的数据域存放顶点的名字如：A B	
	VerTexType data;
	// 指向第一条依附该顶点的边的指针	
	ArcNode *firstarc;
	// 定义入度	
	int indegree;
} VNode, AdjList[MVNum];

// 邻接表： 
typedef struct
{
	AdjList vertices;
	// 顶点数，边数 
	int  vexnum, arcnum;
} ALGraph; 


// 去表中找下标： 
int LocateVex(ALGraph G, VerTexType V)
{
	for(int i = 0; i < G.vexnum; ++i) {
		if (G.vertices[i].data == V) {
			return i;
		}
	}
	// 找到了返回下标，找不到返回 -1，几乎不会找不到	
	return -1;
}


// 打印邻接表---无向图：
void PrintUDG(ALGraph G) {
	for (int i = 0; i < G.vexnum; ++i) {
		cout<<G.vertices[i].data;
		while(G.vertices[i].firstarc) {
			cout<<"->";
			cout<<G.vertices[i].firstarc->adjvex;
			G.vertices[i].firstarc = G.vertices[i].firstarc->nextarc;
		}
		cout<<"\n";
	}
} 



// 创建无向图：
int CreateUDG(ALGraph &G)
{
	printf("请输入图的顶点数和边数\n");
	cin>>G.vexnum>>G.arcnum;
	allNum=G.vexnum;
	cout<<"请输入依次顶点的值\n";
	for(int i = 0; i < G.vexnum; ++i) {
		cin>>G.vertices[i].data;
		// 将各顶点的指针域设为空
		G.vertices[i].firstarc=NULL;
	}
	
	
	// 由边形成的若干个单链表： 
	for(int k = 0; k < G.arcnum; ++k) {
		VerTexType v1, v2;
		int i, j;
		ArcNode *p1, *p2; 
		cout<<"请输入第"<<k+1<<"边的起始节点和末尾节点\n";
		cin>>v1>>v2;
		// 找出 v1，v2 在 G.vertices 中的下标；		
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);

		// 采用头插法---将节点插入到单链表中		
		p1 = new ArcNode;
		p1->adjvex = j;
		p1->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p1; 
	
	}
	return 1;
}


//// 邻接表表示图的深度优先遍历： 
bool visited[MVNum];
//void DFS_AL (ALGraph G, int v) {
//	ArcNode *p;
//	int w;
//	cout<<G.vertices[v].data;
//	visited[v] = true;
//	p = G.vertices[v].firstarc;
//	while(p != NULL) {
//		w = p->adjvex;
//		if (!visited[w]) {
//			DFS_AL(G, w);
//		}
//		p = p->nextarc;
//	}
//	// 找出所有节点，如果该节点也没有入度，则从该节点再遍历一次	
//	for(int i = 0; i < allNum; ++i) {
//		if (!visited[i]) {
//			DFS_AL (G, i);
//		}
//	}
//}



//采用邻接表表示图的深度优先遍历
void DFS_AL(ALGraph G,int v){		//从第v个点出发深度优先遍历图G 
	ArcNode *p;
	p=new ArcNode;
	cout<<G.vertices[v].data;
	visited[v]=1;
	p=G.vertices[v].firstarc;
	while(p!=NULL){
		if(!visited[p->adjvex]) DFS_AL(G,p->adjvex);
		p=p->nextarc;
	}
}

//深度优先搜索遍历非连通图 
void DFSTraverse(ALGraph G){
	int v;
	char c;
	for(v=0;v<G.vexnum;v++) visited[v]=0;//访问标志数组初始化 
	cout<<"请输入深度优先遍历的开始点：\n";
	cin>>c;
	v=LocateVex(G,c);
	DFS_AL(G,v); 
	for(v=0;v<G.vexnum;v++)
		if(!visited[v]) DFS_AL(G,v);
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
void BFS(ALGraph G,int k){
	int i;
	ArcNode *p;
	p=new ArcNode;
	InitQueue(Q);
	cout<<G.vertices[k].data; 
	visited[k]=1;
	EnQueue(Q,k);
	while(QueueEmpty(Q)==0){
		DeQueue(Q,i);
		p=G.vertices[i].firstarc;
		while(p!=NULL){
			if(visited[p->adjvex]==0){
				cout<<G.vertices[p->adjvex].data;
				visited[p->adjvex]=1;
				EnQueue(Q,p->adjvex);
			}
			p=p->nextarc;
		}
	}
}

void BFSTraverse(ALGraph G){
	int v;char c;
	for(v=0;v<G.vexnum;v++) visited[v]=0;
	getchar();
	cout<<"请输入广度优先遍历的开始点：\n";
	cin>>c;
	v=LocateVex(G,c);
	BFS(G,v);
	for(v=0;v<G.vexnum;v++)
		if(!visited[v]) BFS(G,v);
}



//------------------------------------- 以下是拓扑排序用到的数据结构 -----------------------------------------------------------

/*顺序栈的定义*/
#define Stack_Size 100
typedef struct sqStack
{
       int *elem;
       int top;
       int stackSize;//栈数组长度
}sqStack;
 
 
/*顺序栈的初始化*/
void initStack_Sq(sqStack &S)
{
       S.elem=new int[Stack_Size];
       S.top=-1;
       S.stackSize=Stack_Size;
}
/*入栈*/
void push(sqStack &S,int x)
{
       if(S.top==Stack_Size-1)
              cout<<"Stack Overflow!";
       S.elem[++S.top]=x;
}
 
/*出栈*/
int pop(sqStack &S)
{
       int x;
       if(S.top==-1)
              cout<<"Stack Empty!";
       x=S.elem[S.top--];
       return x;
}


//拓扑排序
int TopoSort(ALGraph &G)
{
    sqStack S;
    initStack_Sq(S);
    ArcNode *p;
    int count=0;
    int i,j;
    
	// 将所有点的入度初始化为0    
    for(i=0;i<G.vexnum;i++)
        G.vertices[i].indegree=0;//初始化为0
        
    for(i=0;i<G.vexnum;i++)
    {//计算各个顶点的入度
        p=G.vertices[i].firstarc;
        while(p)
        {
            G.vertices[p->adjvex].indegree++;
            p=p->nextarc;
        }
    }
    
    for(i=0;i<G.vexnum;i++)
        if(G.vertices[i].indegree==0)
            push(S,i);//将度为0的顶点入栈,这里进栈的是入度为0的顶点在数组中的位置
            
    while(S.top!=-1)
    {
        j=pop(S);
        cout<<G.vertices[j].data<<" ";//将栈顶的元素出栈且输出，即将入度为0的顶点输出
        count++;//计数器加1
        p=G.vertices[j].firstarc;//让p指向入度为0的顶点的第一个边表结点
        while(p)
        {
            G.vertices[p->adjvex].indegree--;//将入度为0的顶点的邻接点的入度减1
            if(G.vertices[p->adjvex].indegree==0)
                push(S,p->adjvex);//度减1后的顶点如果其入度为0，则将其入栈
            p=p->nextarc;
        }
    }
    if(count<G.vexnum)
        cout<<"该有向图有回路"<<endl;  
	return 0; 
}



int main() {
	// 声明一个图：	
	ALGraph LG;
	// 创造一个有向图	
	CreateUDG(LG);
	// 打印出来有向图	
	PrintUDG(LG);
	// 深度优点遍历	
	DFSTraverse(LG);
	cout<<"\n";
	// 从输入点进行广度优先遍历	
	BFSTraverse(LG);
	cout<<"\n";
	cout<<"拓扑排序的结果是：\n"; 
	// 对图进行拓扑排序	
	TopoSort(LG);
}
 
