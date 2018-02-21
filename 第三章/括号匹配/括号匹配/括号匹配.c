//本段代码逻辑上没有问题 然而在实际运行中出现了无法识别左括号进行压栈的情况 尚未解决
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


void check() {
	SqStack s;
	SElemType ch[80], *p, e;
	if (InitStack(&s))
	{
		printf("请输入表达式:\n");
		gets(ch);
		p = ch;
	
		while (*p)
		{
			switch (*p)
			{
				case '(':
				case '[':Push(&s,*p++);
					printf("yazhan");
					break;
				case ')':
				case ']':
					if (!StackEmpty(s))
					{
						Pop(&s,&e);
						if (*p==')'&&e!='('||*p==']'&&e!='[')
						{
							printf("左右括号不配对\n");
							exit(ERROR);
						}
						else
						{
							p++;
							break;
						}
					}
					else {
						printf("缺乏左括号\n");
						exit(ERROR);
					}
				default:p++;
			}	
		}
		if (StackEmpty(s)) 
			printf("括号匹配\n");
		else
			printf("缺乏右括号\n");
	}
}

void main(){
	check();
	system("pause");
}