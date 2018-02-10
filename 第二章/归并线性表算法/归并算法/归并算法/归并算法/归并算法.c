#include "predefine.h"

typedef int ElemType;
#define LIST_INIT_SIZE 10  /* 线性表存储空间的初始分配量 */
#define LISTINCREMENT 2 /* 线性表存储空间的分配增量 */
typedef struct
{
	ElemType *elem; /* 存储空间基址 */
	int length; /* 当前长度 */
	int listsize; /* 当前分配的存储容量(以sizeof(ElemType)为单位) */
}SqList;


/*顺序表示的线性表的基本操作(12个) */
//构建一个空的顺序表
Status InitList(SqList *L) {
	(*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!(*L).elem)
	{
		exit(OVERFLOW);
	}
	(*L).length = 0;
	(*L).listsize = LIST_INIT_SIZE;

	return OK;
}

//销毁顺序表
Status DestroyList(SqList *L) {
	free((*L).elem);
	(*L).elem = NULL;
	(*L).length = 0;
	(*L).listsize = 0;
	return OK;
}

//重置顺序表
Status ClearList(SqList *L) {
	(*L).length = 0;
	return OK;
}

//判断顺序表是否为空
Status listEmpty(SqList *L) {
	if (L->length == 0)
	{
		return TRUE;
	}
	return FALSE;
}

//顺序表长度
int ListLength(SqList L) {
	return L.length;
}

//用e返回L中第i个数据元素的值
Status GetElem(SqList L, int i, ElemType *e) {
	if (i<1 || i>L.length)
	{
		exit(ERROR);
	}
	*e = *(L.elem + i - 1);
	return OK;
}

//返回L中第1个与e满足关系compare()的数据元素的位序
int LocateElem(SqList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
	ElemType *p;
	int i = 1;
	p = L.elem;
	while (i <= L.length && !compare(*p++, e)) {
		++i;
	}
	if (i <= L.length) {
		return i;
	}
	return 0;
}

//返回L的数据元素的前驱
Status PriorElem(SqList L, ElemType cur_e, ElemType *pre_e) {
	int i = 2;
	ElemType *p = L.elem + 1;
	while (i <= L.length && *p != cur_e) {
		p++;
		i++;
	}
	if (i>L.length)
	{
		return INFEASIBLE;
	}
	else {
		*pre_e = *--p;
		return OK;
	}
}

//返回L的数据元素的后继
Status NextElem(SqList L, ElemType cur_e, ElemType *next_e) {
	int i = 1;
	ElemType *p = L.elem;
	while (i<L.length && *p != cur_e) {
		i++;
		p++;
	}
	if (i == L.length)
	{
		return INFEASIBLE;
	}
	else {
		*next_e = *++p;
		return OK;
	}
}

//在L中第i个位置之前插入新的数据元素e，表长+1
Status ListInsert(SqList *L, int i, ElemType e) {
	ElemType *newbase, *p, *q;
	if (i<1 || i>(*L).length + 1)
	{
		return ERROR;
	}
	if ((*L).length >= (*L).listsize)
	{
		newbase = (ElemType *)realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)
		{
			exit(OVERFLOW);
		}
		(*L).elem = newbase;
		(*L).listsize += LISTINCREMENT;
	}
	q = (*L).elem + i - 1;
	for (p = (*L).elem + (*L).length - 1; p >= q; --p)
	{
		*(p + 1) = *p;
	}
	*q = e;
	++(*L).length;
	return OK;
}

//删除L中的第i个数据元素，并用e返回其值，L的长度减1
Status ListDelete(SqList *L, int i, ElemType *e) {
	ElemType *p, *q;
	if (i<1 || i>(*L).length)
	{
		return ERROR;
	}
	p = (*L).elem + i - 1;
	*e = *p;
	q = (*L).elem + (*L).length - 1;
	for (++p; p <= q; ++p)
	{
		*(p - 1) = *p;
	}
	(*L).length--;
	return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
/*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
Status ListTraverse(SqList L, void(*vi)(ElemType*))
{
	ElemType *p;
	int i;
	p = L.elem;
	for (i = 1; i <= L.length; i++)
		vi(p++);
	printf("\n");
	return OK;
}

//算法2.2 归并算法
void MergeList(SqList La,SqList Lb,SqList *Lc) {
	int i = 1, j = 1, k = 0;
	int La_len, Lb_len;
	ElemType ai, bj;
	InitList(Lc);
	La_len = ListLength(La);
	Lb_len = ListLength(Lb);
	while (i<=La_len&&j<=Lb_len)
	{
		GetElem(La,i,&ai);
		GetElem(Lb,j,&bj);
		if (ai<=bj)
		{
			ListInsert(Lc,++k,ai);
			++i;
		}
		else {
			ListInsert(Lc,++k,bj);
			++j;
		}
	}
	while (i<=La_len)/* 表La非空且表Lb空 */
	{
		GetElem(La,i++,&ai);
		ListInsert(Lc,++k,ai);
	}
	while (j<=Lb_len)/* 表Lb非空且表La空 */
	{
		GetElem(Lb,j++,&bj);
		ListInsert(Lc,++k,bj);
	}
}

void print(ElemType *c) {
	printf("%d",*c);
}

/*
	预期输入：La = ｛3，5，8，11｝
			  Lb = ｛2，6，8，9，11，15，20｝
	预期输出：La = 35811
			  Lb = 2689111520
			  Lc = 235688911111520
*/

int main(void) {
	SqList La, Lb, Lc;
	int j, a[4] = { 3,5,8,11 }, b[7] = {2,6,8,9,11,15,20};
	InitList(&La);//创建空表
	for (j = 1; j <=4; j++)//La插入元素
	{
		ListInsert(&La,j,a[j-1]);
	}
	printf("La = ");
	ListTraverse(La,print);
	InitList(&Lb);//空表Lb
	for (j = 1; j <= 7; j++)//Lb插入元素
	{
		ListInsert(&Lb,j,b[j-1]);
	}
	printf("Lb = ");
	ListTraverse(Lb,print);
	MergeList(La,Lb,&Lc);
	printf("Lc = ");
	ListTraverse(Lc,print);
	return 0;
}