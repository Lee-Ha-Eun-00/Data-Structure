/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h> //malloc함수를 사용하기 위한 헤더파일포함
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

int icp[] = { 20, 1, 0, 0, 4, 5, 6, 7, 0, 9 }; //stack 왜부에서의 우선순위를 나타낸 배열


char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x) //postfix변환에 필요한 스택에 문자를 넣을 함수
{
	postfixStack[++postfixStackTop] = x; //이전 스택의 그 다음 스택에 연산자 저장
}

char postfixPop() //postfix 스택에 있는 문자를 빼내는 함수
{
	char x;  //문자를 저장할 변수
	if (postfixStackTop == -1) //스택에 연산자가 하나도 없으면  널문자를 리턴
		return '\0';
	else {
		x = postfixStack[postfixStackTop--]; //x에 스택에 있는 문자저장한후 top의 값을 -1함
	}
	return x;  //문자리턴
}


void evalPush(int x) //계산에 필요한 스택에 문자를 넣을 함수
{
	evalStack[++evalStackTop] = x; //이전 스택의 그 다음 스택에 값 저장
}

int evalPop() //계산을 위해 만든 스택에 있는 값을 빼내는 함수
{
	if (evalStackTop == -1) //스택에 수가 없으면 -1반환
		return -1;
	else
		return evalStack[evalStackTop--]; //스택에 있는 값을 리턴한후 top의 값을 -1함

}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}


precedence getToken(char symbol) //전달받은 문자에 대응되는 반환값을 돌려주는 함수
{
	switch (symbol) {
	case '(': return lparen; //symbol이 (이면 lparen 반환
	case ')': return rparen; //symbol이 )이면 rparen 반환
	case '+': return plus; //symbol이  +이면 plus 반환
	case '-': return minus; //symbol이  -이면 minus 반환
	case '/': return divide; //symbol이  /이면 divide 반환
	case '*': return times; //symbol이  *이면 times 반환
	default: return operand; //그외의 값이면 operand반환
	}

}

precedence getPriority(char x) //getToken함수를 통해 얻은 값을 반환해 주는 함수
{
	return getToken(x);
}


/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp[0] == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix() //사용자가 입력한 함수를 후위표기 형식으로 변환해주는 함수
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char* exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	x = *(exp); //문자를 x에 저장
	char pop; //스택에서 pop한 원소를 저장하기 위한 변수

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */

	while (*exp != '\0')
	{

		if (x == '\0') //x에 저장된 값이 널문자이면 while문 탈출
		{
			break;
		}
		precedence token; //어떤 문자인지 확인한 값을 저장하기 위한 변수
		token = getToken(x);  //getToken함수를 통해 반환받은 값을 token에 저장

		if (token == operand) //x의 값이 피연산자이면 바로 postfixExp에 저장
		{
			charCat(exp);
		}
		else if (token == rparen) //x의 값이 오른쪽 괄호이면
		{
			while (getPriority(postfixStack[postfixStackTop]) != lparen) //왼쪽괄호가 나올때까지 postfixStack의 값을 빼서postfixExp에 저장
			{
				pop = postfixPop();
				charCat(&pop);
			}
			postfixPop(); //왼쪽괄호 제거
		}
		else
		{
			if (postfixStackTop == -1) //첫번째 값은 따로 push해줌(밑의 while문의 에러방지)
			{
				postfixPush(x);
				x = *(++exp); //exp의 값 증가
				continue; //처음으로 돌아감
			}
			while (getPriority(postfixStack[postfixStackTop]) >= icp[token])
				//스택안에 있는 값이 token의 우선순위보다 높을 때 반복
			{
				pop = postfixPop(); //스택에 있는 값을 pop해줌
				charCat(&pop); //pop해준 값을 postfixExp에 저장
			}
			postfixPush(x); //우선순위 높은 것을 다 pop해준뒤 push해줌
		}
		x = *(++exp); // exp의 값을 증가
	}
	while (postfixStackTop != -1) //스택에 남아 있는 연산자들을 모두pop 해줌
	{
		pop = postfixPop();
		charCat(&pop);
	}
}

void debug()
//입력된 값, 후기 표기 형태로 변환한값, 계산한값, postfix스택에 있는 값을 출력하는 함수
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset() //모든 값을 초기화 해주는 함수
{
	int i;
	for (i = 0; i < MAX_EXPRESSION_SIZE; i++)
		infixExp[i] = '\0';

	for (i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	for (i = 0; i < MAX_EXPRESSION_SIZE; i++)
	{
		postfixExp[i] = '\0';
	}
	for (i = 0; i < MAX_STACK_SIZE; i++)
	{
		evalStack[i] = '\0';
	}

	
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()//후위 표기식을 계산하는 함수
{
	precedence token; //getToken 함수를 통해 얻은 값을 저장할 변수
	char  symbol; //하나의 문자를 저장하기 위한 변수
	int op1, op2; //피연산자를 저장하기 위한 변수
	char* exp = postfixExp; //후위표기로 변경된 문자열의 주소를 저장할 변수
	symbol = *(exp); //문자열의 첫번째 값을 symbol에 저장
	token = getToken(symbol); //symbol을 인자로 받아 반환된 값을 token 에 저장

	while (*exp != '\0') //exp의 값이 널문자가 아닐때까지 반복
	{
		if (token == operand) //token이 피연산자이면 문자에서 숫자로 변환에 evalStack에 저장
		{
			evalPush(symbol - '0');
		}
		else  //연산자일때
		{
			//evalStack에서 두 피연산자를 빼옴
			op2 = evalPop();
			op1 = evalPop();
			switch (token)
			{
			case plus: //token이 plus일때 두 피연산자를 더해 eval Stack에 저장
				evalPush(op1 + op2);
				break;

			case minus: //token이 minus일때 두 피연산자의 차를 eval Stack에 저장
				evalPush(op1 - op2);
				break;

			case times: //token이 times일때 두 피연산자를 곱해 eval Stack에 저장
				evalPush(op1 * op2);
				break;

			case divide: // token이 divide일때 두 피연산자를 나눠서 eval Stack에 저장
				evalPush(op1 / op2);
				break;

			}
		}

		symbol = *(++exp); //symbol에 다음 문자를 저장
		token = getToken(symbol); //getToken의 값을 token에 저장

	}
	evalResult = evalStack[0]; //stack의 첫번째 원소에 있는 연산된 결과를 evalResult에 저장
}


int main()
{
	char command;//사용자가 입력한 메뉴 값을 저장하는 변수
    printf("----------[이하은]     [2019038037]----------\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자에게 메뉴 입력받음

		switch (command) { //사용자가 입력한 값에 따라 함수 실행
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q'); //q나 Q가 입력될때까지 반복

	return 0;


}