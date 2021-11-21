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



int main() {
	// 声明一个图：	
	ALGraph LG;
	CreateUDG(LG);
	PrintUDG(LG);
}

