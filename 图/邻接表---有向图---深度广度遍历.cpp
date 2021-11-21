#include<bits/stdc++.h>

using namespace std;

// 最大顶点数 
#define MVNum 100
typedef char VerTexType;
typedef int OtherInfo;

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
		cout<<"请输入边的起始节点和末尾节点\n";
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


// 邻接表表示图的深度优先遍历： 
bool visited[MVNum];
void DFS_AL (ALGraph G, int v) {
	ArcNode *p;
	int w;
	cout<<v;
	visited[v] = true;
	p = G.vertices[v].firstarc;
	while(p != NULL) {
		w = p->adjvex;
		if (!visited[w]) {
			DFS_AL(G, w);
		}
		p = p->nextarc;
	}
} 


//--------栈---------
typedef struct StackNode{
    int data;
    struct StackNode *next;
}StackNode,*LinkStack;



LinkStack p1;
LinkStack S;
char ch;
char arr[10000];
int num[11];
int len=0,m=0,n=0;

//初始化栈
void InitStack(LinkStack &S){
    S=NULL;
}
//入栈
void Push(LinkStack &S,int e){
    p1=new StackNode;
    p1->data=e;
    p1->next=S;
    S=p1;
}
//出栈
void Pop(LinkStack &S,int &e){
    if(S==NULL) return ;
    e=S->data;
    S=S->next;
}
//判断栈是否为空
bool StackEmpty(LinkStack S){
    return S==NULL;
}

//void FindInDegree(ALGraph G, int []) {
//	
//}


// 拓扑排序：
int TopologicalSort(ALGraph G, int topo[])
{
	// 找出各顶点的入度存放到 indegree 中	
	FindInDegree(G, indegree);
	// 栈 S 初始化为空	
	InitStack(S);
	for(int i = 0; i < G.vexnum; ++i) {
		if (!indegree[i]) {
			Push(S, i);
		}
	}
	m=0;
	while(!StackEmpty(S)) {
		Pop(S, i);
		topo[m]=i;
		++m;
		p=G.vertices[i].firstarc;
		while(p!=NULL) {
			k=p->adjvex;
			--indegree[k];
			if (indegree[k]==0) {
				Push(S, k);
			}
			p=p->nextarc;
		}
	}
	if (m < G.vexnum) {
	//	有回路返回 -1，没有返回 0	
		return -1;
	} else {
		return 0;
	}
}  



int main() {
	// 声明一个图：	
	ALGraph LG;
	CreateUDG(LG);
	PrintUDG(LG);
	int startDot;
	cout<<"请输入深度优点遍历的开始点\n";
	cin>>startDot;
	DFS_AL(LG , startDot);
}
 
