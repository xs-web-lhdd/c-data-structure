#include <iostream>
using namespace std;
const int N=1e2+10;
typedef char DataType;

//----------二叉树的二叉链表存储表示----------
typedef struct BiThrNode{
    DataType data;   //结点数据域
    struct BiThrNode *lchild,*rchild;    //左右孩子指针
    char LTag,RTag;
}BiThrNode,*BiThrTree;             //左右标志

BiThrTree T,q,Thrt;
BiThrTree p;
BiThrTree pre=NULL;


//--------栈---------
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



//----------建立一颗二叉树---------
void CreateBiThrTree(BiThrTree &T){    //创建二叉树，这里是先序遍历的顺序建立的二叉链表   递归形式
    cin>>ch;   //输入链表数据       输入 ABD##E##C##
    if(ch=='#') T=NULL;	//如果出现输入的是#，终止递归
    else{
        T=new BiThrNode;  //申请一个根节点
        T->data=ch;    //对根节点进行赋值
        CreateBiThrTree(T->lchild);   //递归创建左子树
        CreateBiThrTree(T->rchild);	//递归创建右子树
    }
}
//初始化栈
void InitStack(LinkStack &S){
    S=NULL;
}
//入栈
void push(LinkStack &S,BiThrTree e){
    p1=new StackNode;
    p1->data=e;
    p1->next=S;
    S=p1;
}
//出栈
void pop(LinkStack &S,BiThrTree &e){
    if(S==NULL) return ;
    e=S->data;
    S=S->next;
}
//判断栈是否为空
bool StackEmpty(LinkStack S){
    return S==NULL;
}
//先序遍历
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


//中序遍历
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


//后序遍历
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


//-----------统计二叉树中结点的个数-------
void TreeDu(BiThrTree T){//统计二叉树中T中的结点的个数
    p=T;
    int a=0,b=0;
    if(p==NULL) return ;
    else{
        if(T->lchild!=NULL) a++,TreeDu(T->lchild);
        if(T->rchild!=NULL) b++,TreeDu(T->rchild);
        num[a+b]++;
    }
}
//-------计算树的深度------
int Depth(BiThrTree T){
	//计算二叉树T的深度
    if(T==NULL) return 0;   //终止递归条件
    else{
        m=Depth(T->lchild);    //递归计算左子树的深度记为m
        n=Depth(T->rchild);    //递归计算右子树的深度记为n
        if(m>n) return (m+1);     //二叉树的深度为m与n的较大者加1
        else return (n+1);
    }
}


//--------以节点p为根的子树中序线索化-------
void InThreading(BiThrTree p){
	//pre是全局变量，初始化时其右孩子指针为空，便于在树的最左点开始建立线索
    if(p){
        InThreading(p->lchild);
        if(!p->lchild){   //给p加上左线索
            p->LTag=1;
            p->lchild=pre;    //p的左孩子指针指向pre（前驱）
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
	
	//T指向头节点，头节点的左链lchild指向根节点
    //中序遍历的非递归算法，对每个数据元素直接输出
    p=T->lchild;  //p指向根节点
    while(p!=T){
        while(p->LTag==0) p=p->lchild;  //沿左孩子向下
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
    cout<<"前序遍历--- \n";
    PreOrderTraverse(T);
    cout<<"中序遍历---\n";
    InOrderTraverse(T);
    cout<<"后序遍历---\n";
    PostOrderTraverse(T);
    cout<<"二叉树中度为0、1、2的结点个数为: ";
    TreeDu(T);
    cout<<num[0]<<" "<<num[1]<<" "<<num[2]<<endl;
    cout<<"树的深度为：";
    int Height=Depth(T)+1;
    cout<<Height<<endl;
    cout<<"中序线索化-----\n";
    InOrderThreading(Thrt,T);
    InOrderTraverse_Thr(Thrt);


    return 0;
}

