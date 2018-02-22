#include "predefine.h"

#define M 5 /* �Թ�����(������ǽ) */
#define N 5 /* �Թ�����(������ǽ) */
#define D 8 /* �ƶ�������,ֻ��ȡ4��8��(8��,��б��;4��,ֻ��ֱ��) */

typedef struct /* �������Ԫ�غ�ջԪ��Ϊͬ���͵Ľṹ�� */
{
	int x, y; /* ��ǰ�����ֵ����ֵ */
	int pre; /* ǰһ���ڶ����е���� */
}QElemType, SElemType; /* ����ջԪ�غͶ���Ԫ�� */

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

//���нṹ
/* ���е�˳��洢�ṹ(������ѭ�����кͷ�ѭ������) */
#define MAXQSIZE 5
typedef struct {/* �����г���(����ѭ�����У������г���Ҫ��1) */
	QElemType *base;/* ��ʼ���Ķ�̬����洢�ռ� */
	int front;/* ͷָ��,�����в���,ָ�����ͷԪ�� */
	int rear;/* βָ��,�����в���,ָ�����βԪ�ص���һ��λ�� */
}SqQueue;

/*˳����е�9����������*/
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
{ /* �����в���,����e����Q�Ķ�ͷԪ��,������OK,���򷵻�ERROR */
	if (Q.front == Q.rear) /* ���п� */
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

struct /* �ƶ�����,�ƶ�������������˳ʱ��ת */
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
	 printf("��������ڵ��У��У����Ͻ�Ϊ1��1��\n");
	 scanf("%d,%d",&qf.x,&qf.y);
	 printf("��������ڵ��У��У����½�Ϊ%d,%d��\n",M-2,N-2);
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
		 printf("û��·���ɵ����յ�!\n");
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
		 printf("�߳��Թ���һ������:\n");
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
	 int maze[M][N]; /* �Թ����� */
	 printf("%d��%d���Թ�(��������ǽ)\n", M - 2, N - 2);
	 for (i = 0; i<N; i++)
	 { /* 0Ϊǽ,1Ϊͨ�� */
		 maze[0][i] = 0; /* ��ǽ */
		 maze[M - 1][i] = 0; /* ��ǽ */
	 }
	 for (i = 1; i<M - 1; i++)
	 {
		 maze[i][0] = 0; /* ��ǽ */
		 maze[i][N - 1] = 0; /* ��ǽ */
	 }
	 printf("�밴�������Թ��ṹ(�������ܱ�,0Ϊǽ,1Ϊͨ��),��1 0 0 1\n");
	 for (i = 1; i<M - 1; i++)
		 for (j = 1; j<N - 1; j++)
			 scanf("%d", &maze[i][j]);
	 printf("�Թ��ṹ(������ǽ):\n");
	 for (i = 0; i<M; i++)
	 {
		 for (j = 0; j<N; j++)
			 printf("%3d", maze[i][j]);
		 printf("\n");
	 }
	 Path(maze);
	 system("pause");
 }