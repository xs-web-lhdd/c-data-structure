#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define MAXSTRLEN 255

typedef struct
{
    char ch[MAXSTRLEN + 1];
    int length;
} SString;

//��(BF)ģʽƥ��
int INDEX_BF(SString S, SString T, int pos)
{                       //SΪ������TΪģʽ��,posָ�����������е�λ�ã���ʼֵΪ1����󷵻��ҵ���λ��
    int i = pos, j = 1; //��pos��ֵ����i��i�Ǳ��������ģ�j�Ǳ���ģʽ����
    while (i <= S.length && j <= T.length)
    {
        printf("����һ��\n");
        putchar(S.ch[i]);
        putchar(T.ch[j]);
        if (S.ch[i] == T.ch[j])
        {
            printf("����2\n");
            ++i;
            ++j;
        }
        else
        {
            printf("����3\n");
            i = i - j + 2;
            j = 1; //������ʦ����BF�㷨
        }
    }
    if (j > T.length)
        return (i - T.length); //���j�����ִ��ĳ���˵�����������ҵ���ģʽ����λ�ã�����ͨ��return���ظ���pos
    else
    {
        printf("ƥ��ʧ��\n");
        return 0;
    } //���߾���ƥ��ʧ��
}

//����next����ֵ
void get_next(SString T, int *next)
{
    //��ģʽ��T��next����ֵ���������next
    int i = 1;
    next[1] = 0;
    int j = 0;
    while (i < T.length)
    {
        if (j == 0 || T.ch[i] == T.ch[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}

//KMP�㷨��ģʽƥ��

int INDEX_KMP(SString S, SString T, int pos)
{                       //SΪ������TΪģʽ��,posָ�����������е�λ�ã���ʼֵΪ1����󷵻��ҵ���λ��
    int i = pos, j = 1; //��pos��ֵ����i��i�Ǳ��������ģ�j�Ǳ���ģʽ����
    int next[MAXSTRLEN];
    get_next(T, next);
    while (i <= S.length && j <= T.length)
    {
        if (j == 0 || S.ch[i] == T.ch[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j > T.length)
        return (i - T.length);
    else
    {
        printf("ƥ��ʧ��");
        return 0;
    } //���߾���ƥ��ʧ��
}

//����next��������ֵ
void get_nextval(SString T, int nextval[])
{
    //��ģʽ��T��next��������ֵ����������nextval
    int i = 1;
    nextval[1] = 0;
    int j = 0;
    while (i < T.length)
    {
        if (j == 0 || T.ch[i] == T.ch[j])
        {
            ++i;
            ++j;
            if (T.ch[i] != T.ch[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        }
        else
            j = nextval[j];
    }
}

//�������KMP�㷨��ģʽƥ��

int XINDEX_KMP(SString S, SString T, int pos)
{                       //SΪ������TΪģʽ��,posָ�����������е�λ�ã���ʼֵΪ1����󷵻��ҵ���λ��
    int i = pos, j = 1; //��pos��ֵ����i��i�Ǳ��������ģ�j�Ǳ���ģʽ����
    int nextval[MAXSTRLEN];
    get_nextval(T, nextval);
    while (i <= S.length && j <= T.length)
    {
        if (j == 0 || S.ch[i] == T.ch[j])
        {
            i++;
            j++;
        }
        else
        {
            j = nextval[j];
        }
    }
    if (j > T.length)
        return (i - T.length);
    else
    {
        printf("ƥ��ʧ��");
        return 0;
    } //���߾���ƥ��ʧ��
}

int main()
{
    SString T;
    SString S;
    int lenT;
    int lenS;
    char s;
    char t;
    printf("�������������ĳ���:\n");
    scanf("%d", &lenS);
    getchar();
    S.length = lenS;
    printf("����������������\n");
    for (int i = 1; i <= lenS; ++i)
    {
        scanf("%c", &s);
        S.ch[i] = s;
    }
    getchar();
    printf("��������ģʽ���ĳ��ȣ�\n");
    scanf("%d", &lenT);
    getchar();
    T.length = lenT;
    printf("����������ģʽ��:\n");
    for (int i = 1; i <= lenT; ++i)
    {
        scanf("%c", &t);
        T.ch[i] = t;
    }
    getchar();
    int ch = 0;
    printf("ʹ�ü�ģʽƥ��������1\nʹ��KMPƥ��������2\nʹ���������KMPƥ��������3\n");
    scanf("%d", &ch);
    getchar();
    if (ch == 1)
    {
        int i = 0;
        i = INDEX_BF(S, T, 1);
        printf("ģʽ���������е�λ��Ϊ��%d\n", i);
    }
    else if (ch == 2)
    {
        int i = 0;
        i = INDEX_KMP(S, T, 1);
        printf("ģʽ���������е�λ��Ϊ��%d\n", i);
    }
    else
    {
        int i = 0;
        i = XINDEX_KMP(S, T, 1);
        printf("ģʽ���������е�λ��Ϊ��%d\n", i);
    }
    system("pause");
}

