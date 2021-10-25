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

void DstoryQueue(SqQueue &Q) { //����
	while ( Q.front!= Q.rear) {
		free(&Q.base[Q.front]);
		Q.front=(Q.front+1)%MAXQSIZE;
	}
}

void  ClearQueue(SqQueue &Q) { //���
	int i=Q.front;
	while (i != Q.rear) {
		i=0;
		i++;
	}
	Q.front=Q.rear=0;
}

Status GetHead(SqQueue &Q) { //ȡ��Ԫ��
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
	printf("������ѭ�����еĳ��ȣ�");
	scanf("%d",&n);
	for (int i = 1; i <=n; i++) {
		printf("��%d��Ԫ��Ϊ��",i);
		scanf("%d",&Q.base[Q.rear]);
		Q.rear=(Q.rear+1)%MAXQSIZE;
	}
}

int main()
{   int a;
    SqQueue Q;
	InitQueue(Q);//��ʼ������
	printf("׼�����Զ��в���....\n\n");
	CreatQueue(Q);//����ѭ������
	printf("\n\n");
	printf("���г���Ϊ:%d", QueueLength(Q));//��ӳ�
	printf("\n\n");
	if(JudgeEmpty(Q) == 0)
	printf("���в��գ�");
	else printf("����Ϊ�գ�");
	printf("\n\n�����е�Ԫ��Ϊ��");
	QueueTraver(Q);//��������
	printf("\n\n");
	printf("��Ԫ��Ϊ��%d", GetHead(Q));//ȡ��Ԫ��
	printf("\n\n");printf("ɾ����ͷԪ�أ�%d", DeQueue(Q));//ɾ��
	printf("\n\nʣ��Ԫ��Ϊ��");
	QueueTraver(Q);//��������

}

