#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int status;

typedef struct Node
{
    char e;
    struct Node *next;
} node;

typedef struct Steak
{
    node *top;
    node *base;
    int length;
} steak;

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

//压栈
status push(steak *s, char c)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->e = c;
    temp->next = s->top;
    s->top = temp;
    s->length += 1;
    return 0;
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

char pop(steak *s)
{
    node *temp = s->top;
    s->top = temp->next;
    s->length--;
    char c = temp->e;
    free(temp);
    return c;
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

//判断算式中是否有非法元素，并区分运算符和数字
status properity(char c)
{
    switch (c)
    {
    case '*':
    case '/':
    case '+':
    case '-':
        return 2;
        break;

    default:
        if (c >= '0' && c <= '9')
            return 1;
        else
            return 0;
        break;
    }
}

//前缀表达式运算
int function(steak *s)
{
    //存储数字
    steak opnd;
    initSteak(&opnd);
    //记录数字数
    char a, b;
    int len = s->length;
    node *temp = s->top;
    for (int i = 0; i < len; i++)
    {
        if (temp->e >= '0' && temp->e <= '9')
        {
            push(&opnd, temp->e - '0');
        }
        else
        {
            switch (temp->e)
            {
            case '+':
                a = pop(&opnd);
                b = pop(&opnd);
                push(&opnd, a + b);
                break;
            case '-':
                a = pop(&opnd);
                b = pop(&opnd);
                push(&opnd, a - b);
                break;
            case '*':
                a = pop(&opnd);
                b = pop(&opnd);
                push(&opnd, a * b);
                break;
            case '/':
                a = pop(&opnd);
                b = pop(&opnd);
                push(&opnd, a / b);
                break;
            }
        }
        temp = temp->next;
    }
    return pop(&opnd);
}
//从命令行接收值
status inputElem(steak *s)
{
    printf("请输入一段公式（以“#”结尾）:");
    char e;

    while (scanf("%c", &e) && e != '#')
    {
        if (properity(e))
            push(s, e);
        else
        {
            printf("表达式错误");
            exit(0);
        }
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    steak s;
    initSteak(&s);
    inputElem(&s);
    printf("%d\n", function(&s));
    system("pause");
    return 0;
}

