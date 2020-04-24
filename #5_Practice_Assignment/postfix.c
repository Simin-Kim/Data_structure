/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen =0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호 */
	times = 6,   /* * 곱셈 */
	divide = 5,  /* / 나눗셈 */
	plus = 4,    /* + 덧셈 */
	minus = 3,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x)
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];
	}
		return x;
	
}

void evalPush(int x)
{
	evalStack[++evalStackTop] = x;
}

int evalPop()
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
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

precedence getToken(char symbol)
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}

}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixEx의 문자 하나씩을 읽기위한 포인터 */
	char* exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	int input_prior;	/* 입력되는 연산자의 우선순위 */
	int Stack_prior;	/* postfixStack의 postfixStackTop에 있는 연산자의 우선순위 */
	int cnt = 0;

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')							 /* exp에 널문자가 나올때까지 반복 */
	{
		x = *exp;									 /* x에 exp포인터의 문자 하나 저장 */
		input_prior = getPriority(x);		         /* 입력값의 우선순위를 저장하는 변수(왼쪽괄호 연산자가 스택의 연산자 우선순위와 달라진다 할지라도 아래 조건문에서 커버해줌) */

		if (input_prior == 1)						 /* 입력값이 피연산자이면 postfixExp에 바로 저장 */
			charCat(exp);
		else
		{
			if (postfixStackTop == -1)				 /* postfixStackTop이 1일때, 즉 스택에 저장된 값이 없을때 postfixStack으로 push */
			{
				postfixPush(*exp);					 
			}
			else
			{

				Stack_prior = getPriority(postfixStack[postfixStackTop]);		  /* Stack_prior변수에 postfixStackTop에 있는 값의 우선순위를 대입 */

				if (input_prior > Stack_prior)		     /* 입력값의 우선순위가 postfixStackTop에 있는 값의 우선순위보다 높으면 postfixStack으로 push */
				{
					if (input_prior == 9)				 /* 입력값이 왼쪽 괄호이면 */
					{
						while (getPriority(postfixStack[postfixStackTop]) != 0)		  /* 오른쪽 괄호가 나올때까지 postfixStackTop에 있는 연산자 pop하여 postfixExp로 보냄 */
						{
							x = postfixPop();
							charCat(&x);
						}
						postfixPop();												  /* 오른쪽 괄호 나오면 오른쪽 괄호 pop해줌 */
					}
					else								/* 왼쪽 괄호 아니면 postfixStack으로 push */
						postfixPush(*exp);
				}
				else if (input_prior < Stack_prior)			 /* 입력값의 우선순위가 postfixStackTop에 있는 값의 우선순위보다 낮으면 postfixStackTop에 있는 값을 pop하고 스택에 저장 */
				{
					if (input_prior == 0)			         /* 왼쪽 괄호일경우 스택들어가기 전 고유의 우선순위가 가장 높기때문에 바로 postfixStack에 Push */
						postfixPush(*exp);
					else									 
					{
						x = postfixPop();
						charCat(&x);
						postfixPush(*exp);
					}
				}
				else									 /* 입력값의 우선순위가 postfixStackTop에 있는 값의 우선순위와 같으면 pop&push */
				{
					x = postfixPop();
					charCat(&x);
					postfixPush(*exp);
				}

			}
		}
		exp += 1;									/* 반복문이 끝날때마다 exp값 증가 */
	}
	
	while (postfixStackTop != -1) 					/* 공백스택이 될때까지 pop하여 postfixExp로 보내줌 */
	{
		x=postfixPop();
		charCat(&x);
	}
	
}

void debug()
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

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	char *eval=postfixExp;
	int op1, op2;										  /* 계산에 이용할 피연산자값 변수 선언 */
	precedence token;									  /* getToken으로 연산자 문자 받을 token 선언 */

	while (*eval != '\0')								  /* eval에 널문자가 나올때까지 반복 */
	{
		token = getToken(*eval);						  /* getToken으로 token에 연산자 문자 저장 */
		if (token==operand)								  /* token값이 피연산자일때 evalStack에 push */
		{
			evalPush((*eval)-'0');						  

		}
		else											  /* token값이 연산자일때 */
		{
			op2 = evalPop();							  /* evalStackTop에 있는 값 pop하여 op2에 저장*/
			op1 = evalPop();							  /* evalStackTop에 있는 값 pop하여 op1에 저장*/

			switch (token) {							  /* token값을 switch문으로 해당 연산자 찾아 연산수행하여 evalStack에 push */
			case plus: evalPush(op1 + op2); break;
			case minus: evalPush(op1 - op2); break;
			case times: evalPush(op1 * op2); break;
			case divide: evalPush(op1 / op2); 
			}
		}
		eval++;											  /* 반복문 끝날때마다 eval값 증가 */
	}
	evalResult=evalPop();								  /* evalStack의 가장 아래에 저장된 최종결과값 evalResult에 저장 */
}


int main()
{
	printf("[이름] : 김시민\t[학번] : 2016039081\n");

	char command;

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
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

	} while (command != 'q' && command != 'Q');

	return 0;


}