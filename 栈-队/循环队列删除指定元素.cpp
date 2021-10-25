#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define MAXSIZE 100

typedef struct numStack{
	int data;
	struct numStack *next;
}numStack,*linkNum;

//3.ѭ������ʵ��ջָ��ɾ��
//ѭ������
typedef struct Queue{
	int *base;
	int front;
	int rear;
}Queue;


//��ʼ��
void initStackNum(linkNum &l){
	l=NULL;
}

//��ջ
void pushNum(linkNum &l,int e){
	linkNum p;
	p=(numStack *)malloc(sizeof(numStack));
	p->next=l;
	p->data=e;
	l=p;
}

//��ջ
int popNum(linkNum &l){}

//ȡջ��Ԫ��
int getTopNum(linkNum &l){
	return l->data;
}

//��ʼ��
void initQueue(Queue &q){
	int arr[MAXSIZE];
	q.base=arr;
	q.front=q.rear=0;
}

//���
void enqueue(Queue &q,int e){
	// ���ж϶�����	
	if((q.rear+1)%MAXSIZE==q.front ){
		printf("����");
		return;
	}
	q.base[q.rear]=e;
	q.rear=(q.rear+1)%MAXSIZE;
}
//����
void dequeue(Queue &q,int &e){
	// �ӿգ�	
	if(q.rear==q.front){
		printf("�ӿ�");
		return ;
	}
	e=q.base[q.front];
	q.front=(q.front+1)%MAXSIZE;
}

void deleteStackWithQueue(){
	linkNum l1;
	int n,e,m,n1,n2;
	initStackNum(l1);
	printf("������Ԫ�ظ���:\n");
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		std::cin>>e;
		pushNum(l1,e);
	}
	//��������
	Queue p;
	initQueue(p);
	printf("��������Ҫɾ����Ԫ��m:\n");
	scanf("%d",&m);
	for(int j=0;j<n;j++){
		if(getTopNum(l1)==m){
			popNum(l1);
			continue;
		}
		n1=popNum(l1);
		enqueue(p,n1);
	}
	printf("ɾ�����Ԫ��Ϊ:\n");
	while(p.rear!=p.front){
		dequeue(p,n2);
		printf("%d ",n2);
	}
}



 
int main(){
	deleteStackWithQueue();
	return 0;
}
