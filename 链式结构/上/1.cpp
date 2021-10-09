#include<stdio.h>
#include<stdlib.h>

typedef int SLTDataType;
// 定义链表结构体的一个节点 
struct SListNode {
	SLTDataType data;
	struct SListNode* next;
};

typedef struct SListNode SLTNode;


// 声明所有函数：

// 尾插:
void SListPushBack(SLTNode** phead, SLTDataType x); 
// 打印：
void SListPrint(SLTNode* phead);

void SListPushBack(SLTNode** phead, SLTDataType x) {
	// 创造一个节点 
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	// 节点的数据是要插进去的数据	
	newnode->data = x;
	// 因为是尾插，所以后面没有节点，即next是NULL	
	newnode->next = NULL;


	if(*phead == NULL) {
		*phead = newnode;
	} else {
		SLTNode* tail = *phead;
		while(tail->next != NULL) {
			tail = tail->next;
		}
		// 得出的 tail 是链表的最后一个节点
		// 将尾节点连到新节点	
		tail->next = newnode;
	}
}



// 节点打印函数 
void SListPrint(SLTNode* phead) {
	SLTNode* cur = phead;
	while(cur != NULL) {
		printf("%d\n", cur->data);
		cur = cur->next; 
	}
}
















void TestSList1() {
	SLTNode* plist = NULL;
	SListPushBack(&plist, 1);
	SListPushBack(&plist, 2);
	SListPushBack(&plist, 3);
	SListPushBack(&plist, 4);
	SListPrint(plist); 
}

int main() {
	TestSList1();
	return 0;
}


