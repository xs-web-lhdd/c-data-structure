#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define null 0

// 多项式的项
typedef struct
{
	float coef; //系数
	int expn;	//指数
} term;

typedef int status;

typedef struct Lnode
{
	term data;			//单链表中的数据项
	struct Lnode *next; //指向下一个链表项的指针
} * Link, *Linklist;

/*
	判断两个项的指数的关系
	相等：返回0，
	不等：如果第一个大于第二个，返回1，否则返回-1。
*/
int cmp(term a, term b)
{
	if (a.expn == b.expn) // 指数相等
		return 0;
	else
		return (a.expn - b.expn) / abs(a.expn - b.expn); //指数不相等，abs求绝对值
}
/*
	按顺序插入值，顺序可以自己指定，指定的方法就是comp函数指针
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
	按项查找
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
	删除当前元素的下一个元素
*/
void Delnext(Linklist &L, Link s)
{
	Link q = s->next;
	s->next = q->next;
	free(q);
}

/*
	把一个多项式项加到一个多项式链表的程序。
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
	循环接收指定数量的元素存储到链表中，并自动调整顺序
*/
void Creatpolyn(Linklist &p, int m)
{
	term e;
	int i;
	p = (Link)malloc(sizeof(Lnode));
	p->next = null;
	printf("\n请输入%d个系数和指数用空格符间隔: \n", m);
	for (i = 1; i <= m; i++)
	{
		scanf("%f%d", &e.coef, &e.expn);
		Orderinsertmerge(p, e, cmp);
	}
}

/*
	添加元素
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
	//销毁链表LB
}

//打印指数和系数
void printpolyn(Linklist p)
{
	Link q;
	q = p->next;

	printf("%-8s %s\n", "系数", "指数");
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
	printf("\n请输入第一个一元多项式的项数:");
	scanf("%d", &x);
	Creatpolyn(L1, x);
	printpolyn(L1);
	printf("\nL1=");
	//PrintList(L1);
	printf("\n请输入第二个一元多项式的项数:");
	scanf("%d", &x);
	Creatpolyn(L2, x);
	printpolyn(L2);
	printf("\nL2=");
	//PrintList(L2);
	add(L1, L2);
	printf("\n相加以后的一元多项式为：\n");
	printpolyn(L1);
	printf("\nL1+L2=");
	system("pause");
	//PrintList(L1);
}

