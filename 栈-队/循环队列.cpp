#include <stdio.h>
#include <stdlib.h>

typedef int status;

// 元素： 
typedef struct Node
{
    char e;
    struct Node *next;
} node;

// 栈： 
typedef struct Steak
{
    node *top;
    node *base;
    int length;
} steak;

// 队： 
typedef struct Queue
{
    node *front;
    node *rear;
    int length;
} queue;

//对栈进行初始化
status initSteak(steak *s)
{
    s->base = (node *)malloc(sizeof(node));
    s->top = s->base;
    s->length = 0;
    if (s->base == NULL)
    {
        printf("栈初始化失败");
        return -1;
    }
    return 0;
}

//对队列进行初始化
status initQueue(queue *q)
{
    q->front = (node *)malloc(sizeof(node));
    q->rear = q->front;
    if (q->front == NULL)
    {
        printf("队列初始化失败");
    }
    q->length = 0;
    return 0;
}

//入栈： 
status push(steak *s, char c)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->e = c;
    temp->next = s->top;
    s->top = temp;
    s->length += 1;
    return 0;
}
//入队： 
status quePush(queue *q, char c)
{
    q->rear->e = c;
    node *e = (node *)malloc(sizeof(node));
    q->rear->next = e;
    q->rear = e;
    q->length++;
}

//输出栈中所有的元素
status showSteak(steak *s)
{
    printf("展示栈中的公式：\n");
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

//出栈： 
char pop(steak *s)
{
    node *temp = s->top;
    s->top = temp->next;
    s->length--;
    char c = temp->e;
    free(temp);
    return c;
}

//出队
char quePop(queue *q)
{
    node *e = q->front;
    q->front = e->next;
    q->length--;
    char c = e->e;
    free(e);
    return c;
}

//从命令行接收值
status inputElem(steak *s)
{
    printf("请输入一段公式（以“#”结尾）:");
    char e;

    while (scanf("%c", &e) && e != '#')
    {
        push(s, e);
    }
    return 1;
}
//对原来的栈进行倒置
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

//从栈中删除对应的值
status delVal(steak *s)
{
    int len = s->length;
    queue q;
    initQueue(&q);
    char c, a;
    node *temp = s->top;
    printf("请输入要删除的值：");
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
        printf("栈中没有对应的值");
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

