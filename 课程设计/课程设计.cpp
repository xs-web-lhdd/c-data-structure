#include<bits/stdc++.h>
#include <string.h>
#define STACK_FIRST_SIZE 100
#define stack_addment 10
#define MAX_SIZE_OF_EXPRESSION 100 //֧�ֵı��ʽ������ַ�����
using namespace std;



// ��ȡ������ĺ����� 
char getOp (bool innerIsZero)
{
	char ops[] = {'+', '-', '*', '/'};
	// rand() �������������	���� 0 - 32767 
	return innerIsZero ? ops[rand() % 3] : ops[rand() % 4];
	
//  ע�⣺
	// rand() % 3 ����� 0 1 2 ������ ops[rand()%3] �����ܷ��� /
	// ͬ�� ops[rand() % 4] ���ܷ��� / 
}

// ��ȡ���ֵĺ����� ���� preIsDiv��ǰ������ǲ��ǳ��� 
char getOd(bool preIsDiv)
{
	char ops[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
	// ���ݴ���� preIsDiv �� true �� false	���ܲ��ܷ��� 0 
	return preIsDiv ? ops[rand() % 9] : ops[rand() % 10];
	
// ע�⣺������ 
    // rand() % 9  ����� 0-8 ������֮һ������	ops[rand() % 9] ���᷵�� 0 
    // rand() % 10  ����� 0-9 ������֮һ������	ops[rand() % 10] ���ܷ��� 0 
    // ��������� preIsDiv ���þ��ǿ��Ʒ��ص���������ܲ����� 0 ��
	//��� ǰ���������� / ��ô��������־Ͳ����� 0�����Դ� preIsDiv = true ���� 
}



// ���������ڵĽ���Ƿ��� 0���������һ�������ŵ��������ʽ���磺(3+4) 
double fune(string st) {
	int a, b;
	char c[5];
//	memset(c, 0, 5);

// c[0] = (    c[4] = )    c[1] = ��һ��������˹�������ʽ��    c[2] = ����    c[3] = �ڶ���������˹�������ʽ�� 
// ��Ϊ����������һ���ַ�����Ȼ���ַ���תΪ����������������������ÿһ�����һ���ַ���'0' �ڰ�˹�������� 48 
// 0 �İ�˹������ 48������������� 
 
//  c���Լ��ݣ���c������û��string���ͣ��ʱ���ͨ��string�����ĳ�Ա����c_str()��string ����ת����c�е��ַ�����ʽ��
	strcpy(c, st.c_str());
	a = c[1];
	b = c[3];
	switch(c[2]) {
		case '+': return a + b;
			      break;
		case '-': return a - b;
			      break;
		case '*': return a * b;
			      break;
		default: return a / b;
			      break; 
	}
}



// ���ʽ����������  ���� :: ��ʾ randomExcs ������ ss ���ڲ���Ա 
string randomExcs()
{
	// n Ϊ��ʼ���б�ĳ��ȣ���Ϊ��ʽ�������������� n Ҳ����������������ͨ�� % ���Կ��� n �Ĵ�СҲ���� ��ʽ �ĳ���	
	// ���� rend() %4 �� n ȡֵΪ 3��6��7��9 ֮һ��������ʽ���Ⱦ��� 3 6 7 9 ֮һ 
	int n = (1+rand()%10)*2+1;
	// ����һ������Ϊ n �ı��ʽ�����涼���Ϊ ' '�����ǿգ� 
	string expression(n, ' ');
	int left, right;
	if (n < 7) {
		// ��������ɵ��������ʽ�ĳ���С�� 7 ��ʱ�򣬲����� () ����	
		bool preIsDiv = false;
		int k;
		for(k = 0; k <= n-2; k++) {
			// ��Ϊ�������ʽ�Ŀ�ͷ��������������������ȵ��� getOd ��ȡһ���������			
			expression[k] = getOd(preIsDiv);
			// Ϊ��֤�����������ʽ����ȷ�ԣ������ֺ��治���������֣����Ե��� getOp ��ȡһ��������������			
			expression[++k] = getOp(false);
			// �����һ��������ɵ�������� / ��ô��һ��������ɵ����־Ͳ����� 0�����Խ��ⲿ preIsDiv �ĳ� true			
			preIsDiv = expression[k]=='/' ? true : false;
		}
		// ��ʽ���ʽ����������������ѭ����ż����ѭ�����������Ҫ����һ�� ���� ����ʽ���ʽ��β���ʵ���  getOd() ����һ������ 
		expression[k] = getOd(preIsDiv);
	} else if (n == 7) {
		// ��������ɵ���ʽ���ʽ�ĳ����� 7 ��ʱ�򣬳��� () ���ǣ�() ��λ���ǹ̶��ģ����ʽ����λ�� (������λ�� ) 
		left = 2;
		right = left + 4;
		// ���ʽ����λ�� (		
		expression[left] = '(';
		// ���ʽ����λ�� )
		expression[right] = ')';
		// ���������������λ���ʽ���磺3 + 4 
		
		// ���ʽ����λ��һ�����������		
		expression[(left + right) / 2] = getOp(false); // +
		expression[left + 1] = getOd(false); // 3
		bool preIsDiv = expression[(left + right) / 2] == '/' ? true : false; // ������ʽ / ��ô��λ������ 0������������� +�����Կ������� 0 
		expression[right - 1] = getOd(preIsDiv);
		
		// �� (3+4) �����һ�����ʽ 
		string inner(expression, left, right);
		
		// ����������ı��ʽ����ǲ��� 0		
		bool innerIsZero = fune(inner) == 0 ? true : false;
		// ������ɿ�ʼ����ǰ����������ʽ 		
		preIsDiv = false;
		for(int i = 0; i <= left - 2; i++) {
			expression[i] = getOd(preIsDiv);
			expression[++i] = getOp(false);
			preIsDiv = expression[i]=='/' ? true : false;
		}
		// ���ݺ�����������Ľ���ǲ��� 0�����ж�����ǰ��������������ܲ����� /  
		expression[left - 1] = getOp(innerIsZero);
		// ������ɽ������ź�����������ʽ 
		for(int j = right + 1; j <= n - 1; j++) {
			expression[j] = getOp(false);
			preIsDiv = expression[j] = '/' ? true : false;
			expression[++j] = getOd(preIsDiv);
		}
	} else {
		// ��������ɵ��������ʽ�ĳ��ȴ��� 7 ��ʱ��
		// �ö���������������ű��ʽ���磺(3+4) 
		// �����ŵ�λ�ö��� �������ʽ ���±� 0 ��ʼ�� ż�� ��λ�ã��� 2 4 ��������������� ż�� �����������ŵ�λ�� 
		left = (1 + rand() % 2) * 2;
		right = left + 4;
		expression[left] = '(';
		expression[right] = ')';
		expression[(left + right) / 2] = getOp(false);
		expression[left + 1] = getOd(false);
		bool preIsDiv = expression[(left + right) / 2] == '/' ? true : false;
		expression[right - 1] = getOd(preIsDiv);
		
		string inner(expression, left, right); // �� (3+4) ת��Ϊ�ַ�����ʽ��������������ֵ�ǲ��� 0  
		
		bool innerIsZero = fune(inner) == 0 ? true : false;
		// �ö������������������ǰ����������ʽ 
		preIsDiv = false;
		for(int i = 0; i <= left - 2; i++) {
			expression[i] = getOd(preIsDiv);
			expression[++i] = getOp(false);
			preIsDiv = expression[i]=='/' ? true : false;
		}
		expression[left - 1] = getOp(innerIsZero);
		// ������������������ź�����������ʽ 
		for(int j = right + 1; j <= n - 1; j++) {
			expression[j] = getOp(false);
			preIsDiv = expression[j] == '/' ? true : false;
			expression[++j] = getOd(preIsDiv);	
		}
	}
	// �����ɵ��������ʽ���� 
	return expression;
}


//����һ������ջ�Ľṹ��
typedef struct
{
	char op[MAX_SIZE_OF_EXPRESSION];
	int top;
}stack_op,*pstack_op;

//������ջ���
void clear_stack_op(pstack_op  s){
	s->top=-1;
}

//����ջѹջ
void push_op(pstack_op  s,char c){
	s->top++; 
	s->op[s->top]=c;
}

//��������ջ��ջ��Ԫ��
char pop_op(pstack_op  s){
    int i=s->top;
	s->top--;
    return s->op[i];
}

//�õ�����ջ��ջ��Ԫ��
char get_op_top(pstack_op  s){
    return s->op[s->top]; 
}

//�жϷ���ջ�Ƿ�Ϊ��
int is_stack_op_empty(pstack_op  s){
	if(s->top==-1){
	   return 1;//����ջΪ�� 
	}else{
	   return 0;//����ջ�ǿ� 
	}
}


//����һ��ջ����Ų�����
typedef struct
{
	float num[MAX_SIZE_OF_EXPRESSION];
	int top;
}stack_num,*pstack_num;

//��������ջ���
void clear_stack_num(pstack_num s){
	s->top=-1;
}

//������ѹջ
void push_num(pstack_num  s,float num){
	s->top++; 
	s->num[s->top]=num;
}

//����ջ���Ĳ����� 
float pop_num(pstack_num  s){
	int i=s->top;
	s->top--;
    return s->num[i];
}

//�õ�ջ��������
float get_num_top(pstack_num  s){
    return s->num[s->top]; 
}

//�жϲ�����ջ�Ƿ�Ϊ��
int is_stack_num_empty(pstack_num  s){
	if(s->top==-1){
	    return 1;//ջΪ�� 
	}else{
	   return 0;//ջ�ǿ� 
	}
}


//�ж��Ƿ�Ϊ���ֻ�С����
int is_digit(char x){
	if((x>='0'&&x<='9')||x=='.')
	{
	  return 1;
	}
	return 0;
}


// ����ֵ�� 
float Operate(float n1,float n2,char c_op)
{
   float r;
   switch(c_op)
   {
     case '+':  r=n1+n2;break;
     case '-':  r=n1-n2;break;
     case '*':  r=n1*n2;break;
     case '/':  r=n1/n2;break;
    }
    return r;
}



// �Ƚ����������������ȼ�  
char Precede(char c1,char c2){
  if(c1=='+')
  {
   if(c2=='+') return  '>';
    else if(c2=='-') return  '>';
    else if(c2=='*') return  '<';
    else if(c2=='/') return  '<';
    else if(c2=='(') return  '<';
    else if(c2==')') return  '>';
    else return  '>';
   }
  else if(c1=='-')
  {
   if(c2=='+') return  '>';
    else if(c2=='-') return  '>';
    else if(c2=='*') return  '<';
    else if(c2=='/') return  '<';
    else if(c2=='(') return  '<';
    else if(c2==')') return  '>';
    else return  '>';
   }
  else if(c1=='*')
  {
   if(c2=='+') return  '>';
    else if(c2=='-') return  '>';
    else if(c2=='*') return  '>';
    else if(c2=='/') return  '>';
    else if(c2=='(') return  '<';
    else if(c2==')') return  '>';
    else return  '>';
   }
   else if(c1=='/')
  {
   if(c2=='+') return  '>';
    else if(c2=='-') return  '>';
    else if(c2=='*') return  '>';
    else if(c2=='/') return  '>';
    else if(c2=='(') return  '<';
    else if(c2==')') return  '>';
    else return  '>';
   }
   else if(c1=='(')
  {
   if(c2=='+') return  '<';
    else if(c2=='-') return  '<';
    else if(c2=='*') return  '<';
    else if(c2=='/') return  '<';
    else if(c2=='(') return  '<';
    else return  '=';

   }
   else if(c1==')')
  {
   if(c2=='+') return  '>';
    else if(c2=='-') return  '>';
    else if(c2=='*') return  '>';
    else if(c2=='/') return  '>';
    else if(c2==')') return  '>';
    else return  '>';
   }
   else
  {
   if(c2=='+') return  '<';
    else if(c2=='-') return  '<';
    else if(c2=='*') return  '<';
    else if(c2=='/') return  '<';
    else if(c2=='(') return  '<';

    else return  '=';
   }
}


// ��׺���ʽת��׺���ʽ
// �㷨˼·����׺����׺���ʽ�в������Ĵ���һ�£���ɨ�赽��׺���ʽ������ʱֱ��������ɣ�������������������ȼ������ȼ��ߵ������������������㣩����һ����������ջS���Ƚ�S�ÿգ����롮#����������׺���ʽ�Ѵ�������mid[n] ������ɨ��mid[n]�и�����mid[i]�� x ��
//          ��x=��������ֱ�����x��
//          ��x=��#���������������������ջS���������ת��������
//          ��x=��)����������ջ���S���ӱ��ʽ�����,ֱ��ջ��=��(�������˵���
//          ��x=�������������ջ���ջS���������ֱ��ջ����<x��
//    ע�⣺��ͬ�Ĳ�����֮���ÿո��
void Mid_Post(const char*  mid_expression,char* post_expression){
int i=1,j=0;
char x,ch_precede;
 
   stack_op st_op;//����ջ 
   clear_stack_op(&st_op);//�ÿ�ջ
   push_op(&st_op,'#');
    
   while(is_stack_op_empty(&st_op)==0){//����ջ�ǿ� 
       x=mid_expression[i];
       if( is_digit(x)){
          do{
             post_expression[j++]=x;
              i++;
             x=mid_expression[i];
          }while(is_digit(x));
          post_expression[j++]=' ';//����֮���ÿո�� 
       }else if(x=='#'){
          while(!is_stack_op_empty(&st_op)){//����ջ�ǿ� 
             post_expression[j++]=pop_op(&st_op);
          }
       }else if(x==')'){
          while(get_op_top(&st_op)!='('){
             post_expression[j++]=pop_op(&st_op);
          }
          pop_op(&st_op);//��"("���� 
          i++;
       }else if(x==' '){
          //do nothing 
       }else{
          while((ch_precede=Precede(get_op_top(&st_op),x))!='<'){
             post_expression[j++]=pop_op(&st_op);
          }
          push_op(&st_op,x);
          i++;
       }
   } 
}




//   �����׺���ʽ��ֵ 
//   �㷨˼·���������ջst_num,�Ƚ����ÿ�,Ȼ��ɨ���׺���ʽ�и�������x��
// ��x=��������ֱ�ӽ�ջ��
// ��x=�������b=Pop(&st_num)��a=Pop(&st_num)����a��b����x������,����ٽ�ջ��
// ��x=��#�����㷨���������ջ���������ʽ�����
float PostCount(const char * post_expression){
    int i=0,j=0;
    char x;
    char num_temp[MAX_SIZE_OF_EXPRESSION];//��ʱ����ַ��͵����֣�����ת���ɸ����� 
    float y,result,a,b; 
   stack_num st_num;//��Ų����� 
   clear_stack_num(&st_num);
    
   while(post_expression[i]!='#'){
       x=post_expression[i];
//       cout<<x<<"\n";
   if(is_digit(x)){
   		  // �� x ���ǲ�������+-*/����ʱ������������� 
          do{
             num_temp[j++]=x;
              i++;
             x=post_expression[i];
//             cout<<x<<"\n"; 
          }while(x!=' ');
          num_temp[j]='\0';
          y=atof(&num_temp[0]);//ת������ֵ����ջ
          push_num(&st_num,y);
          j=0;
          i++;
       }else{
          b=pop_num(&st_num); a=pop_num(&st_num);//ȡ��������
          result=Operate(a,b,x);
          push_num(&st_num,result);
          i++;
       }
    }
   if(!is_stack_num_empty(&st_num)){
      return get_num_top(&st_num);
   } 
    
}

// ���Լ������ʽ���ʽ��ֵ�� 
double computd(string suanshi)
{
//���������������������׺�ͺ�׺���ʽ
char mid_expression[MAX_SIZE_OF_EXPRESSION],post_expression[MAX_SIZE_OF_EXPRESSION]; 
//char if_continue='y';//�����ж��Ƿ���� 
char ch_in;//�����洢������ַ� 
float result=0.0;
int i=1;

mid_expression[0]='#';

int k = 0;
while(ch_in=suanshi[k])
{
	if(i< MAX_SIZE_OF_EXPRESSION){
        mid_expression[i++]=ch_in;
        k++;
    }else{
        cout<<"����ı��ʽ������Χ,�����볤��С��"<<MAX_SIZE_OF_EXPRESSION<<"�ı��ʽ\n";
        system("pause");
        return -1; 
    }
    if(ch_in=='#'){
        // �� # ��βʱ������ѭ�� 
    	break;
    }
}

i=1;
   
Mid_Post(mid_expression,post_expression);
       
result=PostCount(post_expression);


return result;
}






// ������ 
void mainProgram() {
    // ����������������������� 
	srand((unsigned) time(NULL));
	int n;
	float num = 0;
	double youresult, score;
	int firstInput = 0; 
	string suanshi;
	cout<<"**********************************************************************************\n"; 
	cout<<"***********************************�������Գ���***********************************\n"; 
	cout<<"**********************************************************************************\n"; 

	int flag, input_flag, first_input = 0;
	do{
        if(first_input == 0) {
        	cout<<"��������Ŀ���������� 1 �⣬��� 100 �⣺";
        	first_input = 1;
        }
        if(!scanf("%d",&n))
        {
        	printf("\n�������������������룺");
        	// ������뻺�� 
            fflush(stdin); 
			flag = 0;
        }
		else{
			if(n>=1 && n<=100)    /*�ж��������ֵĺϷ���*/
        	{
            	flag = 1;
				break;
        	}else {
        		cout<<"\n�������������������룺";
        	}
		} 
	}while(flag == 0);
	cout<<"\n";
	
	for (int i = 0; i < n; i++) {
		suanshi = randomExcs();
		cout<<"��"<<i+1<<"�⣺"<<suanshi<<"\n";
		double result = computd(suanshi+'#');
		cout<<"���Լ�����Ϊ:"<<result<<"\n";
		char p[100];
		memset(p, 0, 100);
		// �� suanshi.c_str() ���Ƶ� p ����		
		strcpy(p, suanshi.c_str());
		cout<<suanshi<<"=��";
		do{
        	if(!scanf("%d",&youresult))
        	{
        		printf("\n�������ʽ������������ȷ�ĸ�ʽ��");
            	fflush(stdin);
				input_flag = 0;
        	}else {
        	    input_flag = 1;
				break;
        	}
		}while(input_flag == 0);
		
		if(youresult == result) {
			// �����ȷ�������ȷ�����ҽ��Ե������� 1		
			cout<<"��ȷ��\n"<<endl;
			num++;
		} else {
			cout<<"������ȷ���ǣ�"<<result<<"\n\n";
		}
	}

	score = num / n * 100;
	cout<<"\n��ĳɼ�Ϊ��"<<score<<"\n"<<endl;
	cout<<"**********************************************************************************\n"; 
	cout<<"*********************************  ����  *****************************************\n"; 
	cout<<"**********************************************************************************\n"; 
}

int main(){
	mainProgram(); 
    return 0;
}






