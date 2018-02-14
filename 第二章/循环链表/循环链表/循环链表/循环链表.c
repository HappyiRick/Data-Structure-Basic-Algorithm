#include "predefine.h"
typedef int ElemType;
struct LNode
{
	ElemType data;
	struct LNode *next;
};
typedef struct LNode *LinkList;

/*����βָ��ĵ�ѭ�������12���������� */
Status InitList_CL(LinkList *L) {
	*L = (LinkList)malloc(sizeof(struct LNode)); /* ����ͷ���,��ʹLָ���ͷ��� */
	if (!*L)
	{
		exit(OVERFLOW);
	}
	(*L)->next = *L; /* ָ����ָ��ͷ��� */
	return OK;
}

Status DestroyList_CL(LinkList *L) {
	LinkList q, p = (*L)->next;/* pָ��ͷ��� */
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
	*L = (*L)->next;/* Lָ��ͷ��� */
	p = (*L)->next;/* pָ���һ����� */
	while (p!=*L)
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = *L; /* ͷ���ָ����ָ������ */
	return OK;
}

Status ListEmpty_CL(LinkList L) {
	if (L->next == L)/* �� */
	{
		return TRUE;
	}
	return FALSE;
}

int ListLength_CL(LinkList L) {
	int i = 0;
	LinkList p = L->next; /* pָ��ͷ��� */
	while (p!=L)
	{
		i++;
		p = p->next;
	}
	return i;
}

Status GetElem_CL(LinkList L,int i,ElemType *e) {
	int j = 1;/* ��ʼ��,jΪ������ */
	LinkList p = L->next->next; /* pָ���һ����� */
	if (i<=0||i>ListLength_CL(L))/* ��i��Ԫ�ز����� */
	{
		return ERROR;
	}
	while (j<i)
	{ /* ˳ָ��������,ֱ��pָ���i��Ԫ�� */
		p = p->next;
		j++;
	}
	*e = p->data;/* ȡ��i��Ԫ�� */
	return OK;
}

int LocateELem_CL(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType)) {
	/* ��ʼ���������Ա�L�Ѵ��ڣ�compare()������Ԫ���ж����� */
	/* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
	/*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
	int i = 0;
	LinkList p = L->next->next;/* pָ���һ����� */
	while (p!=L->next)
	{
		i++;
		if (compare(p->data,e))/* �����ϵ */
		{
			return i;
		}
		p = p->next;
	}
	return 0;
}

Status PriorELem_CL(LinkList L,ElemType cur_e,ElemType *pre_e) {
	LinkList q, p = L->next->next;/* pָ���һ����� */
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
	/* ��ʼ���������Ա�L�Ѵ��� */
	/* �����������cur_e��L������Ԫ��,�Ҳ������һ��,����next_e�������ĺ�̣� */
	/*           �������ʧ�ܣ�next_e�޶��� */
	LinkList p = L->next->next;/* pָ���һ����� */
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
	LinkList p = (*L)->next, s;/* pָ��ͷ��� */
	int j = 0;
	if (i<=0||i>ListLength_CL(*L)+1) /* �޷��ڵ�i��Ԫ��֮ǰ���� */
	{
		return ERROR;
	}
	while (j<i-1)/* Ѱ�ҵ�i-1����� */
	{
		p = p->next;
		j++;
	}
	s = (LinkList)malloc(sizeof(struct LNode));/* �����½�� */
	s->data = e;/* ����L�� */
	s->next = p->next;
	p->next = s;
	if (p == *L)/* �ı�β��� */
	{
		*L = s;
	}
	return OK;
}

Status ListDelete_CL(LinkList *L, int i, ElemType *e) {/* �ı�L */
	LinkList p = (*L)->next, q;/* pָ��ͷ��� */
	int j = 0;
	if (i <= 0||i>ListLength_CL(*L))/* ��i��Ԫ�ز����� */
	{
		return ERROR;
	}
	while (j<i-1) /* Ѱ�ҵ�i-1����� */
	{
		p = p->next;
		j++;
	}
	q = p->next;/* qָ���ɾ����� */
	p->next = q->next;
	*e = q->data;
	if (*L == q)/* ɾ�����Ǳ�βԪ�� */
	{
		*L = p;
	}
	free(q); /* �ͷŴ�ɾ����� */
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