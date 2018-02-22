#include "predefine.h"

#define M 5 /* 迷宫行数(包括外墙) */
#define N 5 /* 迷宫列数(包括外墙) */
#define D 8 /* 移动方向数,只能取4和8。(8个,可斜行;4个,只可直走) */

typedef struct /* 定义队列元素和栈元素为同类型的结构体 */
{
	int x, y; /* 当前点的行值，列值 */
	int pre; /* 前一点在队列中的序号 */
}QElemType, SElemType; /* 定义栈元素和队列元素 */

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

//队列结构
/* 队列的顺序存储结构(可用于循环队列和非循环队列) */
#define MAXQSIZE 5
typedef struct {/* 最大队列长度(对于循环队列，最大队列长度要减1) */
	QElemType *base;/* 初始化的动态分配存储空间 */
	int front;/* 头指针,若队列不空,指向队列头元素 */
	int rear;/* 尾指针,若队列不空,指向队列尾元素的下一个位置 */
}SqQueue;

/*顺序队列的9个基本操作*/
Status InitQueue(SqQueue *Q) {
	(*Q).base = (QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
	if (!(*Q).base)
	{
		exit(OVERFLOW);
	}
	(*Q).front = (*Q).rear = 0;
	return OK;
}

Status DestroyQueue(SqQueue *Q) {
	if ((*Q).base)
	{
		free((*Q).base);
	}
	(*Q).base = NULL;
	(*Q).front = (*Q).rear = 0;
	return  OK;
}

Status QueueEmpty(SqQueue Q) {
	if (Q.front == Q.rear)
	{
		return TRUE;
	}
	return FALSE;
}

int QueueLength(SqQueue Q) {
	return (Q.rear - Q.front);
}

Status GetHead(SqQueue Q, QElemType *e)
{ /* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
	if (Q.front == Q.rear) /* 队列空 */
		return ERROR;
	*e = *(Q.base + Q.front);
	return OK;
}

Status EnQueue(SqQueue *Q,QElemType e) {
	if ((*Q).rear >= MAXQSIZE)
	{
		(*Q).base = (QElemType *)realloc((*Q).base,((*Q).rear+1)*sizeof(QElemType));
		if (!(*Q).base)
		{
			return ERROR;
		}
	}
	*((*Q).base + (*Q).rear) = e;
	(*Q).rear++;
	return OK;
}

Status DeQueue(SqQueue *Q,QElemType *e){
	if ((*Q).front == (*Q).rear)
	{
		return ERROR;
	}
	*e = (*Q).base[(*Q).front];
	(*Q).front = (*Q).front + 1;
	return OK;
}

Status QueueTraverse(SqQueue Q,void (*vi)(QElemType)) {
	int i;
	i = Q.front;
	while (i != Q.rear)
	{
		vi(*(Q.base + i));
		i++;
	}
	printf("\n");
	return OK;
}

struct /* 移动数组,移动方向由正东起顺时针转 */
{
	int x, y;
#if D==8
}move[D] = { { 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1,1 } };
#endif
#if D==4
 }move[D] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };
#endif

 Status Path(int maze[M][N]) {
	 SqQueue q;
	 QElemType qf, qt;
	 SqStack s;
	 int i, j, flag = 1;
	 int x1, y1;
	 printf("请输入入口的行，列（左上角为1，1）\n");
	 scanf("%d,%d",&qf.x,&qf.y);
	 printf("请输入出口的行，列（右下角为%d,%d）\n",M-2,N-2);
	 scanf("%d,%d",&x1,&y1);
	 qf.pre = -1;
	 maze[qf.x][qf.y] = -1;
	 InitQueue(&q);
	 EnQueue(&q,qf);
	 while (!QueueEmpty(q)&&flag)
	 {
		 DeQueue(&q,&qf);
		 for ( i = 0; i < D; i++)
		 {
			 qt.x = qf.x + move[i].x;
			 qt.y = qf.y + move[i].y;
			 if (maze[qt.x][qt.y]==1)
			 {
				 maze[qt.x][qt.y] = -1;
				 qt.pre = q.front - 1;
				 EnQueue(&q,qt);
				 if (qt.x == x1&&qt.y == y1)
				 {
					 flag = 0;
					 break;
				 }
			 }
		 }
	 }
	 if (flag)
	 {
		 printf("没有路径可到达终点!\n");
		 return ERROR;
	 }
	 else {
		 InitStack(&s);
		 i = q.rear - 1;
		 while (i>=0)
		 {
			 Push(&s,*(q.base+i));
			 i = (*(q.base + i)).pre;
		 }
		 i = 0;
		 while (!StackEmpty(s))
		 {
			 Pop(&s,&qf);
			 i++;
			 maze[qf.x][qf.y]=i;
		 }
		 printf("走出迷宫的一个方案:\n");
		 for ( i = 1; i < M-1; i++)
		 {
			 for ( j = 1; j < N-1; j++)
			 {
				 printf("%3d",maze[i][j]);
			 }
			 printf("\n");
		 }
		 return OK;
	 }
 }

 void main() {
	 int i, j;
	 int maze[M][N]; /* 迷宫数组 */
	 printf("%d行%d列迷宫(不包括外墙)\n", M - 2, N - 2);
	 for (i = 0; i<N; i++)
	 { /* 0为墙,1为通道 */
		 maze[0][i] = 0; /* 北墙 */
		 maze[M - 1][i] = 0; /* 南墙 */
	 }
	 for (i = 1; i<M - 1; i++)
	 {
		 maze[i][0] = 0; /* 西墙 */
		 maze[i][N - 1] = 0; /* 东墙 */
	 }
	 printf("请按行输入迷宫结构(不包括周边,0为墙,1为通道),如1 0 0 1\n");
	 for (i = 1; i<M - 1; i++)
		 for (j = 1; j<N - 1; j++)
			 scanf("%d", &maze[i][j]);
	 printf("迷宫结构(包括外墙):\n");
	 for (i = 0; i<M; i++)
	 {
		 for (j = 0; j<N; j++)
			 printf("%3d", maze[i][j]);
		 printf("\n");
	 }
	 Path(maze);
	 system("pause");
 }