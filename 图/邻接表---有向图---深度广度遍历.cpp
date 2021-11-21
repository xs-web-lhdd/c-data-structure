#include<bits/stdc++.h>

using namespace std;

// ��󶥵��� 
#define MVNum 100
typedef char VerTexType;
typedef int OtherInfo;

// �߽ڵ����ͣ� 
typedef struct ArcNode
{
	// �ñ���ָ��Ķ����λ��	
	int adjvex;
	// ָ����һ���ߵ�ָ��
	struct ArcNode * nextarc;
	// �ͱ���ص���Ϣ
	OtherInfo info;	 
} ArcNode;

// �������ͣ� 
typedef struct VNode
{
	// ������������Ŷ���������磺A B	
	VerTexType data;
	// ָ���һ�������ö���ıߵ�ָ��	
	ArcNode *firstarc; 
} VNode, AdjList[MVNum];

// �ڽӱ� 
typedef struct
{
	AdjList vertices;
	// ������������ 
	int  vexnum, arcnum;
} ALGraph; 


// ȥ�������±꣺ 
int LocateVex(ALGraph G, VerTexType V)
{
	for(int i = 0; i < G.vexnum; ++i) {
		if (G.vertices[i].data == V) {
			return i;
		}
	}
	// �ҵ��˷����±꣬�Ҳ������� -1�����������Ҳ���	
	return -1;
}


// ��ӡ�ڽӱ�---����ͼ��
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



// ��������ͼ��
int CreateUDG(ALGraph &G)
{
	printf("������ͼ�Ķ������ͱ���\n");
	cin>>G.vexnum>>G.arcnum;
	cout<<"���������ζ����ֵ\n";
	for(int i = 0; i < G.vexnum; ++i) {
		cin>>G.vertices[i].data;
		// ���������ָ������Ϊ��
		G.vertices[i].firstarc=NULL;
	}
	
	
	// �ɱ��γɵ����ɸ������� 
	for(int k = 0; k < G.arcnum; ++k) {
		VerTexType v1, v2;
		int i, j;
		ArcNode *p1, *p2; 
		cout<<"������ߵ���ʼ�ڵ��ĩβ�ڵ�\n";
		cin>>v1>>v2;
		// �ҳ� v1��v2 �� G.vertices �е��±ꣻ		
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);

		// ����ͷ�巨---���ڵ���뵽��������		
		p1 = new ArcNode;
		p1->adjvex = j;
		p1->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p1; 
	
	}
	return 1;
}


// �ڽӱ��ʾͼ��������ȱ����� 
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


//--------ջ---------
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

//��ʼ��ջ
void InitStack(LinkStack &S){
    S=NULL;
}
//��ջ
void Push(LinkStack &S,int e){
    p1=new StackNode;
    p1->data=e;
    p1->next=S;
    S=p1;
}
//��ջ
void Pop(LinkStack &S,int &e){
    if(S==NULL) return ;
    e=S->data;
    S=S->next;
}
//�ж�ջ�Ƿ�Ϊ��
bool StackEmpty(LinkStack S){
    return S==NULL;
}

//void FindInDegree(ALGraph G, int []) {
//	
//}


// ��������
int TopologicalSort(ALGraph G, int topo[])
{
	// �ҳ����������ȴ�ŵ� indegree ��	
	FindInDegree(G, indegree);
	// ջ S ��ʼ��Ϊ��	
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
	//	�л�·���� -1��û�з��� 0	
		return -1;
	} else {
		return 0;
	}
}  



int main() {
	// ����һ��ͼ��	
	ALGraph LG;
	CreateUDG(LG);
	PrintUDG(LG);
	int startDot;
	cout<<"����������ŵ�����Ŀ�ʼ��\n";
	cin>>startDot;
	DFS_AL(LG , startDot);
}
 
