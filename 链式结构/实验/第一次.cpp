#include <iostream>
#include<stdio.h>
#include<malloc.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 20
typedef int Status;

typedef struct{
    int *elem;
    int length;
}sqlist;

//��ʼ��
Status initlist(sqlist &L,int size){
    L.elem=new int[size];
    if(!L.elem){
        exit(OVERFLOW);
    }
    L.length=0;
    return OK;
}

//����
Status listInsert(sqlist &L,int i,int e){
    if((i<1)||(i>L.length+1)){
        printf("��������ȷ�Ĳ���λ��\n");
        return ERROR;
    }
    if(L.length==MAXSIZE){
        L.elem = (int *)malloc(sizeof(int)*(MAXSIZE));
    }
    for(int j=L.length-1;j>=i-1;j--){
        L.elem[j+1]=L.elem[j];
    }
    L.elem[i-1]=e;
    L.length++;
    return OK;

}

//ɾ��
Status listIndele(sqlist &L,int i,int &e){
    if((i<1)||(i>L.length)){
        printf("��������ȷ��ɾ��λ��\n");
        return ERROR;
    }
    e=L.elem[i-1];
    for(int j=i;j<=L.length-1;j++){
        L.elem[j-1]=L.elem[j];
    }
    L.length--;
    return OK;
}


//���
Status listInprint(sqlist L){
    for(int j=0;j<=L.length-1;j++){
        printf("%d",L.elem[j]);
        if(j!=L.length-1){
            printf(",");
        }
    }
    return OK;
}


//����
void sort(sqlist &L){
    int temp;
    for(int i=0;i<L.length-1;i++){
        for(int j=0;j<L.length-i-1;j++){
            if(L.elem[j]>L.elem[j+1]){
                temp=L.elem[j];
                L.elem[j]=L.elem[j+1];
                L.elem[j+1]=temp;
            }
        }
    }
}

//�ϲ� ˳���
void MergeList(sqlist La,sqlist Lb,sqlist &Lc){
    sort(La);
    sort(Lb);
    Lc.length=La.length+Lb.length;
    initlist(Lc,Lc.length);
    int *pa=La.elem;
    int *pb=Lb.elem;
    int *pa_last=La.elem+La.length-1;
    int *pb_last=Lb.elem+Lb.length-1;
    while((pa<=pa_last)&&(pb<=pb_last)){
        if(*pa>*pb){
            listInsert(Lc,Lc.length+1,*pb);
            pb++;
        }else{
            listInsert(Lc,Lc.length+1,*pa);
            pa++;

        }
    }
    while(pa<=pa_last){
        listInsert(Lc,Lc.length+1,*pa);
        pa++;
    }
    while(pb<=pb_last){
        listInsert(Lc,Lc.length+1,*pb);
        pb++;
    }
}

//����
void inverse(sqlist &Lc){
    int temp;
    for(int i=0;i<=(Lc.length-1)/2;i++){
        temp=Lc.elem[i];
        Lc.elem[i]=Lc.elem[Lc.length-1-i];
        Lc.elem[Lc.length-1-i]=temp;
    }
}

Status input(sqlist &L,int num){
	scanf("%d",&num);
    if(num>MAXSIZE){
        printf("��������ȷ����ֵ");
        return ERROR;
    }
    printf("��������ȫ����ֵ:");
    for(int i=0;i<num;i++){
        scanf("%d",&L.elem[i]);
        L.length++;
    }
}

int main(){
    int num;
    sqlist La,Lb,Lc;
    initlist(La,MAXSIZE);
    initlist(Lb,MAXSIZE);
    printf("������La����ֵ����(С�ڵ���%d)��",MAXSIZE);
    input(La,num);
    printf("������Lb����ֵ����(С�ڵ���%d)��",MAXSIZE);
    input(Lb,num);

    MergeList(La,Lb,Lc);
    listInprint(Lc);
    printf("\n");
    inverse(Lc);
    listInprint(Lc);

    return OK;
}


