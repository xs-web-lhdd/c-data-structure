#include<bits/stdc++.h>

using namespace std;

#define MAXSIZE 100
// ��󶥵��� 
#define MVNum 100
typedef char VerTexType;
typedef int OtherInfo;

// ����һ��ȫ�ֱ��� --- ��¼������� 
int allNum; 

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
	// �������	
	int indegree;
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
	allNum=G.vexnum;
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
		cout<<"�������"<<k+1<<"�ߵ���ʼ�ڵ��ĩβ�ڵ�\n";
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


//// �ڽӱ��ʾͼ��������ȱ����� 
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
//	// �ҳ����нڵ㣬����ýڵ�Ҳû����ȣ���Ӹýڵ��ٱ���һ��	
//	for(int i = 0; i < allNum; ++i) {
//		if (!visited[i]) {
//			DFS_AL (G, i);
//		}
//	}
//}



//�����ڽӱ��ʾͼ��������ȱ���
void DFS_AL(ALGraph G,int v){		//�ӵ�v�������������ȱ���ͼG 
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

//�������������������ͨͼ 
void DFSTraverse(ALGraph G){
	int v;
	char c;
	for(v=0;v<G.vexnum;v++) visited[v]=0;//���ʱ�־�����ʼ�� 
	cout<<"������������ȱ����Ŀ�ʼ�㣺\n";
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

//��ʼ������ 
int InitQueue(SqQueue &Q){
	Q.base=(int*)malloc(MAXSIZE*sizeof(int));
	if(!Q.base) return 0;
	Q.rear=Q.front;
}

//��� 
int EnQueue(SqQueue &Q,int e){
	if((Q.rear+1)%MAXSIZE==Q.front) return 0;
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXSIZE;
	return 1;
}

//���� 
int DeQueue(SqQueue &Q,int &e){
	if(Q.rear==Q.front) return 0;
	e=Q.base[Q.front];
	Q.front=(Q.front+1%MAXSIZE);
	return 1;
}

//�ж϶����Ƿ�Ϊ��
int QueueEmpty(SqQueue Q){
	if(Q.rear==Q.front) return 1;
	else return 0;
}

SqQueue Q;
//�����������������ͨͼ 
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
	cout<<"�����������ȱ����Ŀ�ʼ�㣺\n";
	cin>>c;
	v=LocateVex(G,c);
	BFS(G,v);
	for(v=0;v<G.vexnum;v++)
		if(!visited[v]) BFS(G,v);
}



//------------------------------------- ���������������õ������ݽṹ -----------------------------------------------------------

/*˳��ջ�Ķ���*/
#define Stack_Size 100
typedef struct sqStack
{
       int *elem;
       int top;
       int stackSize;//ջ���鳤��
}sqStack;
 
 
/*˳��ջ�ĳ�ʼ��*/
void initStack_Sq(sqStack &S)
{
       S.elem=new int[Stack_Size];
       S.top=-1;
       S.stackSize=Stack_Size;
}
/*��ջ*/
void push(sqStack &S,int x)
{
       if(S.top==Stack_Size-1)
              cout<<"Stack Overflow!";
       S.elem[++S.top]=x;
}
 
/*��ջ*/
int pop(sqStack &S)
{
       int x;
       if(S.top==-1)
              cout<<"Stack Empty!";
       x=S.elem[S.top--];
       return x;
}


//��������
int TopoSort(ALGraph &G)
{
    sqStack S;
    initStack_Sq(S);
    ArcNode *p;
    int count=0;
    int i,j;
    
	// �����е����ȳ�ʼ��Ϊ0    
    for(i=0;i<G.vexnum;i++)
        G.vertices[i].indegree=0;//��ʼ��Ϊ0
        
    for(i=0;i<G.vexnum;i++)
    {//���������������
        p=G.vertices[i].firstarc;
        while(p)
        {
            G.vertices[p->adjvex].indegree++;
            p=p->nextarc;
        }
    }
    
    for(i=0;i<G.vexnum;i++)
        if(G.vertices[i].indegree==0)
            push(S,i);//����Ϊ0�Ķ�����ջ,�����ջ�������Ϊ0�Ķ����������е�λ��
            
    while(S.top!=-1)
    {
        j=pop(S);
        cout<<G.vertices[j].data<<" ";//��ջ����Ԫ�س�ջ��������������Ϊ0�Ķ������
        count++;//��������1
        p=G.vertices[j].firstarc;//��pָ�����Ϊ0�Ķ���ĵ�һ���߱���
        while(p)
        {
            G.vertices[p->adjvex].indegree--;//�����Ϊ0�Ķ�����ڽӵ����ȼ�1
            if(G.vertices[p->adjvex].indegree==0)
                push(S,p->adjvex);//�ȼ�1��Ķ�����������Ϊ0��������ջ
            p=p->nextarc;
        }
    }
    if(count<G.vexnum)
        cout<<"������ͼ�л�·"<<endl;  
	return 0; 
}



int main() {
	// ����һ��ͼ��	
	ALGraph LG;
	// ����һ������ͼ	
	CreateUDG(LG);
	// ��ӡ��������ͼ	
	PrintUDG(LG);
	// ����ŵ����	
	DFSTraverse(LG);
	cout<<"\n";
	// ���������й�����ȱ���	
	BFSTraverse(LG);
	cout<<"\n";
	cout<<"��������Ľ���ǣ�\n"; 
	// ��ͼ������������	
	TopoSort(LG);
}
 
