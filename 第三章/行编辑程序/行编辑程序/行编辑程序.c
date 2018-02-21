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

FILE *fp;

Status copy(SElemType c) {
	fputc(c,fp);
	return OK;
}

void LineEdit() {
	SqStack s;
	char ch, c;
	InitStack(&s);
	printf("请输入一个文本文件，^Z结束输入:\n");
	ch = getchar();
	while (ch!=EOF)
	{
		while (ch!=EOF&&ch!='\n')
		{
			switch (ch)
			{
			case '#':Pop(&s,&c);
				break;
			case '@':ClearStack(&s);
				break;
			default:
				Push(&s,ch);
			}
			ch = getchar();
		}
		StackTraverse(s,copy);
		ClearStack(&s);
		fputc('\n',fp);
		if (ch!=EOF)
		{
			ch = getchar();
		}
	}
	DestroyStack(&s);
}

void main() {
	fp = fopen("ED.txt","w");
	if (fp)
	{
		LineEdit();
		fclose(fp);
	}
	else {
		printf("建立文件失败");
	}
	system("pause");
}