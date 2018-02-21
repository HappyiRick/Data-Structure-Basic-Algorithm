#include "predefine.h"
typedef char SElemType;
#define STACK_INIT_SIZE 10
#define STACKINCREMENT 2
typedef struct SqStack {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

/*顺序栈的9个基本操作*/
Status InitStack(SqStack *S) {
	(*S).base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!(*S).base)
	{
		exit(OVERFLOW);
	}
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

Status DestroyStack(SqStack *S) {
	free((*S).base);
	(*S).base = NULL;
	(*S).top = NULL;
	(*S).stacksize = 0;
	return OK;
}

Status ClearStack(SqStack *S) {
	(*S).top = (*S).base;
	return OK;
}

Status StackEmpty(SqStack S) {
	if (S.top == S.base)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}

int StackLength(SqStack S) {
	return S.top - S.base;
}

Status GetTop(SqStack S, SElemType *e) {
	if (S.top > S.base)
	{
		*e = *(S.top - 1);
		return OK;
	}
	else {
		return ERROR;
	}
}

Status Push(SqStack *S, SElemType e) {
	if ((*S).top - (*S).base >= (*S).stacksize)
	{
		(*S).base = (SElemType *)realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!(*S).base)
		{
			exit(OVERFLOW);
		}
		(*S).top = (*S).base + (*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++ = e;
	return OK;
}

Status Pop(SqStack *S, SElemType *e) {
	if ((*S).top == (*S).base)
	{
		return ERROR;
	}
	*e = *--(*S).top;
	return OK;
}

Status StackTraverse(SqStack S, Status(*visit)(SElemType)) {
	while (S.top>S.base)
	{
		visit(*S.base++);
	}
	printf("\n");
	return OK;
}

SElemType Precede(SElemType t1,SElemType t2) {
	SElemType f;
	switch (t2)
	{
	case '+':
	case '-':if (t1 == '('||t1=='#')
		{
		f = '<';
		}
			 else {
				 f = '>';
		}
			 break;
	case '*':
	case '/':if (t1=='*'||t1=='/'||t1==')')
		{
		f = '>';
		}
			 else {
				 f = '<';
		}
			 break;
	case '(':if (t1==')')
		{
		printf("ERROR1\n");
		exit(ERROR);
		}
			 else {
				 f = '<';
		}
			 break;
	case ')':switch (t1)
		{
			case '(':f = '=';
				break;
			case '#':printf("ERROR2\n");
				exit(ERROR);
			default:
			f='>';
		}
			 break;
	case '#':switch (t1)
		{
			case '#':f = '=';
				break;
			case '(':printf("ERROR3\n");
				exit(ERROR);
			default:f = '>';
		}
	}
	return f;
}

/* 判断c是否为运算符 */
Status In(SElemType c) {
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	case '#':
		return TRUE;
	default:
		return FALSE;
	}
}

SElemType Operate(SElemType a,SElemType theta,SElemType b) {
	SElemType c;
	a = a - 48;
	b = b - 48;
	switch (theta)
	{
	case '+':c = a + b + 48;
		break;
	case '-':c = a - b + 48;
		break;
	case '*':c = a * b + 48;
		break;
	case '/':c = a / b + 48;
	}
	return c;
}

//Algo 3.4
SElemType EvaluateExpression() {
	SqStack OPTR, OPND;
	SElemType a, b, c, x, theta;
	InitStack(&OPTR);
	Push(&OPTR,'#');
	InitStack(&OPND);
	c = getchar();
	GetTop(OPTR,&x);
	while (c!='#'||x!='#')
	{
		if (In(c))
		{
			switch (Precede(x,c))
			{
			case '<':Push(&OPTR, c);
				c = getchar();
				break;
			case '=':Pop(&OPTR,&x);
				c = getchar();
				break;
			case '>':Pop(&OPTR,&theta);
				Pop(&OPND,&b);
				Pop(&OPND,&a);
				Push(&OPND,Operate(a,theta,b));
				break;
			}
		}
		else if (c>='0'&&c<='9')
		{
			Push(&OPND,c);
			c = getchar();
		}else{
			printf("ERROR4\n");
			exit(ERROR);
		}
		GetTop(OPND,&x);
	}
	GetTop(OPND,&x);
	return x;
}

void main() {
	printf("请输入算术表达式：（中间值及最终结果要在0-9之间），并以#结束\n");
	printf("%c\n",EvaluateExpression());
	system("pause");
}