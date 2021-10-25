#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define MAXSIZE 50
typedef struct stackNode{
	char data;
	struct stackNode *next;
}stackNode,*linkStack;

//初始化
void initStack(linkStack &l){
	l=NULL;
}

//入栈
void push(linkStack &l,char e){
	linkStack p;
	p=(stackNode *)malloc(sizeof(stackNode));
	p->next=l;
	p->data=e;
	l=p;
}
//出栈
void pop(linkStack &l,char &e){
	if(l==NULL){
		printf("栈空");
		return;
	}
	linkStack p;
	e=l->data;
	p=l;
	l=l->next;
	free(p);
} 
//取栈顶元素
char getTop(linkStack &l){
	return l->data;
}

//1.括号匹配

//括号配对函数
int leftOrRight(char e,linkStack &l){
	switch(e){
		case'{':
		case'[':
		case'(':
			return 1;
		case'}':
			if(getTop(l)=='{')return 0;
		case']':
			if(getTop(l)=='[')return 0;
		case')':
			if(getTop(l)=='(')return 0;
		default:
			return 2;		
	}
}
int maching(){
	linkStack l1;
	char str,e;
	int flag=1;
	initStack(l1);
	std::cin>>str;
	while(str!='#'&&flag){
		if(leftOrRight(str,l1)==1){
			push(l1,str);
		}else if(leftOrRight(str,l1)==0 && l1){
			pop(l1,e);
		}else flag=0;
		std::cin>>str;
	}
	if(l1==NULL &&flag){
		return 1;
	}else{
		return 0;
	}
}

//2.前缀表达式求值
typedef struct numStack{
	int data;
	struct numStack *next;
}numStack,*linkNum;
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
int popNum(linkNum &l){
	int e;
	if(l==NULL){
		printf("栈空");
		return 0.0;
	}
	linkNum p;
	e=l->data;
	p=l;
	l=l->next;
	free(p);
	return e;
} 
//取栈顶元素
int getTopNum(linkNum &l){
	return l->data;
}
 
int prefixNum(){
	char str[30];
	int n,n1=0,n2=0;
	char *p=str,*s=str;
	linkNum l2;
	initStackNum(l2);
	printf("请输入开头结尾都带#的前缀表达式:\n");
	scanf("%s",str);
	//倒序 
	while(*p!='#'){
		p++;
	}
	s--; 
	//从右往左扫描 
	while(p!=s){
		if(*p>='0'&&*p<='9'){
			n=*p-'0';
			pushNum(l2,n);
			//printf("%.1f\n",l2->data);
		}else{
			if(*p=='+'){
				n1=popNum(l2);
				//printf("n1: %f\n",n1);
				n2=popNum(l2);
				//printf("n2: %f\n",n2);
				n1=n1+n2;
				pushNum(l2,n1);
				//printf("n1: %f\n",getTopNum(l2));
			}else if(*p=='-'){
				n1=popNum(l2);
				n2=popNum(l2);
				n1=n1-n2;
				pushNum(l2,n1);
			}else if(*p=='*'){
				n1=popNum(l2);
				n2=popNum(l2);
				n1=n1*n2;
				pushNum(l2,n1);
			}else if(*p=='/'){
				n1=popNum(l2);
				n2=popNum(l2);
				n1=n1/n2;
				pushNum(l2,n1);
			}
		}
		
		p--;
	}
	if(l2->next==NULL){
		n1=getTopNum(l2);
	}
	return n1;
}

//3.循环队列实现栈指定删除
//循环队列
typedef struct Queue{
	int *base;
	int front;
	int rear;
}Queue;

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
	int m;
	printf("请输入括号组:\n");
	if(maching()){
		printf("括号匹配成功");
	}else{
		printf("括号匹配失败");
	}
	printf("\n");
	m=prefixNum();
	printf("前缀表达式求值结果为：%d",m);
	deleteStackWithQueue();
	return 0;
}
