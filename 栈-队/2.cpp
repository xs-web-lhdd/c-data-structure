#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 100
#define OK 1
#define ERROR -1
#define MAX 1000
typedef char ElemType;
typedef int Elem;
typedef int Status;

//����ջ
typedef struct stack{
	ElemType data;
	stack *next;
}Node,*LStack; 

//ջ�ĳ�ʼ�� 
Status InitStack(LStack &s){
	s = NULL;
	return OK;
}
//���Ԫ�� 
Status push(LStack &s,ElemType e){
	LStack p;
	p = new Node;
	p->data = e;
	p->next = s;
	s = p;
	return OK;
}
//ȡ��Ԫ�� 
Status pop(LStack &s,ElemType &e){
	if(s == NULL){
		printf("ջ����");
		return ERROR;
	} 
	LStack p;
	p = s;
	e = s->data;
	s = s->next;
	delete p;
	return OK;
}
//��ȡջ��Ԫ�� 
ElemType getTop(LStack s){
	if(s != NULL){
		return s->data;
	}
}
//�ж�ջ�Ƿ�Ϊ�� 
Status StackEmpty(LStack s){
	if(s == NULL){
		return 1;
	}
	return 0;
}
//��ʾջ������Ԫ�� 
Status list(LStack s){
	printf("��ǰջ��Ԫ��Ϊ��");
	while(s != NULL){
		printf("%d ",s->data);
		s = s->next;
	}
	printf("\n");
}

//�㷨һ������ƥ��
bool Matching(char str[]){
	LStack s;
	InitStack(s);
	char x;
	int flag = 1;
	for(int i = 0;i < strlen(str);i++){
		switch(str[i]){
			case '[':
			case '(':
				push(s,str[i]);
				break;
			case ')':
				if(!StackEmpty(s) && getTop(s) == '(')
				   pop(s,x);
				else flag = 0;
				break;
				
			case ']':
				if(!StackEmpty(s) && getTop(s) == '[')
				   pop(s,x);
				else flag = 0;
				break;
		}
	}
	if(StackEmpty(s) && flag) return true;
	else return false;
	
} 


//�㷨�� 
//�ж��ǲ�������(��λ��)�����λ����Ҫ�õ�������ʽ��

typedef struct stack1{
	Elem data;
	stack1 *next;
}Node1,*LStack1; 
Status InitStack1(LStack1 &s){
	s = NULL;
	return OK;
}
Status push1(LStack1 &s,Elem e){
	LStack1 p;
	p = new Node1;
	p->data = e;
	p->next = s;
	s = p;
	return OK;
}
Status pop1(LStack1 &s,Elem &e){
	if(s == NULL){
		printf("ջ����");
		return ERROR;
	} 
	LStack1 p;
	p = s;
	e = s->data;
	s = s->next;
	delete p;
	return OK;
}

//�ж�ĳ���ַ��Ƿ�Ϊ���� 
bool Digit(char a){
	if(a >= '0'&& a <= '9'){
		return true;
	}
	return false;
} 
//ǰ׺���ʽ��ֵ�� 
int calculator(char s[]){
	LStack1 s2; //s2����ջ 
	InitStack1(s2);
	for(int i = strlen(s) - 1;i >= 0;i--){
		if(Digit(s[i])){  // ��������֣�ֱ��ѹ����ջ�� 
			push1(s2,s[i]-'0'); 
		}else{
			int num1,num2; 
			pop1(s2,num1);
			pop1(s2,num2);
			int res;
			if(s[i] == '+'){
				res = num1 + num2;
			}else if(s[i] == '-'){
				res = num1 - num2;
			}else if(s[i] == '*'){
				res = num1 * num2;
			}else if(s[i] == '/'){
				res = num1 / num2;
			}else{
				printf("�������������");
				return ERROR;
			}
			push1(s2,res);
		}
		
	}
	int x;
	pop1(s2,x);
	return x;
}
//��׺���ʽ��ֵ�� 
int calculator1(char s[]){
	LStack1 s2; //s2����ջ 
	InitStack1(s2);
	for(int i = 0;i < strlen(s);i++){
		if(Digit(s[i])){  // ��������֣�ֱ��ѹ����ջ�� 
			push1(s2,s[i]-'0'); 
		}else{
			int num1,num2; 
			pop1(s2,num1);
			pop1(s2,num2);
			int res;
			if(s[i] == '+'){
				res = num1 + num2;
			}else if(s[i] == '-'){
				res = num2 - num1;
			}else if(s[i] == '*'){
				res = num1 * num2;
			}else if(s[i] == '/'){
				res = num2 / num1;
			}else{
				printf("�������������");
				return ERROR;
			}
			push1(s2,res);
		}
		
	}
	int x;
	pop1(s2,x);
	return x;
}




//�㷨�� ����ѭ������ʵ�ֽ���ջ�еĸ���ֵɾ����
//����ʵ�� 
 
typedef struct Node2{
	ElemType data;
	Node2 *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue &s){
	s.front = s.rear = new QNode;
	s.front->next = NULL;
	return OK;
}
//��� 
Status EnQueue(LinkQueue &s,ElemType e)
{
	QueuePtr p;	//����һ�����
	p=(QNode*)malloc(sizeof(QNode));//Ϊ������ռ�
	p->data=e;//�½��������������e
	p->next=NULL;//��Ϊ�ڶ�β��ӣ��½��p����Ҫָ�����ָ����Ϊ��
	s.rear->next=p;//��βָ��ָ���½��p
	s.rear = p;//ʹ�½��pΪ��β���
	return OK;
}

//ȡ��ͷԪ�� 
Status getHead(LinkQueue &s){
	if(s.front != s.rear){
		return s.front->data;
	}
	else {
		printf("���пգ�");
		return ERROR;
	}
}
//���� 
Status deleteQueue(LinkQueue &s,ElemType &e){
	QueuePtr q;
	if(s.front == s.rear){
		printf("���пգ�");
		return ERROR;
	}
	q = s.front->next;
	e = q->data;
	s.front->next = q->next;
	if(s.rear == q) s.rear = s.front;
	free(q);
	return OK;
	//s.front = s.front->next;
}
//�ж϶����Ƿ�Ϊ�� 
Status Empty_LQueue(LinkQueue s)
{
	if(s.rear == s.front)
		return true;
	else
		return false;
}

//��ʼ��ջ 
Status initstack3(LStack &s){
	InitStack(s);
	int n;
	printf("�������������Ԫ�أ�\n");
	scanf("%d",&n);
	printf("���%d��Ԫ��\n",n);
	for(int i = 0;i < n;i++){
		int e;
		printf("�������%d��Ԫ��\n",i + 1);
		scanf("%d",&e);
		push(s,e);
	} 
	list(s); 
	return OK;
	
}
//���ö���ɾ��ջ��ָ��Ԫ�� 
void delstackelem(LStack &s,ElemType e){
 	ElemType elem,data,temp;
	LinkQueue q;
	InitQueue(q);
 	while(!StackEmpty(s)){
 		elem = getTop(s);
 		if(elem != e){
 			EnQueue(q,elem);
 			pop(s,temp);
		 }else{
		 	pop(s,temp);
		 }
	 }
	 //list(s);
	 int arr[1000],i = 0;
	 while(!Empty_LQueue(q)){
	 	deleteQueue(q,data);
	 	//printf("%d",data); 
	 	arr[i++] = data;
	 }
	 while(i!=0){
	 	push(s,arr[--i]);
	}
	 printf("�ɹ�ɾ��Ԫ��%d\n",e);
	 list(s);
	 
	 
} 


void  Main(){
	bool flag = 1; 
	while(flag){
	printf("\t\t��ѡ���㷨��1,����ƥ��\t\t\n");
	printf("\t\t            2,������  \t\t\n");
	printf("\t\t            3,ɾ��ջ��Ԫ��\t\t\n");
	printf("\t\t            4,����-1�˳�\t\t\n");
	int x,y,res;
	char str[MAXSIZE];
	scanf("%d",&x);
	switch(x){
		case 1:
			printf("�������ƥ������ţ�");
			scanf("%s",str);
			y = Matching(str);
			if(y){
				printf("ƥ��ɹ�\n");
			}else{
				printf("ƥ��ʧ��\n");
			}
			break;
		case 2:
			printf("���������ı��ʽ��ǰ׺����");
			scanf("%s",str);
			res = calculator(str);
			printf("���Ϊ%d\n",res);
			break;
		case 3:
			LStack s;
			initstack3(s);
			printf("������Ҫɾ����Ԫ�أ�\n");
			int e;
			scanf("%d",&e);
			delstackelem(s,e);
			break;
		case -1:
			flag = 0;	
		}
	}
		
}
int main(){
	Main();
	return 0;
	
}

