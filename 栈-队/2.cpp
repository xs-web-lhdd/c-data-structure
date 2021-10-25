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

//链性栈
typedef struct stack{
	ElemType data;
	stack *next;
}Node,*LStack; 

//栈的初始化 
Status InitStack(LStack &s){
	s = NULL;
	return OK;
}
//添加元素 
Status push(LStack &s,ElemType e){
	LStack p;
	p = new Node;
	p->data = e;
	p->next = s;
	s = p;
	return OK;
}
//取出元素 
Status pop(LStack &s,ElemType &e){
	if(s == NULL){
		printf("栈空了");
		return ERROR;
	} 
	LStack p;
	p = s;
	e = s->data;
	s = s->next;
	delete p;
	return OK;
}
//获取栈顶元素 
ElemType getTop(LStack s){
	if(s != NULL){
		return s->data;
	}
}
//判断栈是否为空 
Status StackEmpty(LStack s){
	if(s == NULL){
		return 1;
	}
	return 0;
}
//显示栈中所有元素 
Status list(LStack s){
	printf("当前栈中元素为：");
	while(s != NULL){
		printf("%d ",s->data);
		s = s->next;
	}
	printf("\n");
}

//算法一：括号匹配
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


//算法二 
//判断是不是数字(个位数)，如果位数多要用到正则表达式。

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
		printf("栈空了");
		return ERROR;
	} 
	LStack1 p;
	p = s;
	e = s->data;
	s = s->next;
	delete p;
	return OK;
}

//判断某个字符是否为数字 
bool Digit(char a){
	if(a >= '0'&& a <= '9'){
		return true;
	}
	return false;
} 
//前缀表达式求值。 
int calculator(char s[]){
	LStack1 s2; //s2数字栈 
	InitStack1(s2);
	for(int i = strlen(s) - 1;i >= 0;i--){
		if(Digit(s[i])){  // 如果是数字，直接压如数栈。 
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
				printf("运算符输入有误！");
				return ERROR;
			}
			push1(s2,res);
		}
		
	}
	int x;
	pop1(s2,x);
	return x;
}
//后缀表达式求值。 
int calculator1(char s[]){
	LStack1 s2; //s2数字栈 
	InitStack1(s2);
	for(int i = 0;i < strlen(s);i++){
		if(Digit(s[i])){  // 如果是数字，直接压如数栈。 
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
				printf("运算符输入有误！");
				return ERROR;
			}
			push1(s2,res);
		}
		
	}
	int x;
	pop1(s2,x);
	return x;
}




//算法三 借助循环队列实现将堆栈中的给定值删除。
//链队实现 
 
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
//入队 
Status EnQueue(LinkQueue &s,ElemType e)
{
	QueuePtr p;	//定义一个结点
	p=(QNode*)malloc(sizeof(QNode));//为结点分配空间
	p->data=e;//新结点数据域存放数据e
	p->next=NULL;//因为在队尾入队，新结点p不需要指向哪里，指针域为空
	s.rear->next=p;//将尾指针指向新结点p
	s.rear = p;//使新结点p为队尾结点
	return OK;
}

//取队头元素 
Status getHead(LinkQueue &s){
	if(s.front != s.rear){
		return s.front->data;
	}
	else {
		printf("队列空！");
		return ERROR;
	}
}
//出队 
Status deleteQueue(LinkQueue &s,ElemType &e){
	QueuePtr q;
	if(s.front == s.rear){
		printf("队列空！");
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
//判断队列是否为空 
Status Empty_LQueue(LinkQueue s)
{
	if(s.rear == s.front)
		return true;
	else
		return false;
}

//初始化栈 
Status initstack3(LStack &s){
	InitStack(s);
	int n;
	printf("请向链表中添加元素！\n");
	scanf("%d",&n);
	printf("添加%d个元素\n",n);
	for(int i = 0;i < n;i++){
		int e;
		printf("请输入第%d个元素\n",i + 1);
		scanf("%d",&e);
		push(s,e);
	} 
	list(s); 
	return OK;
	
}
//利用队列删除栈中指定元素 
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
	 printf("成功删除元素%d\n",e);
	 list(s);
	 
	 
} 


void  Main(){
	bool flag = 1; 
	while(flag){
	printf("\t\t请选择算法：1,括号匹配\t\t\n");
	printf("\t\t            2,计算器  \t\t\n");
	printf("\t\t            3,删除栈中元素\t\t\n");
	printf("\t\t            4,输入-1退出\t\t\n");
	int x,y,res;
	char str[MAXSIZE];
	scanf("%d",&x);
	switch(x){
		case 1:
			printf("请输入待匹配的括号：");
			scanf("%s",str);
			y = Matching(str);
			if(y){
				printf("匹配成功\n");
			}else{
				printf("匹配失败\n");
			}
			break;
		case 2:
			printf("请输入计算的表达式（前缀）：");
			scanf("%s",str);
			res = calculator(str);
			printf("结果为%d\n",res);
			break;
		case 3:
			LStack s;
			initstack3(s);
			printf("请输入要删除的元素！\n");
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

