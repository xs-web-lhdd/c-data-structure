/**
*  有序顺序表的合并: 已知顺序表LA、LB中的数据元素按值非递减有序排列，
*  现要求将LA和LB归并为一个新的顺序表LC，且LC中的数据元素仍按值非递减有序排列
*/ 
#include<stdio.h> 
typedef int ElemType;
struct SqList                   //结构体 
{
    ElemType *elem; 
    int listsize;
    int length;
};
void InputData(SqList &LA)      //输入LA表数据 
{
    printf("请按升序输入一系列整数，用空格隔开，以-9999结尾：\n");
    int temp;
    for(int i=0;;i++)           //循环输入一系列整数 
    {
        scanf("%d",&temp);
        if(temp!=-9999)
        {
            LA.elem[i]=temp;
            LA.length++;
        }
        else
            break;
    }
}
void MergeList_Sq(SqList LA,SqList LB,SqList &LC)
{                                           //LA、LB中元素原来按非递减顺序存储要求合并后的LC也按照非递减序存储
    int i,j,k;
    i=j=k=0;                                //下面生成线性表LC
    LC.length=LA.length+LB.length;          //表LC长度 
    LC.listsize=LA.length+LB.length;        //？？？ 
    LC.elem=new ElemType[LC.listsize];       

    while(i<=LA.length-1 && j<=LB.length-1){//当LA、LB同时不为空时，进行下面操作
        ElemType pa=LA.elem[i];             //取LA的第i个元素
        ElemType pb=LB.elem[j];             //取LB的第j个元素
        if(pa<=pb) 
        {                                   //如果pa<=pb
            LC.elem[k]=pa;                  //pa插入LC尾部
            k++;i++;                        //LC、LA下标后移
}
        else
        {
            LC.elem[k]=pb;
            k++;j++;
        }
    }
    while(i<=LA.length-1)
    {                                       //如果LA中还有元素，则所有元素全部插入LC尾部
        ElemType pa=LA.elem[i];
        LC.elem[k]=pa;
        k++;i++;
    }
    while(j<=LB.length-1)
    {                                       //如果LB中还有元素，则所有元素全部插入LC尾部   
        ElemType pb=LB.elem[j];
        LC.elem[k]=pb;
        k++;j++;
    }
}
void print(SqList LC)               //输出合并后表LC的数据 
{
    for(int i=0;i<LC.length;i++)
        printf("%d ",LC.elem[i]);
    printf("\n");
}
int main(void)
{
    SqList LA,LB,LC;
    LA.elem=new ElemType[100];  //初始化LA 
    LA.length=0;
    LA.listsize=100;

    LB.elem=new ElemType[100];  //初始化LB 
    LB.length=0;
    LB.listsize=100;

    InputData(LA);              //输入表LA的数据 
    InputData(LB);              //输入表LB的数据 
    MergeList_Sq(LA,LB,LC);     //合并数据 
    print(LC);                  //输出数据  
}
