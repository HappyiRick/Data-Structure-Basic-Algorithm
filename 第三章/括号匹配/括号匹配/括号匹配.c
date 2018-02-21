#include "predefine.h"
typedef char SElemType;
#define STACK_INIT_SIZE 10
#define STACKINCREMENT 2
typedef struct SqStack {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

/*˳��ջ��9����������*/
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
		printf("��������ʽ:\n");
		gets(ch);
		p = ch;
	
		while (*p)
		{
			switch (*p)
			{
				case '(':
				case '[':Push(&s,*p++);
					printf("push in stack\n");
					break;
				case ')':
				case ']':
					if (!StackEmpty(s))
					{
						Pop(&s,&e);
						if (*p==')'&&e!='('||*p==']'&&e!='[')
						{
							printf("�������Ų����\n");
							exit(ERROR);
						}
						else
						{
							p++;
							break;
						}
					}
					else {
						printf("ȱ��������\n");
						exit(ERROR);
					}
				default:p++;
			}	
		}
		if (StackEmpty(s)) 
			printf("����ƥ��\n");
		else
			printf("ȱ��������\n");
	}
}

void main(){
	check();
	system("pause");
}