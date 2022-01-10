#include<bits/stdc++.h>
#include <string.h>
#define STACK_FIRST_SIZE 100
#define stack_addment 10
#define MAX_SIZE_OF_EXPRESSION 100 //支持的表达式的最长的字符长度
using namespace std;



// 获取运算符的函数： 
char getOp (bool innerIsZero)
{
	char ops[] = {'+', '-', '*', '/'};
	// rand() 随机数产生函数	生成 0 - 32767 
	return innerIsZero ? ops[rand() % 3] : ops[rand() % 4];
	
//  注意：
	// rand() % 3 结果是 0 1 2 ，所以 ops[rand()%3] 不可能返回 /
	// 同理 ops[rand() % 4] 可能返回 / 
}

// 获取数字的函数： 参数 preIsDiv：前面的数是不是除号 
char getOd(bool preIsDiv)
{
	char ops[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
	// 根据传入的 preIsDiv 的 true 或 false	看能不能返回 0 
	return preIsDiv ? ops[rand() % 9] : ops[rand() % 10];
	
// 注意：！！！ 
    // rand() % 9  结果是 0-8 中整数之一，所以	ops[rand() % 9] 不会返回 0 
    // rand() % 10  结果是 0-9 中整数之一，所以	ops[rand() % 10] 可能返回 0 
    // 这个函数传 preIsDiv 作用就是控制返回的随机数字能不能是 0 ，
	//如果 前面的运算符是 / 那么后面的数字就不能是 0，所以传 preIsDiv = true 即可 
}



// 检验括号内的结果是否是 0，传入的是一个带括号的算数表达式，如：(3+4) 
double fune(string st) {
	int a, b;
	char c[5];
//	memset(c, 0, 5);

// c[0] = (    c[4] = )    c[1] = 第一个数（阿斯克码的形式）    c[2] = 符号    c[3] = 第二个数（阿斯克码的形式） 
// 因为传进来的是一个字符串，然后将字符串转为数组存放起来，所以数组中每一项就是一个字符，'0' 在阿斯克码中是 48 
// 0 的阿斯克码是 48，其他依次相加 
 
//  c语言兼容，在c语言中没有string类型，故必须通过string类对象的成员函数c_str()把string 对象转换成c中的字符串样式。
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



// 表达式产生函数：  其中 :: 表示 randomExcs 函数是 ss 的内部成员 
string randomExcs()
{
	// n 为初始化列表的长度，因为算式都是奇数，所以 n 也必须是奇数，另外通过 % 可以控制 n 的大小也就是 算式 的长度	
	// 这里 rend() %4 故 n 取值为 3、6、7、9 之一，所以算式长度就是 3 6 7 9 之一 
	int n = (1+rand()%10)*2+1;
	// 生成一个长度为 n 的表达式，里面都填充为 ' '（就是空） 
	string expression(n, ' ');
	int left, right;
	if (n < 7) {
		// 当随机生成的算术表达式的长度小于 7 的时候，不会有 () 出现	
		bool preIsDiv = false;
		int k;
		for(k = 0; k <= n-2; k++) {
			// 因为算数表达式的开头不可能是运算符，所以先调用 getOd 获取一个随机数字			
			expression[k] = getOd(preIsDiv);
			// 为保证生成算数表达式的正确性，即数字后面不能再是数字，所以调用 getOp 获取一个随机算数运算符			
			expression[++k] = getOp(false);
			// 如果上一个随机生成的运算符是 / 那么下一个随机生成的数字就不能是 0，所以将外部 preIsDiv 改成 true			
			preIsDiv = expression[k]=='/' ? true : false;
		}
		// 算式表达式长度是奇数，上面循环是偶数次循环，所以最后要加上一个 数字 将算式表达式结尾，故调用  getOd() 生成一个数字 
		expression[k] = getOd(preIsDiv);
	} else if (n == 7) {
		// 当随机生成的算式表达式的长度是 7 的时候，出现 () 但是，() 的位置是固定的，表达式第三位是 (，第七位是 ) 
		left = 2;
		right = left + 4;
		// 表达式第三位是 (		
		expression[left] = '(';
		// 表达式第七位是 )
		expression[right] = ')';
		// 生成括号里面的三位表达式，如：3 + 4 
		
		// 表达式第五位是一个算数运算符		
		expression[(left + right) / 2] = getOp(false); // +
		expression[left + 1] = getOd(false); // 3
		bool preIsDiv = expression[(left + right) / 2] == '/' ? true : false; // 如果表达式 / 那么该位不会是 0，这个例子中是 +，所以可以生成 0 
		expression[right - 1] = getOd(preIsDiv);
		
		// 将 (3+4) 保存成一个表达式 
		string inner(expression, left, right);
		
		// 计算括号里的表达式结果是不是 0		
		bool innerIsZero = fune(inner) == 0 ? true : false;
		// 随机生成开始括号前面的算术表达式 		
		preIsDiv = false;
		for(int i = 0; i <= left - 2; i++) {
			expression[i] = getOd(preIsDiv);
			expression[++i] = getOp(false);
			preIsDiv = expression[i]=='/' ? true : false;
		}
		// 根据后面括号里面的结果是不是 0，来判断括号前面的算数操作符能不能是 /  
		expression[left - 1] = getOp(innerIsZero);
		// 随机生成结束括号后面的算术表达式 
		for(int j = right + 1; j <= n - 1; j++) {
			expression[j] = getOp(false);
			preIsDiv = expression[j] = '/' ? true : false;
			expression[++j] = getOd(preIsDiv);
		}
	} else {
		// 当随机生成的算术表达式的长度大于 7 的时候
		// 该段语句用于生成括号表达式，如：(3+4) 
		// 左括号的位置都是 算术表达式 以下标 0 开始的 偶数 的位置，如 2 4 ，该语句用来生成 偶数 ，用于左括号的位置 
		left = (1 + rand() % 2) * 2;
		right = left + 4;
		expression[left] = '(';
		expression[right] = ')';
		expression[(left + right) / 2] = getOp(false);
		expression[left + 1] = getOd(false);
		bool preIsDiv = expression[(left + right) / 2] == '/' ? true : false;
		expression[right - 1] = getOd(preIsDiv);
		
		string inner(expression, left, right); // 将 (3+4) 转化为字符串形式，方便计算里面的值是不是 0  
		
		bool innerIsZero = fune(inner) == 0 ? true : false;
		// 该段语句用于生成左括号前面的算数表达式 
		preIsDiv = false;
		for(int i = 0; i <= left - 2; i++) {
			expression[i] = getOd(preIsDiv);
			expression[++i] = getOp(false);
			preIsDiv = expression[i]=='/' ? true : false;
		}
		expression[left - 1] = getOp(innerIsZero);
		// 该语段用于生成右括号后面的算数表达式 
		for(int j = right + 1; j <= n - 1; j++) {
			expression[j] = getOp(false);
			preIsDiv = expression[j] == '/' ? true : false;
			expression[++j] = getOd(preIsDiv);	
		}
	}
	// 将生成的算数表达式返回 
	return expression;
}


//定义一个符号栈的结构体
typedef struct
{
	char op[MAX_SIZE_OF_EXPRESSION];
	int top;
}stack_op,*pstack_op;

//将符号栈清空
void clear_stack_op(pstack_op  s){
	s->top=-1;
}

//符号栈压栈
void push_op(pstack_op  s,char c){
	s->top++; 
	s->op[s->top]=c;
}

//弹出符号栈的栈顶元素
char pop_op(pstack_op  s){
    int i=s->top;
	s->top--;
    return s->op[i];
}

//得到符号栈的栈顶元素
char get_op_top(pstack_op  s){
    return s->op[s->top]; 
}

//判断符号栈是否为空
int is_stack_op_empty(pstack_op  s){
	if(s->top==-1){
	   return 1;//符号栈为空 
	}else{
	   return 0;//符号栈非空 
	}
}


//定义一个栈，存放操作数
typedef struct
{
	float num[MAX_SIZE_OF_EXPRESSION];
	int top;
}stack_num,*pstack_num;

//将操作数栈清空
void clear_stack_num(pstack_num s){
	s->top=-1;
}

//操作数压栈
void push_num(pstack_num  s,float num){
	s->top++; 
	s->num[s->top]=num;
}

//弹出栈顶的操作数 
float pop_num(pstack_num  s){
	int i=s->top;
	s->top--;
    return s->num[i];
}

//得到栈顶操作数
float get_num_top(pstack_num  s){
    return s->num[s->top]; 
}

//判断操作数栈是否为空
int is_stack_num_empty(pstack_num  s){
	if(s->top==-1){
	    return 1;//栈为空 
	}else{
	   return 0;//栈非空 
	}
}


//判断是否为数字或小数点
int is_digit(char x){
	if((x>='0'&&x<='9')||x=='.')
	{
	  return 1;
	}
	return 0;
}


// 计算值： 
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



// 比较两个操作符的优先级  
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


// 中缀表达式转后缀表达式
// 算法思路：中缀、后缀表达式中操作数的次序一致，故扫描到中缀表达式操作数时直接输出即可；对于运算符，视其优先级别，优先级高的运算符先输出（先运算）；设一存放运算符的栈S，先将S置空，存入‘#’。另设中缀表达式已存入数组mid[n] 。依次扫描mid[n]中各分量mid[i]送 x ：
//          若x=操作数，直接输出x；
//          若x=‘#’（结束符），依次输出栈S中运算符，转换结束；
//          若x=‘)’，反复退栈输出S中子表达式运算符,直到栈顶=‘(’，并退掉；
//          若x=运算符，反复退栈输出栈S中运算符，直到栈顶符<x。
//    注意：不同的操作数之间用空格格开
void Mid_Post(const char*  mid_expression,char* post_expression){
int i=1,j=0;
char x,ch_precede;
 
   stack_op st_op;//符号栈 
   clear_stack_op(&st_op);//置空栈
   push_op(&st_op,'#');
    
   while(is_stack_op_empty(&st_op)==0){//符号栈非空 
       x=mid_expression[i];
       if( is_digit(x)){
          do{
             post_expression[j++]=x;
              i++;
             x=mid_expression[i];
          }while(is_digit(x));
          post_expression[j++]=' ';//数字之间用空格格开 
       }else if(x=='#'){
          while(!is_stack_op_empty(&st_op)){//符号栈非空 
             post_expression[j++]=pop_op(&st_op);
          }
       }else if(x==')'){
          while(get_op_top(&st_op)!='('){
             post_expression[j++]=pop_op(&st_op);
          }
          pop_op(&st_op);//将"("弹出 
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




//   计算后缀表达式的值 
//   算法思路：设操作数栈st_num,先将其置空,然后扫描后缀表达式中各分量送x；
// 若x=操作数，直接进栈；
// 若x=运算符：b=Pop(&st_num)，a=Pop(&st_num)，作a、b关于x的运算,结果再进栈；
// 若x=‘#’，算法结束，输出栈顶，即表达式结果。
float PostCount(const char * post_expression){
    int i=0,j=0;
    char x;
    char num_temp[MAX_SIZE_OF_EXPRESSION];//临时存放字符型的数字，用来转换成浮点数 
    float y,result,a,b; 
   stack_num st_num;//存放操作数 
   clear_stack_num(&st_num);
    
   while(post_expression[i]!='#'){
       x=post_expression[i];
//       cout<<x<<"\n";
   if(is_digit(x)){
   		  // 当 x 不是操作符（+-*/）的时候就依次向下找 
          do{
             num_temp[j++]=x;
              i++;
             x=post_expression[i];
//             cout<<x<<"\n"; 
          }while(x!=' ');
          num_temp[j]='\0';
          y=atof(&num_temp[0]);//转换成数值，进栈
          push_num(&st_num,y);
          j=0;
          i++;
       }else{
          b=pop_num(&st_num); a=pop_num(&st_num);//取两操作数
          result=Operate(a,b,x);
          push_num(&st_num,result);
          i++;
       }
    }
   if(!is_stack_num_empty(&st_num)){
      return get_num_top(&st_num);
   } 
    
}

// 电脑计算出算式表达式的值： 
double computd(string suanshi)
{
//定义两个数组用来存放中缀和后缀表达式
char mid_expression[MAX_SIZE_OF_EXPRESSION],post_expression[MAX_SIZE_OF_EXPRESSION]; 
//char if_continue='y';//用来判断是否继续 
char ch_in;//用来存储读入的字符 
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
        cout<<"输入的表达式超出范围,请输入长度小于"<<MAX_SIZE_OF_EXPRESSION<<"的表达式\n";
        system("pause");
        return -1; 
    }
    if(ch_in=='#'){
        // 以 # 结尾时，不再循环 
    	break;
    }
}

i=1;
   
Mid_Post(mid_expression,post_expression);
       
result=PostCount(post_expression);


return result;
}






// 主程序： 
void mainProgram() {
    // 启动随机数生成器！！！！ 
	srand((unsigned) time(NULL));
	int n;
	float num = 0;
	double youresult, score;
	int firstInput = 0; 
	string suanshi;
	cout<<"**********************************************************************************\n"; 
	cout<<"***********************************算数测试程序***********************************\n"; 
	cout<<"**********************************************************************************\n"; 

	int flag, input_flag, first_input = 0;
	do{
        if(first_input == 0) {
        	cout<<"请输入题目数量，最少 1 题，最多 100 题：";
        	first_input = 1;
        }
        if(!scanf("%d",&n))
        {
        	printf("\n您输入有误，请重新输入：");
        	// 清除输入缓存 
            fflush(stdin); 
			flag = 0;
        }
		else{
			if(n>=1 && n<=100)    /*判断输入数字的合法性*/
        	{
            	flag = 1;
				break;
        	}else {
        		cout<<"\n您输入有误，请重新输入：";
        	}
		} 
	}while(flag == 0);
	cout<<"\n";
	
	for (int i = 0; i < n; i++) {
		suanshi = randomExcs();
		cout<<"第"<<i+1<<"题："<<suanshi<<"\n";
		double result = computd(suanshi+'#');
		cout<<"电脑计算结果为:"<<result<<"\n";
		char p[100];
		memset(p, 0, 100);
		// 把 suanshi.c_str() 复制到 p 上面		
		strcpy(p, suanshi.c_str());
		cout<<suanshi<<"=？";
		do{
        	if(!scanf("%d",&youresult))
        	{
        		printf("\n您输入格式有误，请输入正确的格式：");
            	fflush(stdin);
				input_flag = 0;
        	}else {
        	    input_flag = 1;
				break;
        	}
		}while(input_flag == 0);
		
		if(youresult == result) {
			// 如果正确就输出正确，并且将对的题数加 1		
			cout<<"正确！\n"<<endl;
			num++;
		} else {
			cout<<"错误！正确答案是："<<result<<"\n\n";
		}
	}

	score = num / n * 100;
	cout<<"\n你的成绩为："<<score<<"\n"<<endl;
	cout<<"**********************************************************************************\n"; 
	cout<<"*********************************  结束  *****************************************\n"; 
	cout<<"**********************************************************************************\n"; 
}

int main(){
	mainProgram(); 
    return 0;
}






