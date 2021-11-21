#include<bits/stdc++.h>

using namespace std;

#define MaxInt 32767
#define MAXNum 100
typedef char VerTexType;
typedef int ArcType;

typedef struct
{
	VerTexType vexs[MAXNum];
	ArcType arcs[MAXNum][MAXNum];
	int vexnum, arcnum;
} AMGraph;


int LocateVex(AMGraph G, VerTexType V)
{
	for(int k = 0; k < G.vexnum; ++k) {
		if (V == G.vexs[k]) {
			return k;
		}
	}
	return 0;
}


// ������������
int CreateUDM(AMGraph &G)
{
	printf("���������������Ķ����������������\n");
	cin>>G.vexnum>>G.arcnum;
	printf("�������������Ķ��㣺\n");
	for(int i = 0; i < G.vexnum; ++i) {
		cin>>G.vexs[i];
	}
	
	// ��ʼ�������� --- Ĭ���� 	32767
	for(int i = 0; i < G.vexnum; ++i) {
		for(int j = 0; j < G.vexnum; ++j) {
			G.arcs[i][j]=MaxInt; 
		}
	}
	
	for(int k = 0; k < G.arcnum; ++k) {
		VerTexType v1, v2;
		int w, i, j;
		printf("�������������ĵ�һ������͵ڶ�������ͱߵ�Ȩֵ��\n");
		// ����ߵ���ʼ�ڵ��ĩβ�ڵ�ͱߵ�Ȩֵ		
		cin>>v1>>v2>>w;
		// �õ���ʼ�ڵ��ĩβ�ڵ��ڶ�����е��±�		
		i = LocateVex(G, v1);
		j = LocateVex(G, v2); 
		G.arcs[i][j] = w;
		G.arcs[j][i] = G.arcs[i][j];
	}
	return 1;
}

void PrintGraph (AMGraph G) {
	for(int i = 0; i < G.vexnum; ++i) {
		for(int j = 0; j < G.vexnum; ++j) {
			cout<<G.arcs[i][j];
			cout<<" ";
		}
		printf("\n");
	}	
}

int main() {
	AMGraph LG;
	CreateUDM(LG);
	PrintGraph(LG);
}

// ���������
// 5 6 
// A B C D E
// A B 1
// A D 1
// B C 1
// B E 1
// C E 1
// C D 1
// ��������� P154 �� 32747 �ĳ� 0 ���� 
