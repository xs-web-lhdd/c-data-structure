#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define MAXSTRLEN 255

typedef struct
{
    char ch[MAXSTRLEN + 1];
    int length;
} SString;

//简单(BF)模式匹配
int INDEX_BF(SString S, SString T, int pos)
{                       //S为主串，T为模式串,pos指的是在主串中的位置，初始值为1，最后返回找到的位置
    int i = pos, j = 1; //将pos的值赋给i，i是遍历主串的，j是遍历模式串的
    while (i <= S.length && j <= T.length)
    {
        printf("运行一遍\n");
        putchar(S.ch[i]);
        putchar(T.ch[j]);
        if (S.ch[i] == T.ch[j])
        {
            printf("运行2\n");
            ++i;
            ++j;
        }
        else
        {
            printf("运行3\n");
            i = i - j + 2;
            j = 1; //课上老师讲的BF算法
        }
    }
    if (j > T.length)
        return (i - T.length); //如果j大于字串的长度说明在主串中找到了模式串的位置，并且通过return返回给了pos
    else
    {
        printf("匹配失败\n");
        return 0;
    } //否者就是匹配失败
}

//计算next函数值
void get_next(SString T, int *next)
{
    //求模式串T的next函数值并存放数组next
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

//KMP算法的模式匹配

int INDEX_KMP(SString S, SString T, int pos)
{                       //S为主串，T为模式串,pos指的是在主串中的位置，初始值为1，最后返回找到的位置
    int i = pos, j = 1; //将pos的值赋给i，i是遍历主串的，j是遍历模式串的
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
        printf("匹配失败");
        return 0;
    } //否者就是匹配失败
}

//计算next函数修正值
void get_nextval(SString T, int nextval[])
{
    //求模式串T的next函数修正值并放入数组nextval
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

//修正后的KMP算法的模式匹配

int XINDEX_KMP(SString S, SString T, int pos)
{                       //S为主串，T为模式串,pos指的是在主串中的位置，初始值为1，最后返回找到的位置
    int i = pos, j = 1; //将pos的值赋给i，i是遍历主串的，j是遍历模式串的
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
        printf("匹配失败");
        return 0;
    } //否者就是匹配失败
}

int main()
{
    SString T;
    SString S;
    int lenT;
    int lenS;
    char s;
    char t;
    printf("请输入您主串的长度:\n");
    scanf("%d", &lenS);
    getchar();
    S.length = lenS;
    printf("请输入您的主串：\n");
    for (int i = 1; i <= lenS; ++i)
    {
        scanf("%c", &s);
        S.ch[i] = s;
    }
    getchar();
    printf("请输入您模式串的长度：\n");
    scanf("%d", &lenT);
    getchar();
    T.length = lenT;
    printf("请输入您的模式串:\n");
    for (int i = 1; i <= lenT; ++i)
    {
        scanf("%c", &t);
        T.ch[i] = t;
    }
    getchar();
    int ch = 0;
    printf("使用简单模式匹配请输入1\n使用KMP匹配请输入2\n使用修正后的KMP匹配请输入3\n");
    scanf("%d", &ch);
    getchar();
    if (ch == 1)
    {
        int i = 0;
        i = INDEX_BF(S, T, 1);
        printf("模式串在主串中的位置为：%d\n", i);
    }
    else if (ch == 2)
    {
        int i = 0;
        i = INDEX_KMP(S, T, 1);
        printf("模式串在主串中的位置为：%d\n", i);
    }
    else
    {
        int i = 0;
        i = XINDEX_KMP(S, T, 1);
        printf("模式串在主串中的位置为：%d\n", i);
    }
    system("pause");
}

