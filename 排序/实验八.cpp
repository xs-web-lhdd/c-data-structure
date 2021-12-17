#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
#define MAXSIZE 20
#define LEN(a) sizeof(a)/sizeof(a[0])

typedef int InfoType;
typedef int KeyType;
int flag=0;

typedef struct {
	KeyType key;
	InfoType otherinfo;
} RedType;

typedef struct {
	RedType r[MAXSIZE + 1];
	int length;
} SqList;

//ϣ������
void ShellInsert(SqList &L, int dk) {         
	int i, j;
	for (i = dk + 1; i <= L.length; i++)
		if(L.r[i].key < L.r[i-dk].key) {
			L.r[0] = L.r[i];
			for (j = i-dk; j > 0 && L.r[0].key < L.r[j].key; j -= dk)
				L.r[j + dk] = L.r[j];
			L.r[j + dk] = L.r[0];
		}
}

void ShellSort(SqList &L, int dt[], int t) {
	int k;
	for (k = 0; k < t ; ++k) {
		ShellInsert(L, dt[k]);
		if(dt[k]==5){
			printf("\n��һ�ˣ�");
			for (int i = 1; i <= L.length; i++)
				printf("%d ", L.r[i].key);
			printf("\n");
		}
		
	}
		
}


//��������
int Partition(SqList &L, int low, int high) {
	int pivotkey;
	int pivotloc;
	L.r[0] = L.r[low];
	pivotkey=L.r[low].key;
	while (low < high) {
		while (low < high && L.r[high].key >= pivotkey) --high;    /*�Ҳ�ɨ��*/
		L.r[low]=L.r[high];
		while (low < high && L.r[low].key <= pivotkey)  ++low;    /*���ɨ��*/
		L.r[high]=L.r[low];
	}
	L.r[low]=L.r[0];
	return low;                                                /*lowΪ��ֵ��¼������λ��*/
}

void QSort(SqList &L, int low, int high) {
	int pivotloc;
	
	flag+=1;
	if(low<high) {
		pivotloc=Partition (L, low, high);
		
		if(flag==1){
			printf("\n��һ�ˣ�");
			for (int i = 1; i <= L.length; i++)
				printf("%d ", L.r[i].key);
			printf("\n");
		}
		QSort (L, low, pivotloc-1);
		QSort (L, pivotloc+1, high);
	}
}

void QuickSort(SqList &L) {
	int flag=0;
	QSort(L,1,L.length);
}

//������
void HeapAdjust(SqList &L, int s, int m) {
	RedType rc;
	int j;
	rc = L.r[s];
	for(j=2*s; j<=m; j*=2) {
		if (j < m && L.r[j].key < L.r[j+1].key) ++j;
		if (rc.key >= L.r[j].key) break;
		L.r[s]=L.r[j];
		s=j;
	}
	L.r[s] = rc;
}

void HeapSort(SqList &L) {
	int i,n=L.length;
	RedType x;
	RedType y;
	for (i = n/2; i >= 1; i--)
		HeapAdjust(L, i, n);
	x = L.r[1];
		L.r[1] =L.r[L.length];
		L.r[L.length] = x;
	printf("\n��һ�ˣ�");
	for (int w = 1; w <= L.length; w++)
		printf("%d ", L.r[w].key);
	printf("\n");
	x = L.r[1];
		L.r[1] =L.r[i];
		L.r[i] = x;
	for (i = L.length; i > 1; --i) {
		x = L.r[1];
		L.r[1] =L.r[i];
		L.r[i] = x;
		HeapAdjust(L, 1, i-1);
	}
}

void CreatSq(SqList &L) {
	printf("���������ݸ�����");
	scanf("%d", &L.length);
	printf("������%d������Ԫ�أ�", L.length);
	for (int i = 0; i <= L.length; i++)
		scanf("%d", &L.r[i].key);
}

void Print(SqList L) {
	for (int i = 1; i <= L.length; i++)
		printf("%d ", L.r[i].key);
	printf("\n\n");
}

int main() {
	SqList L;
	printf("******ϣ������******\n");
	int dt[3]= {5,3,1};
	int length; 
	cout<<"�����������б��ȣ�"; 
	cin>>length;
	int a[length];
	int k = 0;
	char b;
	cout<<"�����������б������ֵ"; 
	while(b = getchar()) {
		if(b == '#') {
			break;
		}
		a[k] = b;
		k++;
	} 
	CreatSq(L);
	printf("����ǰ:");
	Print(L);
	ShellSort(L,dt,3);
	printf("�����:");
	Print(L);

	printf("******��������******\n");
	CreatSq(L);
	printf("����ǰ:");
	Print(L);
	QuickSort(L);
	printf("�����:");
	Print(L);

	printf("*******������******\n");
	CreatSq(L);
	printf("����ǰ:");
	Print(L);
	HeapSort(L);
	printf("�����:");
	Print(L);
	
	return 0;
	
}

