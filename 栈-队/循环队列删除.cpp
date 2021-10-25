#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define MAXQSIZE 100
typedef int Status;
typedef int QElemType;
typedef struct {
	int *base;
	int front;
	int rear;
} SqQueue;

Status InitQueue(SqQueue &Q) {
	Q.base=(QElemType*)malloc(MAXQSIZE*sizeof(QElemType));
	if(!Q.base)  return ERROR;
	Q.front=Q.rear=0;
	return 0;
}

Status QueueLength(SqQueue &Q) {
	int length;
	length=(Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
	return length;
}

Status EnQueue(SqQueue &Q,QElemType e) {
	if((Q.rear+1)%MAXQSIZE==Q.front) return ERROR;
	Q.base[(Q.rear)]=e;
	Q.rear=(Q.rear+1)%MAXQSIZE;
	return 0;
}

Status DeQueue(SqQueue &Q) {
	int e,test;
	if(Q.front==Q.rear) return ERROR;
	test=Q.front;
	e=Q.base[Q.front];
	Q.front=(Q.front+1) % MAXQSIZE;
	return e;
}

int JudgeEmpty(SqQueue &Q) {
	if(Q.front==Q.rear) 
	return 1;
	return 0;
}

void DstoryQueue(SqQueue &Q) { //销毁
	while ( Q.front!= Q.rear) {
		free(&Q.base[Q.front]);
		Q.front=(Q.front+1)%MAXQSIZE;
	}
}

void  ClearQueue(SqQueue &Q) { //清空
	int i=Q.front;
	while (i != Q.rear) {
		i=0;
		i++;
	}
	Q.front=Q.rear=0;
}

Status GetHead(SqQueue &Q) { //取首元素
	QElemType e;
	if(Q.front==Q.rear)
		return ERROR;
	return e=Q.base[Q.front];
}

void QueueTraver(SqQueue &Q) {
	int i=Q.front;
	while (i!=Q.rear) {
		printf("%5d",Q.base[i]);
		i++;
	}
}
void CreatQueue(SqQueue &Q) {
	int n;
	printf("请输入循环队列的长度：");
	scanf("%d",&n);
	for (int i = 1; i <=n; i++) {
		printf("第%d个元素为：",i);
		scanf("%d",&Q.base[Q.rear]);
		Q.rear=(Q.rear+1)%MAXQSIZE;
	}
}

int main()
{   int a;
    SqQueue Q;
	InitQueue(Q);//初始化调试
	printf("准备测试队列操作....\n\n");
	CreatQueue(Q);//创建循环队列
	printf("\n\n");
	printf("队列长度为:%d", QueueLength(Q));//求队长
	printf("\n\n");
	if(JudgeEmpty(Q) == 0)
	printf("队列不空！");
	else printf("队列为空！");
	printf("\n\n队列中的元素为：");
	QueueTraver(Q);//遍历调试
	printf("\n\n");
	printf("首元素为：%d", GetHead(Q));//取首元素
	printf("\n\n");printf("删除队头元素：%d", DeQueue(Q));//删除
	printf("\n\n剩下元素为：");
	QueueTraver(Q);//遍历调试

}

