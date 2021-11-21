#include <iostream>
using namespace std;
const int N=1e2+10;
typedef char DataType;

//----------�������Ķ�������洢��ʾ----------
typedef struct BiThrNode{
    DataType data;   //���������
    struct BiThrNode *lchild,*rchild;    //���Һ���ָ��
    char LTag,RTag;
}BiThrNode,*BiThrTree;             //���ұ�־

BiThrTree T,q,Thrt;
BiThrTree p;
BiThrTree pre=NULL;


//--------ջ---------
typedef struct StackNode{
    BiThrTree data;
    struct StackNode *next;
}StackNode,*LinkStack;



LinkStack p1;
LinkStack S;
char ch;
char arr[N];
int num[11];
int len=0,m=0,n=0;



//----------����һ�Ŷ�����---------
void CreateBiThrTree(BiThrTree &T){    //���������������������������˳�����Ķ�������   �ݹ���ʽ
    cin>>ch;   //������������       ���� ABD##E##C##
    if(ch=='#') T=NULL;	//��������������#����ֹ�ݹ�
    else{
        T=new BiThrNode;  //����һ�����ڵ�
        T->data=ch;    //�Ը��ڵ���и�ֵ
        CreateBiThrTree(T->lchild);   //�ݹ鴴��������
        CreateBiThrTree(T->rchild);	//�ݹ鴴��������
    }
}
//��ʼ��ջ
void InitStack(LinkStack &S){
    S=NULL;
}
//��ջ
void push(LinkStack &S,BiThrTree e){
    p1=new StackNode;
    p1->data=e;
    p1->next=S;
    S=p1;
}
//��ջ
void pop(LinkStack &S,BiThrTree &e){
    if(S==NULL) return ;
    e=S->data;
    S=S->next;
}
//�ж�ջ�Ƿ�Ϊ��
bool StackEmpty(LinkStack S){
    return S==NULL;
}
//�������
void PreOrderTraverse(BiThrTree T){
    InitStack(S);
    p=T;
    q=new BiThrNode;
    while(p||!StackEmpty(S)){
        if(p){
            cout<<p->data;
            push(S,p);
            p=p->lchild;
        }
        else{
            pop(S,q);
            p=q->rchild;
        }
    }
    cout<<endl;
}


//�������
void InOrderTraverse(BiThrTree T){
    InitStack(S);
    p=T;
    q=new BiThrNode;
    while(p||!StackEmpty(S)){
        if(p){
            push(S,p);
            p=p->lchild;
        }
        else{
            pop(S,q);
            cout<<q->data;
            p=q->rchild;
        }
    }
    cout<<endl;
}


//�������
void PostOrderTraverse(BiThrTree T){
    InitStack(S);
    p=T;
    q=new BiThrNode;
    while(p||!StackEmpty(S)){
        if(p){
            arr[++len]=p->data;
            push(S,p);
            p=p->rchild;
        }
        else{
            pop(S,q);
            p=q->lchild;
        }
    }
    for(int i=len;i>=1;i--) cout<<arr[i];
    cout<<endl;
}


//-----------ͳ�ƶ������н��ĸ���-------
void TreeDu(BiThrTree T){//ͳ�ƶ�������T�еĽ��ĸ���
    p=T;
    int a=0,b=0;
    if(p==NULL) return ;
    else{
        if(T->lchild!=NULL) a++,TreeDu(T->lchild);
        if(T->rchild!=NULL) b++,TreeDu(T->rchild);
        num[a+b]++;
    }
}
//-------�����������------
int Depth(BiThrTree T){
	//���������T�����
    if(T==NULL) return 0;   //��ֹ�ݹ�����
    else{
        m=Depth(T->lchild);    //�ݹ��������������ȼ�Ϊm
        n=Depth(T->rchild);    //�ݹ��������������ȼ�Ϊn
        if(m>n) return (m+1);     //�����������Ϊm��n�Ľϴ��߼�1
        else return (n+1);
    }
}


//--------�Խڵ�pΪ������������������-------
void InThreading(BiThrTree p){
	//pre��ȫ�ֱ�������ʼ��ʱ���Һ���ָ��Ϊ�գ���������������㿪ʼ��������
    if(p){
        InThreading(p->lchild);
        if(!p->lchild){   //��p����������
            p->LTag=1;
            p->lchild=pre;    //p������ָ��ָ��pre��ǰ����
        }
        else p->LTag=0;
        if(!pre->rchild){
            pre->RTag=1;
            pre->rchild=p;
        }
        else pre->RTag=0;
        pre=p;
        InThreading(p->rchild);
    }
}



void InOrderThreading(BiThrTree &Thrt,BiThrTree T){
    Thrt=new BiThrNode;
    Thrt->LTag=0;
    Thrt->RTag=1;
    Thrt->rchild=Thrt;
    if(!T) Thrt->lchild=Thrt;
    else{
        Thrt->lchild=T;
        pre=Thrt;
        InThreading(T);
        pre->rchild=Thrt;
        pre->RTag=1;
        Thrt->rchild=pre;
    }
}



void InOrderTraverse_Thr(BiThrTree T){
	
	//Tָ��ͷ�ڵ㣬ͷ�ڵ������lchildָ����ڵ�
    //��������ķǵݹ��㷨����ÿ������Ԫ��ֱ�����
    p=T->lchild;  //pָ����ڵ�
    while(p!=T){
        while(p->LTag==0) p=p->lchild;  //����������
        cout<<p->data;
        while(p->RTag==1&&p->rchild!=T){
            p=p->rchild;
            cout<<p->data;
        }
        p=p->rchild;
    }
    cout<<endl;

}
int main(){
    cout<<"satrting ------ \n";
    CreateBiThrTree(T);
    cout<<"ǰ�����--- \n";
    PreOrderTraverse(T);
    cout<<"�������---\n";
    InOrderTraverse(T);
    cout<<"�������---\n";
    PostOrderTraverse(T);
    cout<<"�������ж�Ϊ0��1��2�Ľ�����Ϊ: ";
    TreeDu(T);
    cout<<num[0]<<" "<<num[1]<<" "<<num[2]<<endl;
    cout<<"�������Ϊ��";
    int Height=Depth(T)+1;
    cout<<Height<<endl;
    cout<<"����������-----\n";
    InOrderThreading(Thrt,T);
    InOrderTraverse_Thr(Thrt);


    return 0;
}

