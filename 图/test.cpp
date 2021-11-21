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
	cout<<G.vertices[v].data;
	visited[v] = true;
	p = G.vertices[v].firstarc;
	while(p != NULL) {
		w = p->adjvex;
		if (!visited[w]) {
			DFS_AL(G, w);
		}
		p = p->nextarc;
	}
	// �ҳ����нڵ㣬����ýڵ�Ҳû����ȣ���Ӹýڵ��ٱ���һ��	
	for(int i = 0; i < allNum; ++i) {
		if (!visited[i]) {
			DFS_AL (G, i);
		}
	}
}


void DFS(ALGraph G,int v,int visited[])
{
 int w;
 ArcNode *p;
 cout<<G.vertices[v].data<<"->";//���ʵ�v+1�����㣻
 visited[v]=1;
 p=G.vertices[v].firstarc;
 if(p!=NULL)
 w=p->adjvex;//w��v����һ���ڽӵ��λ�ã�����v+1���������һ�������ǵ�w+1�����㣻
 if (p!=NULL)//������ڽӵ�w
 {
  if(visited[w]==0)//���wû���ʹ�
  {
   DFS(G,w,visited);
  }
  else//�����ʹ��������v����һ���ڽӵ㣬���������ж��Ƿ���ڸ��ڽӵ�
  {
   p=p->nextarc;//G.vertices[v].firstarc=G.vertices[v].firstarc->nextarc;
   if(p!=NULL) w=p->adjvex;//w=G.vertices[v].firstarc->adjex;
  }
 }
}

void DFSTraverse(ALGraph G)
{
 
 int v,visted[100];
 for (v=0;v<G.vexnum;v++)
 {
  visted[v]=0;
 }
 for (v=0;v<G.vexnum;v++)
 {
  if(visted[v]==0)
   DFS(G,v,visted);
 }
}




bool visited_B[MVNum];
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
void BFS_AL(ALGraph G,int k){
	int i;
//	SqQueue Q; 
	ArcNode *p;
	p=new ArcNode;
	InitQueue(Q);
	printf("%c",G.vertices[k].data);
	visited_B[k]=1;
	EnQueue(Q,k);
	while(QueueEmpty(Q)==0){
		DeQueue(Q,i);
		p=G.vertices[i].firstarc;
		while(p!=NULL){
			if(visited_B[p->adjvex]==0){
				printf("%3c",G.vertices[p->adjvex].data);
				visited_B[p->adjvex]=1;
				EnQueue(Q,p->adjvex);
			}
			p=p->nextarc;
		}
	}
	
	for(int i = 0; i < allNum; ++i) {
		if (!visited_B[i]) {
			BFS_AL(G, i);
		}
	}
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
	// ��������������ŵ����	
	int startDFSDot;
	cout<<"����������ŵ�����Ŀ�ʼ��\n";
	cin>>startDFSDot;
	DFS_AL(LG, startDFSDot);
	DFSTraverse(LG); 
	cout<<"\n";
	// ���������й�����ȱ���	
	int startBFSDot;
	cout<<"�����������ȱ����Ŀ�ʼ��\n";
	cin>>startBFSDot;
	BFS_AL(LG, startBFSDot);
	cout<<"\n";
	cout<<"��������Ľ���ǣ�\n"; 
	// ��ͼ������������	
	TopoSort(LG);
}
 
