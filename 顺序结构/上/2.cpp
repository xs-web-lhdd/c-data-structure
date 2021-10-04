/**
*  ����˳���ĺϲ�: ��֪˳���LA��LB�е�����Ԫ�ذ�ֵ�ǵݼ��������У�
*  ��Ҫ��LA��LB�鲢Ϊһ���µ�˳���LC����LC�е�����Ԫ���԰�ֵ�ǵݼ���������
*/ 
#include<stdio.h> 
typedef int ElemType;
struct SqList                   //�ṹ�� 
{
    ElemType *elem; 
    int listsize;
    int length;
};
void InputData(SqList &LA)      //����LA������ 
{
    printf("�밴��������һϵ���������ÿո��������-9999��β��\n");
    int temp;
    for(int i=0;;i++)           //ѭ������һϵ������ 
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
{                                           //LA��LB��Ԫ��ԭ�����ǵݼ�˳��洢Ҫ��ϲ����LCҲ���շǵݼ���洢
    int i,j,k;
    i=j=k=0;                                //�����������Ա�LC
    LC.length=LA.length+LB.length;          //��LC���� 
    LC.listsize=LA.length+LB.length;        //������ 
    LC.elem=new ElemType[LC.listsize];       

    while(i<=LA.length-1 && j<=LB.length-1){//��LA��LBͬʱ��Ϊ��ʱ�������������
        ElemType pa=LA.elem[i];             //ȡLA�ĵ�i��Ԫ��
        ElemType pb=LB.elem[j];             //ȡLB�ĵ�j��Ԫ��
        if(pa<=pb) 
        {                                   //���pa<=pb
            LC.elem[k]=pa;                  //pa����LCβ��
            k++;i++;                        //LC��LA�±����
}
        else
        {
            LC.elem[k]=pb;
            k++;j++;
        }
    }
    while(i<=LA.length-1)
    {                                       //���LA�л���Ԫ�أ�������Ԫ��ȫ������LCβ��
        ElemType pa=LA.elem[i];
        LC.elem[k]=pa;
        k++;i++;
    }
    while(j<=LB.length-1)
    {                                       //���LB�л���Ԫ�أ�������Ԫ��ȫ������LCβ��   
        ElemType pb=LB.elem[j];
        LC.elem[k]=pb;
        k++;j++;
    }
}
void print(SqList LC)               //����ϲ����LC������ 
{
    for(int i=0;i<LC.length;i++)
        printf("%d ",LC.elem[i]);
    printf("\n");
}
int main(void)
{
    SqList LA,LB,LC;
    LA.elem=new ElemType[100];  //��ʼ��LA 
    LA.length=0;
    LA.listsize=100;

    LB.elem=new ElemType[100];  //��ʼ��LB 
    LB.length=0;
    LB.listsize=100;

    InputData(LA);              //�����LA������ 
    InputData(LB);              //�����LB������ 
    MergeList_Sq(LA,LB,LC);     //�ϲ����� 
    print(LC);                  //�������  
}
