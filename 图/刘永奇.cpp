#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
#define MVNum 100
#define ERROR 0
#define OK 1
#define OVERFLOW -1
typedef int Status;

//�߽�� 
typedef struct ArcNode{
	int adjvex;
	struct ArcNode *nextarc;//ָ����һ���ߵ�ָ�� 
}ArcNode,*Arc;

//������Ϣ 
typedef struct VNode{
	char data;
	int indegree;
	ArcNode *firstarc;		//ָ���һ����������ıߵ�ָ�� 
}VNode,AdjList[MVNum];		//AdjList ��ʾ�ڽӱ����� 

typedef struct{    			//�ڽӱ� 
	AdjList vertices;
	int vexnum,arcnum;		//ͼ�ĵ�ǰ�������ͱ��� 
}Graph;

//��ѯc��G��λ�ã����ظ�λ�õ��±� 
int LocateVex(Graph G,char c){
	int i;
	for(i=0;i<G.vexnum;i++)
		if(G.vertices[i].data==c)
			return i;
}

//�ڽӱ����Ϣ 
void print(Graph G){
	int i;
	Arc p;p=new ArcNode;
	printf("ͼ���ڽӱ�");
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

//�����ڽӱ��ʾ������������ͼ 
Status CreatDG(Graph &G){
	int i,j,k;
	char c1,c2;
	printf("������(���ûس�����) ");
	scanf("%d",&G.vexnum);		//�����ܶ�����
	printf("�� ��	");
	scanf("%d",&G.arcnum);		//�����ܱ���
	printf("�������\n");
	getchar();
	for(i=0;i<G.vexnum;++i){		//������� 
		scanf("%c",&G.vertices[i].data);		//���붥��ֵ 
		G.vertices[i].indegree=0;			//��ʼ�����Ϊ0 
		G.vertices[i].firstarc=NULL; 		//��ʼ����ͷ����ָ����ΪNULL 
	}
	printf("����������\n");
	for(k=0;k<G.arcnum;k++){
		getchar(); 
		printf("��%d���ߵ����˵��±�",k+1);
		scanf("%c%c",&c1,&c2);		//���������,c1ָ��c2 
		i=LocateVex(G,c1); j=LocateVex(G,c2);
		//ȷ��v1��v2��G��λ��,��������G.vertices�е����
		Arc p1;
		p1=new ArcNode; 
		p1->adjvex=j;
		p1->nextarc=G.vertices[i].firstarc;
		G.vertices[i].firstarc=p1;	//���½��*p1���붥��v1�ı߱�ͷ�� 
		G.vertices[j].indegree++;	//v2���+1 
	}
	return OK;
}

//����v�ĵ�һ���ڽӵ���±�,���ڽӵ㷵��-1
int FirstAdjVex(Graph G,int v){
	if(!G.vertices[v].firstarc)
		return G.vertices[v].firstarc->adjvex;
	else return -1;
}

//����v�����w����һ���ڽӵ���±�,û���򷵻�-1 
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

int visited[MVNum];				//���ʱ�־���飬��ֵΪ"false"

//�����ڽӱ��ʾͼ��������ȱ���
void DFS(Graph G,int v){		//�ӵ�v�������������ȱ���ͼG 
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

//�������������������ͨͼ 
void DFSTraverse(Graph G){
	int v;char c;
	for(v=0;v<G.vexnum;v++) visited[v]=0;//���ʱ�־�����ʼ�� 
	getchar();
	printf("���ĸ��㿪ʼ������ȱ���");
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
	printf("\n���ĸ��㿪ʼ������ȱ���");
	scanf("%c",&c);
	v=LocateVex(G,c);
	BFS(G,v);
	for(v=0;v<G.vexnum;v++)
		if(!visited[v]) BFS(G,v);
}

typedef struct{//����˳��ջ
    int *base;
    int *top;
    int stacksize;
}SqStack;


Status Push(SqStack &S,int e)//��ջ
{
    if(S.top-S.base == S.stacksize)  //�ж�ջ��
        return ERROR;
    *S.top++ = e;                    //Ԫ��eѹ��ջ����ջ��ָ������һλ;
    return OK;
 }
Status Pop(SqStack &S, int &e){//��ջ
    if(S.top == S.base)   return ERROR;
    e = *--S.top;
    return OK;
}

void GetTop(SqStack S,int &e){//ȡջ��Ԫ��
    if(S.top != S.base)
	e=*(S.top - 1);
}

Status StackEmpty(SqStack S){//�ж�ջ�� 
    if(S.top - S.base == 0)    return OK;
    else return ERROR;
}

Status InitStack(SqStack &S){//����˳��ջ 
    S.base =new int[MAXSIZE];
    if(!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}

//�������� 
Status TopologicalSort(Graph G){
	printf("\n��������\n");
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
	if(!x) printf("����ͼ�л�·");
	printf("\n");
	system("pause");
	return 0;
}
