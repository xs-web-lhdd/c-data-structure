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

//��ջ�� 
status pop(steak *s)
{
    node *temp = s->top;
    s->top = temp->next;
    s->length--;
    free(temp);
}

//��������ֵ�����Ƿ����
status mate(steak *s)
{
    //bracket ����
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
                    printf("���Ų�ƥ��\n");
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
                    printf("���Ų�ƥ��\n");
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
                    printf("���Ų�ƥ��\n");
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
        printf("���Ų���ȫƥ��\n");
        return 0;
    }
    printf("������ȫƥ��\n");
    return 1;
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

int main(int argc, char const *argv[])
{
    steak s;
    initSteak(&s);
	
	inputElem(&s); 
	
    mate(&s);

    return 0;
}

