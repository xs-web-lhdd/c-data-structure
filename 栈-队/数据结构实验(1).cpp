#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define MAXSIZE 50
typedef struct stackNode{
	char data;
	struct stackNode *next;
}stackNode,*linkStack;

//��ʼ��
void initStack(linkStack &l){
	l=NULL;
}

//��ջ
void push(linkStack &l,char e){
	linkStack p;
	p=(stackNode *)malloc(sizeof(stackNode));
	p->next=l;
	p->data=e;
	l=p;
}
//��ջ
void pop(linkStack &l,char &e){
	if(l==NULL){
		printf("ջ��");
		return;
	}
	linkStack p;
	e=l->data;
	p=l;
	l=l->next;
	free(p);
} 
//ȡջ��Ԫ��
char getTop(linkStack &l){
	return l->data;
}

//1.����ƥ��

//������Ժ���
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

//2.ǰ׺���ʽ��ֵ
typedef struct numStack{
	int data;
	struct numStack *next;
}numStack,*linkNum;
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
int popNum(linkNum &l){
	int e;
	if(l==NULL){
		printf("ջ��");
		return 0.0;
	}
	linkNum p;
	e=l->data;
	p=l;
	l=l->next;
	free(p);
	return e;
} 
//ȡջ��Ԫ��
int getTopNum(linkNum &l){
	return l->data;
}
 
int prefixNum(){
	char str[30];
	int n,n1=0,n2=0;
	char *p=str,*s=str;
	linkNum l2;
	initStackNum(l2);
	printf("�����뿪ͷ��β����#��ǰ׺���ʽ:\n");
	scanf("%s",str);
	//���� 
	while(*p!='#'){
		p++;
	}
	s--; 
	//��������ɨ�� 
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

//3.ѭ������ʵ��ջָ��ɾ��
//ѭ������
typedef struct Queue{
	int *base;
	int front;
	int rear;
}Queue;

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
	int m;
	printf("������������:\n");
	if(maching()){
		printf("����ƥ��ɹ�");
	}else{
		printf("����ƥ��ʧ��");
	}
	printf("\n");
	m=prefixNum();
	printf("ǰ׺���ʽ��ֵ���Ϊ��%d",m);
	deleteStackWithQueue();
	return 0;
}
