/* �Թ�����λ������ */
typedef struct {
	int x;
	int y;
}PosType;

#define MAXLENGTH 25
typedef int MazeType[MAXLENGTH][MAXLENGTH];

MazeType m;/* ���Թ����������Ϊ25 */
int curstep = 1;/* �Թ�����[��][��] */

/* ջ��Ԫ������ */
typedef struct {
	int ord;/* ͨ������·���ϵģ���ţ� */
	PosType seat;/* ͨ�������Թ��еģ�����λ�ã� */
	int di; /* �Ӵ�ͨ����������һͨ����ģ�����(0��3��ʾ������) */
}SElemType;

#include "predefine.h"
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

/*����ǽԪ��ֵΪ0����ͨ��·��Ϊ1������ͨ��·��-1��ͨ��·��Ϊ�㼣*/
Status Pass(PosType b) {
	if (m[b.x][b.y] == 1)
	{
		return OK;
	}
	return ERROR;
}

void FootPrint(PosType a) {
	m[a.x][a.y] = curstep;
}

PosType NextPos(PosType c,int di) {
	PosType direc[4] = { {0,1},{1,0},{0,-1},{-1,0} };
	c.x += direc[di].x;
	c.y += direc[di].y;
	return c;
}

void MarkPrint(PosType b) {
	m[b.x][b.y] = -1;
}

//algo3.3
Status MazePath(PosType start,PosType end) {
	/* ���Թ�maze�д��ڴ����start������end��ͨ���������һ�� */
	/* �����ջ��(��ջ�׵�ջ��)��������TRUE�����򷵻�FALSE */
	SqStack S;
	PosType curpos;
	SElemType e;
	InitStack(&S);
	curpos = start;
	do
	{
		if (Pass(curpos))
		{/* ��ǰλ�ÿ���ͨ��������δ���ߵ�����ͨ���� */
			FootPrint(curpos);/* �����㼣 */
			e.ord = curstep;
			e.seat.x = curpos.x;
			e.seat.y = curpos.y;
			e.di = 0;
			Push(&S,e);/* ��ջ��ǰλ�ü�״̬ */
			curstep++;/* �㼣��1 */
			if (curpos.x == end.x && curpos.y == end.y) /* �����յ�(����) */
			{
				return TRUE;
			}
			curpos = NextPos(curpos,e.di);
		}
		else {/* ��ǰλ�ò���ͨ�� */
			if (!StackEmpty(S))
			{
				Pop(&S,&e);/* ��ջ��ǰһλ�� */
				curstep--;
				while (e.di == 3&&!StackEmpty(S))/* ǰһλ�ô������һ������(��) */
				{
					MarkPrint(e.seat);/* ���²���ͨ���ı��(-1) */
					Pop(&S,&e);/* �˻�һ�� */
					curstep--;
				}
				if (e.di<3)/* û�����һ������(��) */
				{
					e.di++; /* ����һ������̽�� */
					Push(&S,e);
					curstep++;
					curpos = NextPos(e.seat,e.di); /* �趨��ǰλ���Ǹ��·����ϵ����ڿ� */
				}
			}
		}
	} while (!StackEmpty(S));
	return FALSE;
}

void Print(int x,int y) {
	int i, j;
	for ( i = 0; i < x; i++)
	{
		for ( j = 0; j < y; j++)
		{
			printf("%3d",m[i][j]);
		}
		printf("\n");
	}
}

void main() {
	PosType begin, end;
	int i, j, x, y, x1, y1;
	printf("�������Թ�������������(������ǽ):");
	scanf("%d,%d",&x,&y);/* �����ܱ�ֵΪ0(ͬǽ) */
	for ( i = 0; i < x; i++)
	{
		m[0][i] = 0;/* ���ܱ� */
		m[x - 1][i] = 0;
	}
	for ( j = 1; j < y-1; j++)
	{
		m[j][0] = 0;/* ���ܱ� */
		m[j][y - 1] = 0;
	}
	for ( i = 1; i < x-1; i++)
	{
		for ( j = 0; j < y-1; j++)
		{
			m[i][j] = 1;
		}
	}
	printf("�������Թ���ǽ��Ԫ��:");
	scanf("%d",&j);
	printf("�����������Թ���ǽÿ����Ԫ��������������\n");
	for ( i = 1; i <= j; i++)
	{
		scanf("%d,%d",&x1,&y1);
		m[x1][y1] = 0;
	}
	printf("�Թ��ṹ����");
	Print(x,y);
	printf("��������������������:");
	scanf("%d,%d",&begin.x,&begin.y);
	printf("�������յ������������:");
	scanf("%d,%d",&end.x,&end.y);
	if (MazePath(begin,end))/* ���һ��ͨ· */
	{
		printf("���Թ�����ڵ����ڵ�һ��·�����£�\n");
		Print(x,y);
	}
	else
	{
		printf("���Թ�û�д���ڵ����ڵ�·��");
	}
	system("pause");
}