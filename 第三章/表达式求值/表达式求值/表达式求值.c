#include "predefine.h"
typedef int SElemType;
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
SElemType Precede(SElemType t1, SElemType t2) /* 同algo3-6.c */
{ /* 根据教科书表3.1，判断两符号的优先关系 */
	SElemType f;
	switch (t2)
	{
	case '+':
	case '-':if (t1 == '(' || t1 == '=')
		f = '<';
			 else
				 f = '>';
		break;
	case '*':
	case '/':if (t1 == '*' || t1 == '/' || t1 == ')')
		f = '>';
			 else
				 f = '<';
		break;
	case '(':if (t1 == ')')
	{
		printf("ERROR1\n");
		exit(ERROR);
	}
			 else
				 f = '<';
		break;
	case ')':switch (t1)
	{
	case '(':f = '=';
		break;
	case '=':printf("ERROR2\n");
		exit(ERROR);
	default: f = '>';
	}
			 break;
	case '=':switch (t1)
	{
	case '=':f = '=';
		break;
	case '(':printf("ERROR2\n");
		exit(ERROR);
	default: f = '>';
	}
	}
	return f;
}

Status In(SElemType c) /* 几乎与algo3-6.c相同 */
{ /* 判断c是否为运算符 */
	switch (c)
	{
	case'+':
	case'-':
	case'*':
	case'/':
	case'(':
	case')':
	case'=':return TRUE; /* 此句不同于algo3-6.c */
	default:return FALSE;
	}
}

SElemType Operate(SElemType a, SElemType theta, SElemType b) /* 有改动 */
{
	SElemType c;
	switch (theta)
	{
	case'+':c = a + b;
		break;
	case'-':c = a - b;
		break;
	case'*':c = a * b;
		break;
	case'/':c = a / b;
	}
	return c;
}

SElemType EvaluateExpression() /* 有改动 */
{ /* 算术表达式求值的算符优先算法。设OPTR和OPND分别为运算符栈和运算数栈 */
	SqStack OPTR, OPND;
	SElemType a, b, d, x, theta;
	char c; /* 存放由键盘接收的字符串 */
	char z[6]; /* 存放整数字符串 */
	int i;
	InitStack(&OPTR); /* 初始化运算符栈 */
	Push(&OPTR, '='); /* =是表达式结束标志 */
	InitStack(&OPND); /* 初始化运算数栈 */
	c = getchar();
	GetTop(OPTR, &x);
	while (c != '=' || x != '=')
	{
		if (In(c)) /* 是7种运算符之一 */
			switch (Precede(x, c))
			{
			case'<':Push(&OPTR, c); /* 栈顶元素优先权低 */
				c = getchar();
				break;
			case'=':Pop(&OPTR, &x); /* 脱括号并接收下一字符 */
				c = getchar();
				break;
			case'>':Pop(&OPTR, &theta); /* 退栈并将运算结果入栈 */
				Pop(&OPND, &b);
				Pop(&OPND, &a);
				Push(&OPND, Operate(a, theta, b));
			}
		else if (c >= '0'&&c <= '9') /* c是操作数 */
		{
			i = 0;
			do
			{
				z[i] = c;
				i++;
				c = getchar();
			} while (c >= '0'&&c <= '9');
			z[i] = 0;
			d = atoi(z); /* 将字符串数组转为整型存于d */
			Push(&OPND, d);
		}
		else /* c是非法字符 */
		{
			printf("ERROR3\n");
			exit(ERROR);
		}
		GetTop(OPTR, &x);
	}
	GetTop(OPND, &x);
	return x;
}

void main() /* 有改动 */
{
	printf("请输入算术表达式,负数要用(0-正数)表示,并以=结束\n");
	printf("%d\n", EvaluateExpression());
	system("pause");
}
