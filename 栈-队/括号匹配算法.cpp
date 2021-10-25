#include <stdio.h>
#include <stdlib.h>

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

//出栈： 
status pop(steak *s)
{
    node *temp = s->top;
    s->top = temp->next;
    s->length--;
    free(temp);
}

//检测输入的值括号是否配对
status mate(steak *s)
{
    //bracket 括号
    steak brackets;
    initSteak(&brackets);
    int len = s->length;
    node *temp = s->top;
    node *bracket = brackets.top;
    for (int i = 0; i < len; i++)
    {
        if (temp->e == ')' || temp->e == ']' || temp->e == '}')
        {
            push(&brackets, temp->e);
            bracket = brackets.top;
        }
        if (temp->e == '(' || temp->e == '[' || temp->e == '{')
        {
            switch (temp->e)
            {
            case '(':
                if (bracket->e != ')')
                {
                    putchar(bracket->e);
                    printf("括号不匹配\n");
                    return 0;
                }
                else
                {
                    bracket = bracket->next;
                    pop(&brackets);
                }
                break;
            case '[':
                if (bracket->e != ']')
                {
                    printf("括号不匹配\n");
                    return 0;
                }
                else
                {
                    bracket = bracket->next;
                    pop(&brackets);
                }
                break;
            case '{':
                if (bracket->e != '}')
                {
                    printf("括号不匹配\n");
                    return 0;
                }
                else
                {
                    bracket = bracket->next;
                    pop(&brackets);
                }
                break;
            }
        }
        temp = temp->next;
    }
    if (brackets.length > 0)
    {
        printf("括号不完全匹配\n");
        return 0;
    }
    printf("括号完全匹配\n");
    return 1;
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

int main(int argc, char const *argv[])
{
    steak s;
    initSteak(&s);
	
	inputElem(&s); 
	
    mate(&s);

    return 0;
}

