
////////////////////////////////静态//////////////////////////////////////////////////////////////////// 
//#include<stdio.h>
//#include<string.h> 
//
//// 定义宏 --- 增强程序的可维护性 
//#define MAX_SIZE 10
//
//typedef int SQDataType;
//
//struct SeqList {
//	SQDataType a[MAX_SIZE];
//	int size;
//};
//
//// 第一种 struct 的别名 
//typedef struct SeqList SL;
//// 第二种 struct 的别名
////typedef struct SeqList
////{
////	SQDataType a [N];
////	int size;
////} SL;
//
//// 初始化表 
//void SeqListInit (SL *ps);
//// 在尾部插入
//void SeqListPushBack (SL *ps, SQDataType x);
//// 在头部插入 
//void SeqListPushFront (SL *ps, SQDataType x);
//// 头删
//void SeqListPopBack (SL *ps, SQDataType x);
//// 尾删
//void SeqListPopFront (SL *ps, SQDataType x);
//
//// 输出表
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
//		printf("你爆栈了!!!");
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



////////////////////////////////////动态////////////////////////////////////////////////////
#include<stdio.h>
#include<string.h>
#include<stdlib.h> 

// 定义宏 --- 增强程序的可维护性 
#define MAX_SIZE 10

typedef int SQDataType;

struct SeqList {
	SQDataType* a;
	int size;
	int capacity;
};
typedef struct SeqList SL;



// 初始化表 
void SeqListInit (SL *ps);
// 在尾部插入
void SeqListPushBack (SL *ps, SQDataType x);
// 在头部插入 
void SeqListPushFront (SL *ps, SQDataType x);
// 头删
void SeqListPopBack (SL *ps, SQDataType x);
// 尾删
void SeqListPopFront (SL *ps, SQDataType x);

// 输出表
void SeqListPrint (SL *ps, SQDataType i); 


// 对表进行初始化 
void SeqListInit (SL *ps) {
	ps->a = NULL;
	ps->size = 0;
	ps->capacity = 0;
}

// 扩容的函数
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

// 尾插 
void SeqListPushBack (SL *ps, SQDataType x) {
	// 满了就要扩容 --- 一般扩两倍	

	SeqListCapacity(ps);
	ps->a[ps->size] = x;
	ps->size++;
}

void SeqListPushFront (SL *ps, SQDataType x) {
	SeqListCapacity(ps);
//	1、初始条件
//  2、结束条件
//  3、迭代过程
	int end = ps->size - 1;
	while(end >= 0) {
		ps->a[end+1] = ps->a[end];
		--end;
	}
//	printf("11111\n");
	ps->a[0] = x;
	ps->size++;
}

// 打印 
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

// 主函数 
int main() {
	TestSeqList();
	return 0;
}; 
