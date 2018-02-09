/*ʵ�ֹ鲢���Ա��㷨*/
//���Ա�Ķ�̬����˳��洢�ṹ
#include "predefine.h"

typedef int ElemType;
#define LIST_INIT_SIZE 10  /* ���Ա�洢�ռ�ĳ�ʼ������ */
#define LISTINCREMENT 2 /* ���Ա�洢�ռ�ķ������� */
typedef struct
{
	ElemType *elem; /* �洢�ռ��ַ */
	int length; /* ��ǰ���� */
	int listsize; /* ��ǰ����Ĵ洢����(��sizeof(ElemType)Ϊ��λ) */
}SqList;


/*˳���ʾ�����Ա�Ļ�������(12��) */
//����һ���յ�˳���
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

//����˳���
Status DestroyList(SqList *L) {
	free((*L).elem);
	(*L).elem = NULL;
	(*L).length = 0;
	(*L).listsize = 0;
	return OK;
}

//����˳���
Status ClearList(SqList *L) {
	(*L).length = 0;
	return OK;
}

//�ж�˳����Ƿ�Ϊ��
Status listEmpty(SqList *L) {
	if (L->length == 0)
	{
		return TRUE;
	}
	return FALSE;
}

//˳�����
int ListLength(SqList L) {
	return L.length;
}

//��e����L�е�i������Ԫ�ص�ֵ
Status GetElem(SqList L, int i, ElemType *e) {
	if (i<1 || i>L.length)
	{
		exit(ERROR);
	}
	*e = *(L.elem + i - 1);
	return OK;
}

//����L�е�1����e�����ϵcompare()������Ԫ�ص�λ��
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

//����L������Ԫ�ص�ǰ��
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

//����L������Ԫ�صĺ��
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

//��L�е�i��λ��֮ǰ�����µ�����Ԫ��e����+1
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

//ɾ��L�еĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1
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

/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* ������������ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ�ܣ������ʧ�� */
/*           vi()���βμ�'&'��������ͨ������vi()�ı�Ԫ�ص�ֵ */
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

//�㷨2.1
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