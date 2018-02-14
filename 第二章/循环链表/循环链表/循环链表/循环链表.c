#include "predefine.h"
typedef int ElemType;
struct LNode
{
	ElemType data;
	struct LNode *next;
};
typedef struct LNode *LinkList;

/*设立尾指针的单循环链表的12个基本操作 */
Status InitList_CL(LinkList *L) {
	*L = (LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
	if (!*L)
	{
		exit(OVERFLOW);
	}
	(*L)->next = *L; /* 指针域指向头结点 */
	return OK;
}

Status DestroyList_CL(LinkList *L) {
	LinkList q, p = (*L)->next;/* p指向头结点 */
	while (p!=*L)
	{
		q = p->next;
		free(p);
		p = q;
	}
	free(*L);
	*L = NULL;
	return OK;
}

Status ClearList_CL(LinkList *L) {
	LinkList p, q;
	*L = (*L)->next;/* L指向头结点 */
	p = (*L)->next;/* p指向第一个结点 */
	while (p!=*L)
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = *L; /* 头结点指针域指向自身 */
	return OK;
}

Status ListEmpty_CL(LinkList L) {
	if (L->next == L)/* 空 */
	{
		return TRUE;
	}
	return FALSE;
}

int ListLength_CL(LinkList L) {
	int i = 0;
	LinkList p = L->next; /* p指向头结点 */
	while (p!=L)
	{
		i++;
		p = p->next;
	}
	return i;
}

Status GetElem_CL(LinkList L,int i,ElemType *e) {
	int j = 1;/* 初始化,j为计数器 */
	LinkList p = L->next->next; /* p指向第一个结点 */
	if (i<=0||i>ListLength_CL(L))/* 第i个元素不存在 */
	{
		return ERROR;
	}
	while (j<i)
	{ /* 顺指针向后查找,直到p指向第i个元素 */
		p = p->next;
		j++;
	}
	*e = p->data;/* 取第i个元素 */
	return OK;
}

int LocateELem_CL(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType)) {
	/* 初始条件：线性表L已存在，compare()是数据元素判定函数 */
	/* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
	/*           若这样的数据元素不存在，则返回值为0 */
	int i = 0;
	LinkList p = L->next->next;/* p指向第一个结点 */
	while (p!=L->next)
	{
		i++;
		if (compare(p->data,e))/* 满足关系 */
		{
			return i;
		}
		p = p->next;
	}
	return 0;
}

Status PriorELem_CL(LinkList L,ElemType cur_e,ElemType *pre_e) {
	LinkList q, p = L->next->next;/* p指向第一个结点 */
	q = p->next;
	while (q!=L->next)
	{
		if (q->data == cur_e)
		{
			*pre_e = p->data;
			return TRUE;
		}
		p = q;
		q = q->next;
	}
	return FALSE;
}

Status NextElem_CL(LinkList L,ElemType cur_e,ElemType *next_e) {
	/* 初始条件：线性表L已存在 */
	/* 操作结果：若cur_e是L的数据元素,且不是最后一个,则用next_e返回它的后继， */
	/*           否则操作失败，next_e无定义 */
	LinkList p = L->next->next;/* p指向第一个结点 */
	while (p!=L)
	{
		if (p->data == cur_e)
		{
			*next_e = p->next->data;
			return TRUE;
		}
		p = p->next;
	}
	return FALSE;
}

Status ListInsert_CL(LinkList *L,int i,ElemType e) {
	LinkList p = (*L)->next, s;/* p指向头结点 */
	int j = 0;
	if (i<=0||i>ListLength_CL(*L)+1) /* 无法在第i个元素之前插入 */
	{
		return ERROR;
	}
	while (j<i-1)/* 寻找第i-1个结点 */
	{
		p = p->next;
		j++;
	}
	s = (LinkList)malloc(sizeof(struct LNode));/* 生成新结点 */
	s->data = e;/* 插入L中 */
	s->next = p->next;
	p->next = s;
	if (p == *L)/* 改变尾结点 */
	{
		*L = s;
	}
	return OK;
}

Status ListDelete_CL(LinkList *L, int i, ElemType *e) {/* 改变L */
	LinkList p = (*L)->next, q;/* p指向头结点 */
	int j = 0;
	if (i <= 0||i>ListLength_CL(*L))/* 第i个元素不存在 */
	{
		return ERROR;
	}
	while (j<i-1) /* 寻找第i-1个结点 */
	{
		p = p->next;
		j++;
	}
	q = p->next;/* q指向待删除结点 */
	p->next = q->next;
	*e = q->data;
	if (*L == q)/* 删除的是表尾元素 */
	{
		*L = p;
	}
	free(q); /* 释放待删除结点 */
	return OK;
}

Status ListTraverse_CL(LinkList L, void(*vi)(ElemType)) {
	LinkList p = L->next->next;
	while (p!=L->next)
	{
		vi(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

void MergeList_CL(LinkList *La,LinkList Lb) {
	LinkList p = Lb->next;
	Lb->next = (*La)->next;
	(*La)->next = p->next;
	free(p);
	*La = Lb;
}

void visit(ElemType c) {
	printf("%d",c);
}

void main() {
	int n = 5, i;
	LinkList La, Lb;
	InitList_CL(&La);
	for (i = 1; i <= n; i++)
	{
		ListInsert_CL(&La,i,i);
	}
	printf("La = ");
	ListTraverse_CL(La,visit);
	InitList_CL(&Lb);
	for (i = 1; i <= n; i++)
	{
		ListInsert_CL(&Lb,1,i*2);
	}
	printf("Lb = ");
	ListTraverse_CL(Lb, visit);
	MergeList_CL(&La,Lb);
	printf("La+Lb=");
	ListTraverse_CL(La,visit);
	system("pause");
}