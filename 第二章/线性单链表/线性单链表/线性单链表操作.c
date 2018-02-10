#define _CRT_SECURE_NO_WARNINGS //����SDL��������C4996����
#include "predefine.h"
typedef int ElemType;

/*���Ե�����洢�ṹ*/
typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

/*������ʵ�����Ա��������*/
Status InitList(LinkList *L) {
	*L = (LinkList)malloc(sizeof(struct LNode));
	if (!*L)
	{
		exit(OVERFLOW);
	}
	(*L)->next = NULL;
	return OK;
}

Status DestroyList(LinkList *L) {
	LinkList q;
	while (*L)
	{
		q = (*L)->next;
		free(*L);
		*L = q;
	}
	return OK;
}

Status ListEmpty(LinkList L) {
	if (L->next)
	{
		return FALSE;
	}
	return TRUE;
}

int ListLength(LinkList L) {
	int i = 0;
	LinkList p = L->next;
	while (p) {
		i++;
		p->next;
	}
	return i;
}

Status GetElem(LinkList L,int i,ElemType *e) {
	int j = 1;
	LinkList p = L->next;
	while (p&&j<i)
	{
		p = p->next;
		j++;
	}
	if (!p || j>i)
	{
		return ERROR;
	}
	*e = p->data;
	return OK;
}

int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType)) {
	int i = 0;
	LinkList p = L->next;
	while(p)
	{
		i++;
		if (compare(p->data,e))
		{
			return i;
		}
		p = p->next;
	}
	return 0;
}

Status PriorElem(LinkList L,ElemType cur_e,ElemType *pre_e) {
	LinkList q, p = L->next;
	while (p->next)
	{
		q = p->next;
		if (q->data == cur_e)
		{
			*pre_e = p->data;
			return OK;
		}
		p = q;
	}
	return INFEASIBLE;
}

Status NextElem(LinkList L,ElemType cur_e,ElemType *next_e) {
	LinkList p = L->next;
	while (p->next)
	{
		if (p->data == cur_e)
		{	
			*next_e = p->next->data;
			return OK;
		}
		p = p->next;
	}
	return INFEASIBLE;
}

Status ListInsert(LinkList L,int i, ElemType e) {
	int j = 0;
	LinkList p = L, s;
	while (p&&j<i-1)
	{
		p = p->next;
		j++;
	}
	if (!p||j>i-1)
	{	
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(struct LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

Status ListDelete(LinkList L,int i,ElemType *e) {
	int j = 0;
	LinkList p = L, q;
	while (p->next&&j<i-1)
	{
		p = p->next;
		j++;
	}
	if (!p->next||j>i-1)
	{
		return ERROR;
	}
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}

Status ListTraverse(LinkList L,void (*vi)(ElemType)) {
	LinkList p = L->next;
	while (p) {
		vi(p->data);
		p = p->next;
	}
	printf("/n");
	return OK;
}


//��λ�򣨲��ڱ�ͷ������n��Ԫ�ص�ֵ����������ͷ�ṹ�ĵ������Ա�L
//�㷨2.11
void CreatList(LinkList *L, int n) {
	int i;
	LinkList p;
	*L = (LinkList)malloc(sizeof(struct LNode));
	(*L)->next = NULL;
	printf("������%d������",n);
	for ( i = n; i > 0; --i)
	{
		p = (LinkList)malloc(sizeof(struct  LNode));
		scanf("%d",&p->data);
		p->next = (*L)->next;
		(*L)->next = p;
	}
}

//��λ�򣨲��ڱ�β������n��Ԫ�ص�ֵ����������ͷ�ṹ�ĵ������Ա�
void CreatList2(LinkList *L, int n) {
	int i;
	LinkList p, q;
	*L = (LinkList)malloc(sizeof(struct LNode));
	(*L)->next = NULL;
	q = *L;
	printf("������%d������",n);
	for ( i = 1; i <- n; i++)
	{
		p = (LinkList)malloc(sizeof(struct LNode));
		scanf("%d",&p->data);
		q->next = p;
		q = q->next;
	}
	//p->next = NULL;
}

//�㷨2.12
void MergeList(LinkList La,LinkList *Lb,LinkList *Lc) {
	LinkList pa = La->next, pb = (*Lb)->next, pc;
	*Lc = pc = La;
	while (pa&&pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free(*Lb);
	Lb = NULL;
}

void visit(ElemType c) {
	printf("%d",c);
}

int main(void) {
	int n = 5;
	LinkList La, Lb, Lc;
	printf("���ǵݼ�˳��:\n");
	CreatList(&La,n);
	printf("La = ");
	ListTraverse(La, visit);
	CreatList(&Lb, n);
	printf("Lb = ");
	ListTraverse(Lb,visit);
	MergeList(La,&Lb,&Lc);
	printf("Lc = ");
	ListTraverse(Lc, visit);
	system("pause");
	return 0;
}