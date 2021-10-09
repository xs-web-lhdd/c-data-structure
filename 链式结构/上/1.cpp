#include<stdio.h>
#include<stdlib.h>

typedef int SLTDataType;
// ��������ṹ���һ���ڵ� 
struct SListNode {
	SLTDataType data;
	struct SListNode* next;
};

typedef struct SListNode SLTNode;


// �������к�����

// β��:
void SListPushBack(SLTNode** phead, SLTDataType x); 
// ��ӡ��
void SListPrint(SLTNode* phead);

void SListPushBack(SLTNode** phead, SLTDataType x) {
	// ����һ���ڵ� 
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	// �ڵ��������Ҫ���ȥ������	
	newnode->data = x;
	// ��Ϊ��β�壬���Ժ���û�нڵ㣬��next��NULL	
	newnode->next = NULL;


	if(*phead == NULL) {
		*phead = newnode;
	} else {
		SLTNode* tail = *phead;
		while(tail->next != NULL) {
			tail = tail->next;
		}
		// �ó��� tail ����������һ���ڵ�
		// ��β�ڵ������½ڵ�	
		tail->next = newnode;
	}
}



// �ڵ��ӡ���� 
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


