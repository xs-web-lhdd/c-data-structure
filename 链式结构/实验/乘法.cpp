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
	应用场景：输入指数、系数时进行横向表达式合并 
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
	// 头节点	
	q = L;
	// 首元节点	
	p = q->next;
	// 找到插入值的指数小于原表中下一项
	while (p && comp(p->data, e) < 0)
	{
		q = p;
		p = p->next;
	}
	// 创建一个空节点	
	o = (Link)malloc(sizeof(Lnode));
	// 把值赋给空节点	
	o->data = e;
	// 插入	
	q->next = o;
	o->next = p;
}

/*
	按项查找
	Linklist L： 连表 
	term e： 查找的项 
	Link &s 空指针 
	Link &q 空指针 
	int (*comp)(term, term)： 比较指数函数 
*/
status LocateElem(Linklist L, term e, Link &s, Link &q, int (*comp)(term, term))
{
	Link p;
	// 头节点	
	s = L;
	// 首元节点	
	p = s->next;
	
	while (p && comp(p->data, e) != 0)
	{
		// s 是找到项目标项的前一项	
		s = p;
		p = p->next;
	}
	// 空表	
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
	// 如果按位查找找到 e	
	if (LocateElem(L, e, s, q, compara))
	{
		// 系数相加		
		q->data.coef += e.coef;
		// 系数为 0 就将节点删除	
		if (!q->data.coef)
		{
			// 把前一项传入删除空节点			
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
	// 创建一个空链表	
	p = (Link)malloc(sizeof(Lnode));
	p->next = null;
	
	printf("\n请输入%d个系数和指数用空格符间隔: \n", m);
	for (i = 1; i <= m; i++)
	{
		scanf("%f%d", &e.coef, &e.expn);
		// 输入一项就往空链表中插入一项		
		Orderinsertmerge(p, e, cmp);
	}
}

/*
	多项式链表相加
	La 是主表
	Lb 是循环表 
*/
void add(Linklist &Lc, Linklist La, Linklist Lb)

{
	Lc = (Linklist)malloc(sizeof(Linklist));
	Lc->next = null;
	Link qb, qa;
	term b;
	term a;
	// Lb 的首元节点
	qb = Lb->next;
	qa = La->next;
	while (qb)
	{
		b = qb->data;

		// 将 Lb表中的 b 项插到La表中		
		Orderinsertmerge(Lc, b, cmp);

		qb = qb->next;

	}
	while(qa){
		a = qa->data;
		Orderinsertmerge(Lc, a, cmp);
		qa = qa->next;
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

/*
	直接打印多项式链表。
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
	两个多项式相乘
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
			printf("乘法");
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
	printf("\n请输入第一个一元多项式的项数:");
	scanf("%d", &x);
	Creatpolyn(L1, x);
	printpolyn(L1);
	printf("\nL1=");
	printList(L1);
	printf("\n请输入第二个一元多项式的项数:");
	scanf("%d", &x);
	Creatpolyn(L2, x);
	printpolyn(L2);
	printf("\nL2=");
	printList(L2);
	
	
//	 Linklist L4;	
//	 add(L4, L1, L2);
//	 printf("\n相加以后的一元多项式为：\n");
//	 printpolyn(L4);
//	 printf("\nL1+L2=");
//	 printList(L4);
	
	
	Linklist L3;
	multiple(L3, L1, L2);
	printf("\n相乘以后的一元多项式为：\n");
	printpolyn(L3);
	printf("\nL1*L2=");
	printList(L3);
	system("pause");
}

