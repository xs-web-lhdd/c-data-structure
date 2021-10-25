#include <stdio.h>
#include <stdlib.h>

typedef int status;

// Ԫ�أ� 
typedef struct Node
{
    char e;
    struct Node *next;
} node;

// ջ�� 
typedef struct Steak
{
    node *top;
    node *base;
    int length;
} steak;

// �ӣ� 
typedef struct Queue
{
    node *front;
    node *rear;
    int length;
} queue;

//��ջ���г�ʼ��
status initSteak(steak *s)
{
    s->base = (node *)malloc(sizeof(node));
    s->top = s->base;
    s->length = 0;
    if (s->base == NULL)
    {
        printf("ջ��ʼ��ʧ��");
        return -1;
    }
    return 0;
}

//�Զ��н��г�ʼ��
status initQueue(queue *q)
{
    q->front = (node *)malloc(sizeof(node));
    q->rear = q->front;
    if (q->front == NULL)
    {
        printf("���г�ʼ��ʧ��");
    }
    q->length = 0;
    return 0;
}

//��ջ�� 
status push(steak *s, char c)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->e = c;
    temp->next = s->top;
    s->top = temp;
    s->length += 1;
    return 0;
}
//��ӣ� 
status quePush(queue *q, char c)
{
    q->rear->e = c;
    node *e = (node *)malloc(sizeof(node));
    q->rear->next = e;
    q->rear = e;
    q->length++;
}

//���ջ�����е�Ԫ��
status showSteak(steak *s)
{
    printf("չʾջ�еĹ�ʽ��\n");
    int len = s->length - 1;
    node *temp = s->top;
    printf("%c", temp->e);
    for (int i = 0; i < len; i++)
    {
        temp = temp->next;
        printf("%c", temp->e);
    }
    putchar('\n');
    return 1;
}

//��ջ�� 
char pop(steak *s)
{
    node *temp = s->top;
    s->top = temp->next;
    s->length--;
    char c = temp->e;
    free(temp);
    return c;
}

//����
char quePop(queue *q)
{
    node *e = q->front;
    q->front = e->next;
    q->length--;
    char c = e->e;
    free(e);
    return c;
}

//�������н���ֵ
status inputElem(steak *s)
{
    printf("������һ�ι�ʽ���ԡ�#����β��:");
    char e;

    while (scanf("%c", &e) && e != '#')
    {
        push(s, e);
    }
    return 1;
}
//��ԭ����ջ���е���
status reverse(steak *s)
{
    int len = s->length;
    steak new_s;
    initSteak(&new_s);
    node *temp = s->top;
    for (int i = 0; i < len; i++)
    {
        push(&new_s, temp->e);
        temp = temp->next;
        pop(s);
    }
    pop(s);
    *s = new_s;
}

//��ջ��ɾ����Ӧ��ֵ
status delVal(steak *s)
{
    int len = s->length;
    queue q;
    initQueue(&q);
    char c, a;
    node *temp = s->top;
    printf("������Ҫɾ����ֵ��");
    scanf(" %c", &c);
    for (int i = 0; i < len; i++)
    {
        a = pop(s);
        if (a == c)
            continue;
        quePush(&q, a);
    }
    if (len == q.length)
    {
        printf("ջ��û�ж�Ӧ��ֵ");
    }
    len = q.length;
    for (int i = 0; i < len; i++)
    {
        a = quePop(&q);
        push(s, a);
    }
    reverse(s);
}

int main(int argc, char const *argv[])
{
    steak s;
    initSteak(&s);
    inputElem(&s);
    showSteak(&s);
    delVal(&s);
    showSteak(&s);
    system("pause");
    return 0;
}

