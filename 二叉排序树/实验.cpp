#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAXSIZE 100;

typedef int KeyType;

typedef struct BSTNode{
	KeyType key;					//数据域 ,关键字 
	struct BSTNode *lchild,*rchild;	//左右孩子 
}BSTNode,*BSTtree;

//栈的数据结构
typedef struct{
	BSTtree *top;
	BSTtree *base;
	int stacksize;
}stack; 

//判断栈是否为空
int empty(stack s){
	if(s.top=s.base){
		return 1;
	}else{
		return 0;
	}
} 

//判断是否栈满
int  full(stack s){
	if(s.top-s.base==s.stacksize){
		return 1;
	}else{
		return 0;
	}
}

//创建栈
int creatStack(stack &s){
	s.base=(BSTtree*)(malloc(sizeof(BSTNode)));
	if(!s.base){
		exit(-1);
	}
	s.top=s.base;
	s.stacksize=MAXSIZE;
	return 1;
} 

//入栈
int push(stack &s,BSTtree b){
	if(full(s)){
		return 0;
	}
	*s.top=b;
	s.top++;
	return 1;
} 

//出栈 
int pop(stack &s,BSTtree &b){
	if(empty(s)){
		return 0;
	}
	s.top--;
	b=*s.top;
	return 1; 
}
//二叉排序树的查找
int find(BSTtree T,KeyType k,BSTtree &p,BSTtree &f){
	f=NULL;
 	BSTtree temp=T;
 	if(!T){							//如果树为空 
 		p=f;							
 		return 0;
	 }else{
	 	while(temp){
	 		if(temp->key==k){
	 			p=temp;
	 			return 1;
			 }else if(temp->key>k){
			 	f=temp;
			 	temp=temp->lchild;
			 }else if(temp->key<k){
			 	f=temp;
			 	temp=temp->rchild;
			 }
		 }
		 p=f;						//如果未查找到，则p为查找到的最后一个结点 
		 return 0;
	}
}

void findNum(BSTtree T,KeyType k){
	BSTtree p=(BSTtree)(malloc(sizeof(BSTtree)));
	BSTtree f;
	if(find(T,k,p,f)){
		printf("查找成功，结果为：%d",p->key);
	}else{
		printf("查找失败");
	}
}
 	
//二叉排序树的插入 
int insert(KeyType k,BSTtree &T){
	BSTtree p=(BSTtree)(malloc(sizeof(BSTtree)));
	BSTtree f=(BSTtree)(malloc(sizeof(BSTtree)));
	if(!find(T,k,p,f)){
		BSTtree n=(BSTNode*)(malloc(sizeof(BSTNode)));
		n->key=k;
		n->lchild=n->rchild=NULL;
		if(!p){
			T=n;
		}else if(p->key>k){
			p->lchild=n;
		}else if(p->key<k){
			p->rchild=n;
		}
		return 1;
	}
	return 0;
}

//二叉排序树的创建
void creat(BSTtree &T){
	T=NULL;
	int num;
	KeyType key;
	printf("请输入二叉排序树的结点数：");
	scanf("%d",&num);
	printf("请输入各结点的关键字：");
	for(int i=0;i<num;i++){
		scanf("%d",&key);
		insert(key,T);
	}
} 

//二叉排序树的中序遍历
void Order(BSTtree T){
	stack s;
	BSTtree t=T;
	BSTtree temp=(BSTNode*)(malloc(sizeof(BSTNode)));
	creatStack(s);
	while(t||empty(s)){
		if(t){
			push(s,t);
			t=t->lchild;
		}else{
			printf("1\n");
			pop(s,temp);
			printf("%d\n",temp->key);
			t=temp->rchild;
		
		}
	}
}
void order(BSTtree T){
	if(T){
		order(T->lchild);
		printf("%d ",T->key);
		order(T->rchild);
	}
}


//二叉排序树的删除
int deleteN(BSTtree &T,KeyType k){
	if(!T){						//如果树为空 
		return 0;
	}else{
		BSTtree p=(BSTNode*)(malloc(sizeof(BSTNode)));
		BSTtree temp=(BSTNode*)(malloc(sizeof(BSTNode)));
		BSTtree q=(BSTNode*)(malloc(sizeof(BSTNode)));
		BSTtree f=(BSTtree)(malloc(sizeof(BSTtree)));
		find(T,k,p,f);
		if(p->key!=k){			//如果没有查到要删除的结点 
			printf("未找到要删除的结点\n"); 
			return 0;
		}else{
			printf("要删除的结点是%d\n",p->key);			
			if(p->lchild&&p->rchild){		//左右子树都不为空 (找左子树中最大的关键字)	 
				printf("该结点左右子树都不为空\n"); 
				temp=p;
				q=p->lchild;
				while(q->rchild){
					temp=q;
					q=q->rchild;
				}
				p->key=q->key;
				if(temp!=p){
					temp->rchild=q->lchild;
				}else{
					temp->lchild=q->lchild;
				}
				free(q);
				return 1;
			}else if(!p->lchild){				//如果左子树为空 ,重接 右子树 
				printf("该节点无左子树\n");
				temp=p;
				p=p->rchild;
			}else if(!p->rchild){				//如果右子树为空，重接左子树 
				printf("该节点无右子树\n");
				temp=p;
				p=p->lchild;
			}else{								//如果左右子树都为空
				printf("该节点无左子树和右子树\n"); 
				p=NULL;
			}
			if(!f){								//如果删除结点为根节点 
				T=p;
			}else if(temp==f->lchild){
				f->lchild=p; 
			}else if(temp=f->rchild){
				f->rchild=p;
			}
			free(temp);			
			return 1;
		}
	}
	
	
	
} 

int main(){
	int num;
	BSTtree T=(BSTNode*)(malloc(sizeof(BSTNode)));
	creat(T);
	printf("二叉排序树的中序遍历: ");
	order(T);
	printf("\n");
	printf("请输入要插入的关键字: ");
	scanf("%d",&num);
	insert(num,T);
	printf("插入关键字后的二叉排序树的中序遍历：");
	order(T);
	printf("\n");
	printf("请输入要查找的关键字: ");
	scanf("%d",&num);
	findNum(T,num);
	printf("\n");
	printf("请输入要删除的关键字: "); 
	scanf("%d",&num);
	num=deleteN(T,num);
	if(num=1){
		printf("删除关键字后的二叉排序树的中序遍历：");
		order(T);
	}

	return 1;
}

