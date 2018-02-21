/* 迷宫坐标位置类型 */
typedef struct {
	int x;
	int y;
}PosType;

#define MAXLENGTH 25
typedef int MazeType[MAXLENGTH][MAXLENGTH];

MazeType m;/* 设迷宫的最大行列为25 */
int curstep = 1;/* 迷宫数组[行][列] */

/* 栈的元素类型 */
typedef struct {
	int ord;/* 通道块在路径上的＂序号＂ */
	PosType seat;/* 通道块在迷宫中的＂坐标位置＂ */
	int di; /* 从此通道块走向下一通道块的＂方向＂(0～3表示东～北) */
}SElemType;

#include "predefine.h"
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

/*定义墙元素值为0，可通过路径为1，不能通过路径-1，通过路径为足迹*/
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
	/* 若迷宫maze中存在从入口start到出口end的通道，则求得一条 */
	/* 存放在栈中(从栈底到栈顶)，并返回TRUE；否则返回FALSE */
	SqStack S;
	PosType curpos;
	SElemType e;
	InitStack(&S);
	curpos = start;
	do
	{
		if (Pass(curpos))
		{/* 当前位置可以通过，即是未曾走到过的通道块 */
			FootPrint(curpos);/* 留下足迹 */
			e.ord = curstep;
			e.seat.x = curpos.x;
			e.seat.y = curpos.y;
			e.di = 0;
			Push(&S,e);/* 入栈当前位置及状态 */
			curstep++;/* 足迹加1 */
			if (curpos.x == end.x && curpos.y == end.y) /* 到达终点(出口) */
			{
				return TRUE;
			}
			curpos = NextPos(curpos,e.di);
		}
		else {/* 当前位置不能通过 */
			if (!StackEmpty(S))
			{
				Pop(&S,&e);/* 退栈到前一位置 */
				curstep--;
				while (e.di == 3&&!StackEmpty(S))/* 前一位置处于最后一个方向(北) */
				{
					MarkPrint(e.seat);/* 留下不能通过的标记(-1) */
					Pop(&S,&e);/* 退回一步 */
					curstep--;
				}
				if (e.di<3)/* 没到最后一个方向(北) */
				{
					e.di++; /* 换下一个方向探索 */
					Push(&S,e);
					curstep++;
					curpos = NextPos(e.seat,e.di); /* 设定当前位置是该新方向上的相邻块 */
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
	printf("请输入迷宫的行数，列数(包括外墙):");
	scanf("%d,%d",&x,&y);/* 定义周边值为0(同墙) */
	for ( i = 0; i < x; i++)
	{
		m[0][i] = 0;/* 行周边 */
		m[x - 1][i] = 0;
	}
	for ( j = 1; j < y-1; j++)
	{
		m[j][0] = 0;/* 列周边 */
		m[j][y - 1] = 0;
	}
	for ( i = 1; i < x-1; i++)
	{
		for ( j = 0; j < y-1; j++)
		{
			m[i][j] = 1;
		}
	}
	printf("请输入迷宫内墙单元数:");
	scanf("%d",&j);
	printf("请依次输入迷宫内墙每个单元的行数，列数：\n");
	for ( i = 1; i <= j; i++)
	{
		scanf("%d,%d",&x1,&y1);
		m[x1][y1] = 0;
	}
	printf("迷宫结构如下");
	Print(x,y);
	printf("请输入起点的行数，列数:");
	scanf("%d,%d",&begin.x,&begin.y);
	printf("请输入终点的行数，列数:");
	scanf("%d,%d",&end.x,&end.y);
	if (MazePath(begin,end))/* 求得一条通路 */
	{
		printf("此迷宫从入口到出口的一条路径如下：\n");
		Print(x,y);
	}
	else
	{
		printf("此迷宫没有从入口到出口的路径");
	}
	system("pause");
}