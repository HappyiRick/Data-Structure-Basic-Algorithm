/*实现归并线性表算法*/
//线性表的动态分配顺序存储结构
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

//算法2.1
Status equal(ElemType elem1, ElemType elem2) {
	if (elem1 == elem2)
	{
		return TRUE;
	}
	return FALSE;
}

void Union(SqList *La, SqList Lb) {
	ElemType e;
	int La_len, Lb_len;
	int i;
	La_len = ListLength(*La);
	Lb_len = ListLength(Lb);
	for (i = 1; i <= Lb_len; i++)
	{
		GetElem(Lb, i, &e);
		if (!LocateElem(*La, e, equal))
		{
			ListInsert(La, ++La_len, e);
		}
	}
}

void print(ElemType *e) {
	printf("%d", *e);
}

int main(void) {
	SqList La, Lb;
	Status i;
	int j;
	i = InitList(&La);
	if (i == 1) {
		for (j = 1; j <= 5; j++)
		{
			i = ListInsert(&La, j, j);
		}
	}
	printf("La = ");
	ListTraverse(La, print);
	InitList(&Lb);
	for (j = 1; j <= 5; j++)
	{
		i = ListInsert(&Lb, j, 2 * j);
	}
	printf("Lb =");
	ListTraverse(Lb, print);
	Union(&La, Lb);
	printf("new La = ");
	ListTraverse(La, print);
	return 0;
}