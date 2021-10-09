#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define null 0

// ����ʽ����
typedef struct
{
	float coef; //ϵ��
	int expn;	//ָ��
} term;

typedef int status;

typedef struct Lnode
{
	term data;			//�������е�������
	struct Lnode *next; //ָ����һ���������ָ��
} * Link, *Linklist;

/*
	�ж��������ָ���Ĺ�ϵ
	��ȣ�����0��
	���ȣ������һ�����ڵڶ���������1�����򷵻�-1��
*/
int cmp(term a, term b)
{
	if (a.expn == b.expn) // ָ�����
		return 0;
	else
		return (a.expn - b.expn) / abs(a.expn - b.expn); //ָ������ȣ�abs�����ֵ
}
/*
	��˳�����ֵ��˳������Լ�ָ����ָ���ķ�������comp����ָ��
*/
void Orderinsert(Linklist &L, term e, int (*comp)(term, term))
{
	Link o, p, q;
	q = L;
	p = q->next;
	while (p && comp(p->data, e) < 0)
	{
		q = p;
		p = p->next;
	}
	o = (Link)malloc(sizeof(Lnode));
	o->data = e;
	q->next = o;
	o->next = p;
}

/*
	�������
*/
status LocateElem(Linklist L, term e, Link &s, Link &q, int (*comp)(term, term))
{
	Link p;
	s = L;
	p = s->next;
	while (p && comp(p->data, e) != 0)
	{
		s = p;
		p = p->next;
	}
	if (!p)
	{
		s = q = null;
		return 0;
	}
	else
	{
		q = p;
		return 1;
	}
}

/*
	ɾ����ǰԪ�ص���һ��Ԫ��
*/
void Delnext(Linklist &L, Link s)
{
	Link q = s->next;
	s->next = q->next;
	free(q);
}

/*
	��һ������ʽ��ӵ�һ������ʽ����ĳ���
*/
void Orderinsertmerge(Linklist &L, term e, int (*compara)(term, term))
{
	Link q, s;
	if (LocateElem(L, e, s, q, compara))
	{
		q->data.coef += e.coef;
		if (!q->data.coef)
		{
			Delnext(L, s);
		}
	}
	else
		Orderinsert(L, e, compara);
}

/*
	ѭ������ָ��������Ԫ�ش洢�������У����Զ�����˳��
*/
void Creatpolyn(Linklist &p, int m)
{
	term e;
	int i;
	p = (Link)malloc(sizeof(Lnode));
	p->next = null;
	printf("\n������%d��ϵ����ָ���ÿո�����: \n", m);
	for (i = 1; i <= m; i++)
	{
		scanf("%f%d", &e.coef, &e.expn);
		Orderinsertmerge(p, e, cmp);
	}
}

/*
	���Ԫ��
*/
void add(Linklist &La, Linklist Lb)

{
	Link qb;
	term b;
	qb = Lb->next;
	while (qb)
	{
		b = qb->data;
		Orderinsertmerge(La, b, cmp);
		qb = qb->next;
	}
	//��������LB
}

//��ӡָ����ϵ��
void printpolyn(Linklist p)
{
	Link q;
	q = p->next;

	printf("%-8s %s\n", "ϵ��", "ָ��");
	while (q)
	{
		printf("%-8.2f  %-d\n", q->data.coef, q->data.expn);
		q = q->next;
	}
}

int main()
{
	int x;
	Linklist L1, L2;
	printf("\n�������һ��һԪ����ʽ������:");
	scanf("%d", &x);
	Creatpolyn(L1, x);
	printpolyn(L1);
	printf("\nL1=");
	//PrintList(L1);
	printf("\n������ڶ���һԪ����ʽ������:");
	scanf("%d", &x);
	Creatpolyn(L2, x);
	printpolyn(L2);
	printf("\nL2=");
	//PrintList(L2);
	add(L1, L2);
	printf("\n����Ժ��һԪ����ʽΪ��\n");
	printpolyn(L1);
	printf("\nL1+L2=");
	system("pause");
	//PrintList(L1);
}

