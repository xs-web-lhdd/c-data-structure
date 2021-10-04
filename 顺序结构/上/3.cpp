#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
#include<assert.h>

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
// βɾ
void SeqListPopBack (SL *ps);
// ͷɾ
void SeqListPopFront (SL *ps);
// ��ĳ��λ�ý��в���
void SeqListInsert (SL *ps, int i, SQDataType x); 
// ��ĳ��λ�ý���ɾ��
void SeqListDelete (SL *ps, int i); 

// �����
void SeqListPrint (SL *ps, SQDataType i);

// ��������
void sort(SL *ps);

// �Ա���кϲ� 
void MergeList(SL *psOne, SL *psTwo, SL *psLast);

// ��ת���� 
void reverse(SL *ps);


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

// ͷ�� 
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


// βɾ 
void SeqListPopBack (SL *ps) {
	assert(ps->size > 0);
//	ps->a[ps->size-1] = 0;
	ps->size--;
}

// ͷɾ
void SeqListPopFront (SL *ps) {
	// ���� ps->size ���� 0��������Ǿͱ���	
	assert(ps->size > 0);
	int start = 1;
	while(start < ps->size) {
		ps->a[start-1] = ps->a[start];
		++start;
	}
	ps->size--; 
}

// ��ĳ��λ�ý��в��� 
void SeqListInsert (SL *ps, int pos, SQDataType x) {
	assert(pos <= ps->size);
	SeqListCapacity(ps);
	if (pos < 0 || pos > ps->size) {
		printf("��Ҫ���������λ��%d���ڷ�Χ�ڣ�����\n", pos);
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

// ��ĳ��λ�ý���ɾ�� 
void SeqListDelete (SL *ps, int pos) {
	assert(pos <= ps->size);
	if (pos < 0 || pos > ps->size) {
		printf("��Ҫɾ��������λ��%d���ڷ�Χ�ڣ�����\n", pos);
		return;
	}
	
	int start = pos + 1;
	while(start < ps->size) {
		ps->a[start - 1] = ps->a[start];
		start++;
	}
	
	ps->size--;
}


// ����
bool SeqListFind (SL *ps, SQDataType x) {
	for(int i = 0; i < ps->size; i++) {
		if (ps->a[i] == x) {
			return i;
		}
	}
	return -1;
} 


// �Բ��õĿռ��������
void SeqListDestory (SL *ps) {
	free(ps->a);
	ps->a = NULL;
	ps->capacity = ps->size = 0;
}


// ��ӡ 
void SeqListPrint (SL *ps) {
	int i;
	for(i = 0; i < ps->size; i++) {
		printf("%d\n", ps->a[i+1]);
	}
	printf("######################\n");
}

// �������ݣ�
void SeqListInput (SL *ps) {
    printf("�밴��������һϵ���������ÿո��������-999��β��\n");
    SeqListCapacity(ps);
    int temp;
    for(int i=0;;i++)           //ѭ������һϵ������ 
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

// �Ա��������
void sort(SL *ps) {
	int i, j;
	int temp;
    for(i=0; i<ps->size; i++){
        //ÿһ�ֱȽ�ǰ n-1-i ����Ҳ����˵���Ѿ�����õ���� i �����ñȽ�
        for(j=0; j<ps->size-i; j++){
            if(ps->a[j] > ps->a[j+1]){
                temp = ps->a[j];
                ps->a[j] = ps->a[j+1];
                ps->a[j+1] = temp;
            }
        }
    }
}

// �Ա���кϲ� 
void MergeList(SL *psOne, SL *psTwo, SL *psLast) {
	int i = 1;
	int j = 1;
	SeqListCapacity(psLast);
	psLast->size = psOne->size + psTwo->size;
//	�ϲ� 
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
//	��ʼ�� 
	SeqListInit (&slOne);
	SeqListInit (&slTwo);
	SeqListInit (&slThree);
//  ����ֵ 
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
	
//	��������ʹ����֮���������---��ֹ�ڴ�й¶ 
	SeqListDestory(&slOne);
}



// ������ 
int main() {
	TestSeqList();
	return 0;
}; 
