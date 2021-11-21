#include<bits/stdc++.h>

using namespace std;

#define MaxInt 32767
#define MAXNum 100
typedef char VerTexType;
typedef int ArcType;

typedef struct
{
	VerTexType vexs[MAXNum];
	ArcType arcs[MAXNum][MAXNum];
	int vexnum, arcnum;
} AMGraph;


int LocateVex(AMGraph G, VerTexType V)
{
	for(int k = 0; k < G.vexnum; ++k) {
		if (V == G.vexs[k]) {
			return k;
		}
	}
	return 0;
}


// 创建无向网：
int CreateUDM(AMGraph &G)
{
	printf("请先输入无向网的顶点数再输入边数：\n");
	cin>>G.vexnum>>G.arcnum;
	printf("请依次输入具体的顶点：\n");
	for(int i = 0; i < G.vexnum; ++i) {
		cin>>G.vexs[i];
	}
	
	// 初始化无向网 --- 默认是 	32767
	for(int i = 0; i < G.vexnum; ++i) {
		for(int j = 0; j < G.vexnum; ++j) {
			G.arcs[i][j]=MaxInt; 
		}
	}
	
	for(int k = 0; k < G.arcnum; ++k) {
		VerTexType v1, v2;
		int w, i, j;
		printf("请输入无向网的第一个顶点和第二个顶点和边的权值：\n");
		// 输入边的起始节点和末尾节点和边的权值		
		cin>>v1>>v2>>w;
		// 拿到起始节点和末尾节点在顶点表中的下标		
		i = LocateVex(G, v1);
		j = LocateVex(G, v2); 
		G.arcs[i][j] = w;
		G.arcs[j][i] = G.arcs[i][j];
	}
	return 1;
}

void PrintGraph (AMGraph G) {
	for(int i = 0; i < G.vexnum; ++i) {
		for(int j = 0; j < G.vexnum; ++j) {
			cout<<G.arcs[i][j];
			cout<<" ";
		}
		printf("\n");
	}	
}

int main() {
	AMGraph LG;
	CreateUDM(LG);
	PrintGraph(LG);
}

// 输入举例：
// 5 6 
// A B C D E
// A B 1
// A D 1
// B C 1
// B E 1
// C E 1
// C D 1
// 结果入书上 P154 将 32747 改成 0 即可 
