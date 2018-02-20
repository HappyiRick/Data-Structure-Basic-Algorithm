#include "predefine.h"
typedef int SElemType;
#define STACK_INIT_SIZE 10
#define STACKINCREMENT 2
typedef struct SqStack {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

/*˳��ջ��9����������*/
Status InitStack(SqStack *S) {
	(*S).base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
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

Status GetTop(SqStack S,SElemType *e) {
	if (S.top > S.base)
	{
		*e = *(S.top - 1);
		return OK;
	}
	else {
		return ERROR;
	}
}

Status Push(SqStack *S,SElemType e) {
	if ((*S).top - (*S).base>=(*S).stacksize)
	{
		(*S).base = (SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
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

Status Pop(SqStack *S,SElemType *e) {
	if ((*S).top == (*S).base)
	{
		return ERROR;
	}
	*e = *--(*S).top;
	return OK;
}

Status StackTraverse(SqStack S,Status (*visit)(SElemType)){
	while (S.top>S.base)
	{
		visit(*S.base++);
	}
	printf("\n");
	return OK;
}

void conversion8(unsigned n) {
	SqStack s;
	SElemType e;
	InitStack(&s);
	while (n)
	{
		Push(&s,n%8);
		n = n / 8;
	}
	while (!StackEmpty(s))
	{
		Pop(&s,&e);
		printf("%d",e);
	}
	printf("\n");
}

void conversion16(unsigned n)
{ /* �������������һ���Ǹ�10������������ӡ��������ֵ��16������ */
	SqStack s;
	 /* �Ǹ����� */
	SElemType e;
	InitStack(&s); /* ��ʼ��ջ */
	/* ����Ǹ�ʮ��������n */
	while (n) /* ��n������0 */
	{
		Push(&s, n % 16); /* ��ջn����16������(16���Ƶĵ�λ) */
		n = n / 16;
	}
	while (!StackEmpty(s)) /* ��ջ���� */
	{
		Pop(&s, &e); /* ����ջ��Ԫ���Ҹ�ֵ��e */
		if (e <= 9)
			printf("%d", e);
		else
			printf("%c", e + 55);
	}
	printf("\n");
}


void main() {
	unsigned n;
	printf("n(>=0)=");
	scanf("%u", &n);
	printf("\n�˽��ƣ�");
	conversion8(n);
	printf("\nʮ�����ƣ�");
	conversion16(n);
	system("pause");
}