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
	Ӧ�ó���������ָ����ϵ��ʱ���к�����ʽ�ϲ� 
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
	// ͷ�ڵ�	
	q = L;
	// ��Ԫ�ڵ�	
	p = q->next;
	// �ҵ�����ֵ��ָ��С��ԭ������һ��
	while (p && comp(p->data, e) < 0)
	{
		q = p;
		p = p->next;
	}
	// ����һ���սڵ�	
	o = (Link)malloc(sizeof(Lnode));
	// ��ֵ�����սڵ�	
	o->data = e;
	// ����	
	q->next = o;
	o->next = p;
}

/*
	�������
	Linklist L�� ���� 
	term e�� ���ҵ��� 
	Link &s ��ָ�� 
	Link &q ��ָ�� 
	int (*comp)(term, term)�� �Ƚ�ָ������ 
*/
status LocateElem(Linklist L, term e, Link &s, Link &q, int (*comp)(term, term))
{
	Link p;
	// ͷ�ڵ�	
	s = L;
	// ��Ԫ�ڵ�	
	p = s->next;
	
	while (p && comp(p->data, e) != 0)
	{
		// s ���ҵ���Ŀ�����ǰһ��	
		s = p;
		p = p->next;
	}
	// �ձ�	
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
	// �����λ�����ҵ� e	
	if (LocateElem(L, e, s, q, compara))
	{
		// ϵ�����		
		q->data.coef += e.coef;
		// ϵ��Ϊ 0 �ͽ��ڵ�ɾ��	
		if (!q->data.coef)
		{
			// ��ǰһ���ɾ���սڵ�			
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
	// ����һ��������	
	p = (Link)malloc(sizeof(Lnode));
	p->next = null;
	
	printf("\n������%d��ϵ����ָ���ÿո�����: \n", m);
	for (i = 1; i <= m; i++)
	{
		scanf("%f%d", &e.coef, &e.expn);
		// ����һ������������в���һ��		
		Orderinsertmerge(p, e, cmp);
	}
}

/*
	����ʽ�������
	La ������
	Lb ��ѭ���� 
*/
void add(Linklist &Lc, Linklist La, Linklist Lb)

{
	Lc = (Linklist)malloc(sizeof(Linklist));
	Lc->next = null;
	Link qb, qa;
	term b;
	term a;
	// Lb ����Ԫ�ڵ�
	qb = Lb->next;
	qa = La->next;
	while (qb)
	{
		b = qb->data;

		// �� Lb���е� b ��嵽La����		
		Orderinsertmerge(Lc, b, cmp);

		qb = qb->next;

	}
	while(qa){
		a = qa->data;
		Orderinsertmerge(Lc, a, cmp);
		qa = qa->next;
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

/*
	ֱ�Ӵ�ӡ����ʽ����
*/
void printList(Linklist L)
{
	Link p = L->next;
	printf("%.2fx^%d", p->data.coef, p->data.expn);
	while ((p = p->next) != null)
	{
		if (p->data.coef < 0)
		{
			printf(" - %.2fx^%d", -(p->data.coef), p->data.expn);
		}
		else
			printf(" + %.2fx^%d", p->data.coef, p->data.expn);
	}
	putchar('\n');
}
/*
	��������ʽ���
*/
status multiple(Linklist &Lc, Linklist &La, Linklist &Lb)
{
	Lc = (Link)malloc(sizeof(Lnode));
	Lc->next = null;
	Link p, q;
	term e;
	p = La->next;
	q = Lb->next;
	while (p)
	{
		while (q)
		{
			printf("�˷�");
			e.coef = p->data.coef * q->data.coef;
			e.expn = p->data.expn + q->data.expn;
			Orderinsertmerge(Lc, e, cmp);
			q = q->next;
		}
		p = p->next;
		q = Lb->next;
	}
	return 1;
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
	printList(L1);
	printf("\n������ڶ���һԪ����ʽ������:");
	scanf("%d", &x);
	Creatpolyn(L2, x);
	printpolyn(L2);
	printf("\nL2=");
	printList(L2);
	
	
//	 Linklist L4;	
//	 add(L4, L1, L2);
//	 printf("\n����Ժ��һԪ����ʽΪ��\n");
//	 printpolyn(L4);
//	 printf("\nL1+L2=");
//	 printList(L4);
	
	
	Linklist L3;
	multiple(L3, L1, L2);
	printf("\n����Ժ��һԪ����ʽΪ��\n");
	printpolyn(L3);
	printf("\nL1*L2=");
	printList(L3);
	system("pause");
}

