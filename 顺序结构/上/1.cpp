
////////////////////////////////��̬//////////////////////////////////////////////////////////////////// 
//#include<stdio.h>
//#include<string.h> 
//
//// ����� --- ��ǿ����Ŀ�ά���� 
//#define MAX_SIZE 10
//
//typedef int SQDataType;
//
//struct SeqList {
//	SQDataType a[MAX_SIZE];
//	int size;
//};
//
//// ��һ�� struct �ı��� 
//typedef struct SeqList SL;
//// �ڶ��� struct �ı���
////typedef struct SeqList
////{
////	SQDataType a [N];
////	int size;
////} SL;
//
//// ��ʼ���� 
//void SeqListInit (SL *ps);
//// ��β������
//void SeqListPushBack (SL *ps, SQDataType x);
//// ��ͷ������ 
//void SeqListPushFront (SL *ps, SQDataType x);
//// ͷɾ
//void SeqListPopBack (SL *ps, SQDataType x);
//// βɾ
//void SeqListPopFront (SL *ps, SQDataType x);
//
//// �����
//void SeqListPrint (SL *ps, SQDataType i); 
//
//
//void SeqListInit (SL *ps) {
//	memset(ps->a, 0, sizeof(SQDataType)*MAX_SIZE);
//	ps->size = 0;
//}
//
//void SeqListPushBack (SL *ps, SQDataType x) {
//	if (ps->size == 10) {
//		printf("�㱬ջ��!!!");
//	}
//	ps->a[ps->size] = x;
//	ps->size++;
//}
//
//void SeqListPrint (SL *ps, SQDataType i) {
//	if (i == 10) {
//		return;
//	};
//	printf("%d\n", ps->a[i]);
//}
//
//
//
//
//void TestSeqList () {
//	SL sl;
//	SeqListInit (&sl);
//	SeqListPushBack(&sl, 1);
//	SeqListPushBack(&sl, 1);
//	SeqListPushBack(&sl, 1);
//	SeqListPushBack(&sl, 1);
//	SeqListPushBack(&sl, 1);
//	SeqListPushBack(&sl, 1);
//	SeqListPushBack(&sl, 1);
//	SeqListPushBack(&sl, 1);
//	SeqListPushBack(&sl, 1);
//	SeqListPushBack(&sl, 1);
////	SeqListPushBack(&sl, 1);
////	SeqListPushBack(&sl, 1);
//	int i = 0;
//	while(i <= 10) {
//		SeqListPrint(&sl, i);
//		i++;
//	}
//}
//
//int main() {
//	TestSeqList();
//	return 9;
//};

//////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////��̬////////////////////////////////////////////////////
#include<stdio.h>
#include<string.h>
#include<stdlib.h> 

// ����� --- ��ǿ����Ŀ�ά���� 
#define MAX_SIZE 10

typedef int SQDataType;

struct SeqList {
	SQDataType* a;
	int size;
	int capacity;
};
typedef struct SeqList SL;



// ��ʼ���� 
void SeqListInit (SL *ps);
// ��β������
void SeqListPushBack (SL *ps, SQDataType x);
// ��ͷ������ 
void SeqListPushFront (SL *ps, SQDataType x);
// ͷɾ
void SeqListPopBack (SL *ps, SQDataType x);
// βɾ
void SeqListPopFront (SL *ps, SQDataType x);

// �����
void SeqListPrint (SL *ps, SQDataType i); 


// �Ա���г�ʼ�� 
void SeqListInit (SL *ps) {
	ps->a = NULL;
	ps->size = 0;
	ps->capacity = 0;
}

// ���ݵĺ���
void SeqListCapacity (SL *ps) {
	if (ps->size == ps->capacity) {
		int newCapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
		SQDataType* tmp = (SQDataType*) realloc(ps->a, newCapacity * sizeof(SQDataType));
		if (tmp == NULL) {
			printf("realloc fial\n");
			exit(-1);
		} else
		{	
//			printf("ninini1");
			ps->a = tmp;
			ps->capacity = newCapacity;
		}
	}
}

// β�� 
void SeqListPushBack (SL *ps, SQDataType x) {
	// ���˾�Ҫ���� --- һ��������	

	SeqListCapacity(ps);
	ps->a[ps->size] = x;
	ps->size++;
}

void SeqListPushFront (SL *ps, SQDataType x) {
	SeqListCapacity(ps);
//	1����ʼ����
//  2����������
//  3����������
	int end = ps->size - 1;
	while(end >= 0) {
		ps->a[end+1] = ps->a[end];
		--end;
	}
//	printf("11111\n");
	ps->a[0] = x;
	ps->size++;
}

// ��ӡ 
void SeqListPrint (SL *ps) {
	int i = 0;
	for(i = 0; i < ps->size; i++) {
		printf("%d\n", ps->a[i]);
	}
}

void TestSeqList () {
	SL sl;
	SeqListInit (&sl);
	
	SeqListPushFront(&sl, 100);
	SeqListPushFront(&sl, 101);
	SeqListPushFront(&sl, 102);
	SeqListPushFront(&sl, 103);
	SeqListPushFront(&sl, 104);
	SeqListPushFront(&sl, 105);
	SeqListPushFront(&sl, 106);
	
	SeqListPrint(&sl);

}

// ������ 
int main() {
	TestSeqList();
	return 0;
}; 
