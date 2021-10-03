
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
#include<assert.h>

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
// 尾删
void SeqListPopBack (SL *ps);
// 头删
void SeqListPopFront (SL *ps);
// 在某个位置进行插入
void SeqListInsert (SL *ps, int i, SQDataType x); 
// 在某个位置进行删除
void SeqListDelete (SL *ps, int i); 

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

// 头插 
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


// 尾删 
void SeqListPopBack (SL *ps) {
	assert(ps->size > 0);
//	ps->a[ps->size-1] = 0;
	ps->size--;
}

// 头删
void SeqListPopFront (SL *ps) {
	// 断言 ps->size 大于 0，如果不是就报错！	
	assert(ps->size > 0);
	int start = 1;
	while(start < ps->size) {
		ps->a[start-1] = ps->a[start];
		++start;
	}
	ps->size--; 
}

// 在某个位置进行插入 
void SeqListInsert (SL *ps, int pos, SQDataType x) {
	assert(pos <= ps->size);
	SeqListCapacity(ps);
	if (pos < 0 || pos > ps->size) {
		printf("你要插入的数据位置%d不在范围内！！！\n", pos);
		return;
	}
	
	int end = ps->size - 1;
	while(end >= pos) {
		ps->a[end + 1] = ps->a[end];
		end--;
	}
	
	ps->a[pos] = x;
	ps->size++;
}

// 在某个位置进行删除 
void SeqListDelete (SL *ps, int pos) {
	assert(pos <= ps->size);
	if (pos < 0 || pos > ps->size) {
		printf("你要删除的数据位置%d不在范围内！！！\n", pos);
		return;
	}
	
	int start = pos + 1;
	while(start < ps->size) {
		ps->a[start - 1] = ps->a[start];
		start++;
	}
	
	ps->size--;
}


// 查找
bool SeqListFind (SL *ps, SQDataType x) {
	for(int i = 0; i < ps->size; i++) {
		if (ps->a[i] == x) {
			return i;
		}
	}
	return -1;
} 


// 对不用的空间进行销毁
void SeqListDestory (SL *ps) {
	free(ps->a);
	ps->a = NULL;
	ps->capacity = ps->size = 0;
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
	
//	SeqListPopBack(&sl);
//	SeqListPopFront(&sl);

//	SeqListInsert(&sl, 7, 10);
//	SeqListDelete(&sl, 7);

//	int res = SeqListFind(&sl, 104);
	
	SeqListPrint(&sl);
	
//	所有数据使用完之后进行销毁---防止内存泄露 
	SeqListDestory(&sl);
}

// 主函数 
int main() {
	TestSeqList();
	return 0;
}; 
