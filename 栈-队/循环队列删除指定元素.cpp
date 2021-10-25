#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define MAXSIZE 100

typedef struct numStack{
	int data;
	struct numStack *next;
}numStack,*linkNum;

//3.循环队列实现栈指定删除
//循环队列
typedef struct Queue{
	int *base;
	int front;
	int rear;
}Queue;


//初始化
void initStackNum(linkNum &l){
	l=NULL;
}

//入栈
void pushNum(linkNum &l,int e){
	linkNum p;
	p=(numStack *)malloc(sizeof(numStack));
	p->next=l;
	p->data=e;
	l=p;
}

//出栈
int popNum(linkNum &l){}

//取栈顶元素
int getTopNum(linkNum &l){
	return l->data;
}

//初始化
void initQueue(Queue &q){
	int arr[MAXSIZE];
	q.base=arr;
	q.front=q.rear=0;
}

//入队
void enqueue(Queue &q,int e){
	// 先判断队满：	
	if((q.rear+1)%MAXSIZE==q.front ){
		printf("队满");
		return;
	}
	q.base[q.rear]=e;
	q.rear=(q.rear+1)%MAXSIZE;
}
//出队
void dequeue(Queue &q,int &e){
	// 队空：	
	if(q.rear==q.front){
		printf("队空");
		return ;
	}
	e=q.base[q.front];
	q.front=(q.front+1)%MAXSIZE;
}

void deleteStackWithQueue(){
	linkNum l1;
	int n,e,m,n1,n2;
	initStackNum(l1);
	printf("请输入元素个数:\n");
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		std::cin>>e;
		pushNum(l1,e);
	}
	//创建队列
	Queue p;
	initQueue(p);
	printf("请输入想要删除的元素m:\n");
	scanf("%d",&m);
	for(int j=0;j<n;j++){
		if(getTopNum(l1)==m){
			popNum(l1);
			continue;
		}
		n1=popNum(l1);
		enqueue(p,n1);
	}
	printf("删除后的元素为:\n");
	while(p.rear!=p.front){
		dequeue(p,n2);
		printf("%d ",n2);
	}
}



 
int main(){
	deleteStackWithQueue();
	return 0;
}
