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

// 进行排序
void sort(SL *ps);

// 对表进行合并 
void MergeList(SL *psOne, SL *psTwo, SL *psLast);

// 反转函数 
void reverse(SL *ps);


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
	int i;
	for(i = 0; i < ps->size; i++) {
		printf("%d\n", ps->a[i+1]);
	}
	printf("######################\n");
}

// 输入内容：
void SeqListInput (SL *ps) {
    printf("请按升序输入一系列整数，用空格隔开，以-999结尾：\n");
    SeqListCapacity(ps);
    int temp;
    for(int i=0;;i++)           //循环输入一系列整数 
    {
        scanf("%d",&temp);
        if(temp!=-999)
        {
            ps->a[i] = temp;
            ps->size++;
        }
        else
            break;
    }
}

// 对表进行排序
void sort(SL *ps) {
	int i, j;
	int temp;
    for(i=0; i<ps->size; i++){
        //每一轮比较前 n-1-i 个，也就是说，已经排序好的最后 i 个不用比较
        for(j=0; j<ps->size-i; j++){
            if(ps->a[j] > ps->a[j+1]){
                temp = ps->a[j];
                ps->a[j] = ps->a[j+1];
                ps->a[j+1] = temp;
            }
        }
    }
}

// 对表进行合并 
void MergeList(SL *psOne, SL *psTwo, SL *psLast) {
	int i = 1;
	int j = 1;
	SeqListCapacity(psLast);
	psLast->size = psOne->size + psTwo->size;
//	合并 
	while(i <= psOne->size) {
		psLast->a[i] = psOne->a[i];
		i++;
	}
	while(i <= psLast->size ) {
		psLast->a[i] = psTwo->a[j];
		i++;
		j++;
	}
}

void reverse(SL *ps) {
	int i = 1;
	int tmp;
	int L = ps->size;
	for (i; i < ps->size / 2 + 1; i++) {
		tmp = ps->a[L-i+1];
		ps->a[L-i+1] = ps->a[i];
		ps->a[i] = tmp;
	}
} 
 

void TestSeqList () {
	SL slOne;
	SL slTwo;
	SL slThree;
//	初始化 
	SeqListInit (&slOne);
	SeqListInit (&slTwo);
	SeqListInit (&slThree);
//  输入值 
	SeqListInput(&slOne);
	sort(&slOne);
	SeqListInput(&slTwo);
	sort(&slTwo);
	
	MergeList(&slOne, &slTwo, &slThree);
	sort(&slThree);
//	SeqListPushFront(&sl, 100);
//	SeqListPushFront(&sl, 101);
//	SeqListPushFront(&sl, 102);
//	SeqListPushFront(&sl, 103);
//	SeqListPushFront(&sl, 104);
//	SeqListPushFront(&sl, 105);
//	SeqListPushFront(&sl, 106);
	
//	SeqListPopBack(&sl);
//	SeqListPopFront(&sl);

//	SeqListInsert(&sl, 7, 10);
//	SeqListDelete(&sl, 7);

//	int res = SeqListFind(&sl, 104);
	
//	SeqListPrint(&slOne);
//	SeqListPrint(&slTwo);
	SeqListPrint(&slThree);
	
	reverse(&slThree);
	SeqListPrint(&slThree);
	
//	所有数据使用完之后进行销毁---防止内存泄露 
	SeqListDestory(&slOne);
}



// 主函数 
int main() {
	TestSeqList();
	return 0;
}; 
