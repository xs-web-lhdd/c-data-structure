#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAXSIZE 100;

typedef int KeyType;

typedef struct BSTNode{
	KeyType key;					//������ ,�ؼ��� 
	struct BSTNode *lchild,*rchild;	//���Һ��� 
}BSTNode,*BSTtree;

//ջ�����ݽṹ
typedef struct{
	BSTtree *top;
	BSTtree *base;
	int stacksize;
}stack; 

//�ж�ջ�Ƿ�Ϊ��
int empty(stack s){
	if(s.top=s.base){
		return 1;
	}else{
		return 0;
	}
} 

//�ж��Ƿ�ջ��
int  full(stack s){
	if(s.top-s.base==s.stacksize){
		return 1;
	}else{
		return 0;
	}
}

//����ջ
int creatStack(stack &s){
	s.base=(BSTtree*)(malloc(sizeof(BSTNode)));
	if(!s.base){
		exit(-1);
	}
	s.top=s.base;
	s.stacksize=MAXSIZE;
	return 1;
} 

//��ջ
int push(stack &s,BSTtree b){
	if(full(s)){
		return 0;
	}
	*s.top=b;
	s.top++;
	return 1;
} 

//��ջ 
int pop(stack &s,BSTtree &b){
	if(empty(s)){
		return 0;
	}
	s.top--;
	b=*s.top;
	return 1; 
}
//�����������Ĳ���
int find(BSTtree T,KeyType k,BSTtree &p,BSTtree &f){
	f=NULL;
 	BSTtree temp=T;
 	if(!T){							//�����Ϊ�� 
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
		 p=f;						//���δ���ҵ�����pΪ���ҵ������һ����� 
		 return 0;
	}
}

void findNum(BSTtree T,KeyType k){
	BSTtree p=(BSTtree)(malloc(sizeof(BSTtree)));
	BSTtree f;
	if(find(T,k,p,f)){
		printf("���ҳɹ������Ϊ��%d",p->key);
	}else{
		printf("����ʧ��");
	}
}
 	
//�����������Ĳ��� 
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

//�����������Ĵ���
void creat(BSTtree &T){
	T=NULL;
	int num;
	KeyType key;
	printf("����������������Ľ������");
	scanf("%d",&num);
	printf("����������Ĺؼ��֣�");
	for(int i=0;i<num;i++){
		scanf("%d",&key);
		insert(key,T);
	}
} 

//�������������������
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


//������������ɾ��
int deleteN(BSTtree &T,KeyType k){
	if(!T){						//�����Ϊ�� 
		return 0;
	}else{
		BSTtree p=(BSTNode*)(malloc(sizeof(BSTNode)));
		BSTtree temp=(BSTNode*)(malloc(sizeof(BSTNode)));
		BSTtree q=(BSTNode*)(malloc(sizeof(BSTNode)));
		BSTtree f=(BSTtree)(malloc(sizeof(BSTtree)));
		find(T,k,p,f);
		if(p->key!=k){			//���û�в鵽Ҫɾ���Ľ�� 
			printf("δ�ҵ�Ҫɾ���Ľ��\n"); 
			return 0;
		}else{
			printf("Ҫɾ���Ľ����%d\n",p->key);			
			if(p->lchild&&p->rchild){		//������������Ϊ�� (�������������Ĺؼ���)	 
				printf("�ý��������������Ϊ��\n"); 
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
			}else if(!p->lchild){				//���������Ϊ�� ,�ؽ� ������ 
				printf("�ýڵ���������\n");
				temp=p;
				p=p->rchild;
			}else if(!p->rchild){				//���������Ϊ�գ��ؽ������� 
				printf("�ýڵ���������\n");
				temp=p;
				p=p->lchild;
			}else{								//�������������Ϊ��
				printf("�ýڵ�����������������\n"); 
				p=NULL;
			}
			if(!f){								//���ɾ�����Ϊ���ڵ� 
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
	printf("�������������������: ");
	order(T);
	printf("\n");
	printf("������Ҫ����Ĺؼ���: ");
	scanf("%d",&num);
	insert(num,T);
	printf("����ؼ��ֺ�Ķ��������������������");
	order(T);
	printf("\n");
	printf("������Ҫ���ҵĹؼ���: ");
	scanf("%d",&num);
	findNum(T,num);
	printf("\n");
	printf("������Ҫɾ���Ĺؼ���: "); 
	scanf("%d",&num);
	num=deleteN(T,num);
	if(num=1){
		printf("ɾ���ؼ��ֺ�Ķ��������������������");
		order(T);
	}

	return 1;
}

