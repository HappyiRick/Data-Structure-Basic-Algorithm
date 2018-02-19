#include "predefine.h"

typedef int ElemType;
/*��ͷ����������������*/
/* ������� */
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*Link,*Position;

/* �������� */
typedef struct LinkList {
	Link head, tail;/* �ֱ�ָ�����������е�ͷ�������һ����� */
	int len;/* ָʾ��������������Ԫ�صĸ��� */
}LinkList;

/*����ʵ���������������*/
/* ������pָ���ֵΪe�Ľ�㣬������OK��������ʧ�ܡ��򷵻�ERROR */
Status MakeNode(Link *p,ElemType e) {
	*p = (Link)malloc(sizeof(LNode));
	if (!*p)
	{
		return ERROR;
	}
	(*p)->data = e;
	return OK;
}

void FreeNode(Link *p) {
	/*�ͷ�p��ָ���*/
	free(*p);
	*p = NULL;
}

/* ����һ���յ��������� */
Status InitList(LinkList *L) {
	Link p;
	p = (Link)malloc(sizeof(LNode));
	if (p)
	{
		p->next = NULL;
		(*L).head = (*L).tail = p;
		(*L).len = 0;
		return OK;
	}
	else {
		return ERROR;
	}
}

/* ����������L����Ϊ�ձ����ͷ�ԭ����Ľ��ռ� */
Status ClearList(LinkList *L) {
	Link p, q;
	if ((*L).head!=(*L).tail)
	{
		p = q = (*L).head->next;
		(*L).head->next = NULL;
		while (p!=(*L).tail) {
			p = q->next;
			free(q);
			q = p;
		}
		free(q);
		(*L).tail = (*L).head;
		(*L).len = 0;
	}
	return OK;
}

/* ������������L��L���ٴ��� */
Status DestroyList(LinkList *L) {
	ClearList(L);
	FreeNode(&(*L).head);
	(*L).tail = NULL;
	(*L).len = 0;
	return OK;
}

/* �β�����L,��Ϊ���޸�L */
/* hָ��L��һ����㣬��h����ͷ��㣬��s��ָ�������ڵ�һ�����֮ǰ */
Status InsertFirst(LinkList *L,Link h,Link s) {
	s->next = h->next;
	h->next = s;
	if (h == (*L).tail)
	{
		(*L).tail = h->next;
	}
	(*L).len++;
	return OK;
}

/* �β�����L,��Ϊ���޸�L */
Status DeleteFirst(LinkList *L,Link h,Link *q) {
	/* hָ��L��һ����㣬��h����ͷ��㣬ɾ�������еĵ�һ����㲢��q���ء� */
	/* ������Ϊ��(hָ��β���)��q=NULL������FALSE */
	*q = h->next;
	if (*q)
	{
		h->next = (*q)->next;
		if (!h->next)
		{
			(*L).tail = h;
		}
		(*L).len--;
		return OK;
	}
	else
	{
		return FALSE;
	}
}

Status Append(LinkList *L,Link s) {
	/* ��ָ��s(s->dataΪ��һ������Ԫ��)��ָ(�˴���ָ������,��NULL��β)�� */
	/* һ�������������������L�����һ�����֮��,���ı�����L��βָ��ָ���� */
	/* ��β��� */
	int i = 1;
	(*L).tail->next = s;
	while (s->next)
	{
		s = s->next;
		i++;
	}
	(*L).tail = s;
	(*L).len += i;
	return OK;
}

/* ��֪pָ����������L�е�һ����㣬����p��ָ����ֱ��ǰ����λ�� */
/* ����ǰ�����򷵻�NULL */
Position PriorPos(LinkList L,Link p) {
	Link q;
	q = L.head->next;
	if (q == p)
	{
		return NULL;
	}
	else {
		while (q->next!=p) {
			q = q->next;
		}
		return q;
	}
}

/* ɾ����������L�е�β��㲢��q���أ��ı�����L��βָ��ָ���µ�β��� */
Status Remove(LinkList *L,Link *q) {
	Link p = (*L).head;
	if ((*L).len == 0)
	{
		*q = NULL;
		return FALSE;
	}
	while (p->next!=(*L).tail)
	{
		p = p->next;
	}
	*q = (*L).tail;
	p->next = NULL;
	(*L).tail = p;
	(*L).len--;
	return OK;
}

/* ��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮ǰ�� */
/* ���޸�ָ��pָ���²���Ľ�� */
Status InsertBefore(LinkList *L,Link *p,Link s) {
	Link q;
	q = PriorPos(*L,*p);
	if (!q)
	{
		q = (*L).head;
	}
	s->next = *p;
	q->next = s;
	*p = s;
	(*L).len++;
	return OK;
}

/* ��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮�� */
/* ���޸�ָ��pָ���²���Ľ�� */
Status InsertAfter(LinkList *L,Link *p,Link s) {
	if (*p == (*L).tail)
	{
		(*L).tail = s;
	}
	s->next = (*p)->next;
	(*p)->next = s;
	*p = s;
	(*L).len++;
	return OK;
}

Status SetCurElem(Link p, ElemType e)
{ /* ��֪pָ�����������е�һ����㣬��e����p��ָ���������Ԫ�ص�ֵ */
	p->data = e;
	return OK;
}

ElemType GetCurElem(Link p) {
	return p->data;
}

Status ListEmpty(LinkList L) {
	if (L.len)
	{
		return FALSE;
	}
	else {
		return TRUE;
	}
}

int ListLength(LinkList L) {
	return L.len;
}

Position GetHead(LinkList L) {
	return L.head;
}

Position GetLast(LinkList L) {
	return L.tail;
}

Position NextPos(Link p) {
	return p->next;
}

Status LocatePos(LinkList L,int i,Link *p) {
	int j;
	if (i<0||i>L.len)
	{
		return ERROR;
	}
	else {
		*p = L.head;
		for ( j = 1; j <= i; j++)
		{
			*p = (*p)->next;
		}
		return OK;
	}
}

Position LocateElem(LinkList L,ElemType e,Status (*compare)(ElemType,ElemType)) {
	Link p = L.head;
	do
	{
		p = p->next;
	} while (p&&!(compare(p->data,e)));
	return p;
}

Status ListTraverse(LinkList L,void(*visit)(ElemType)) {
	Link p = L.head->next;
	int j;
	for ( j = 1; j <= L.len; j++)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

/* ��֪LΪ��������������Ԫ��e���ǽ��������L�С�������һԪ����ʽ�� */
Status OrderInsert(LinkList *L,ElemType e,int (*comp)(ElemType,ElemType)) {
	Link o, p, q;
	q = (*L).head;
	p = q->next;
	while (p!=NULL&&comp(p->data,e)<0)
	{
		q = p;
		p = p->next;
	}
	o = (Link)malloc(sizeof(LNode));
	o->data = e;
	q->next = o;
	o->next = p;
	(*L).len++;
	if (!p)
	{
		(*L).tail = o;
	}
	return OK;
}

/* ����������L�д�����e�����ж�����compare()ȡֵΪ0��Ԫ�أ���qָʾL�� */
/* ��һ��ֵΪe�Ľ���λ�ã�������TRUE������qָʾ��һ����e�����ж����� */
/* compare()ȡֵ>0��Ԫ�ص�ǰ����λ�á�������FALSE��������һԪ����ʽ�� */
Status LocateElemP(LinkList L,ElemType e,Position *q,int (*compare)(ElemType,ElemType)) {
	Link p = L.head, pp;
	do
	{
		pp = p;
		p = p->next;
	} while (p&&(compare(p->data,e)<0));
	if (!p||compare(p->data,e)>0)
	{
		*q = pp;
		return FALSE;
	}
	else {
		*q = p;
		return TRUE;
	}
}

Status ListInsert_L(LinkList *L,int i,ElemType e) {
	Link h, s;
	if (!LocatePos(*L,i-1,&h))
	{
		return ERROR;
	}
	if (!MakeNode(&s,e))
	{
		return ERROR;
	}
	InsertFirst(L,h,s);
	return OK;
}

Status MergeList_L(LinkList La,LinkList Lb,LinkList *Lc,int(*compare)(ElemType,ElemType)) {
	/* ��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����С��鲢La��Lb�õ��µĵ��� */
	/* ���Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ����С������ı�La��Lb���㷨2.21 */
	Link ha, hb, pa, pb, q;
	ElemType a, b;
	if (!InitList(Lc))
	{
		return ERROR;
	}
	ha = GetHead(La);
	hb = GetHead(Lb);
	pa = NextPos(ha);
	pb = NextPos(hb);
	while (!ListEmpty(La)&&!ListEmpty(Lb))
	{
		a = GetCurElem(pa);
		b = GetCurElem(pb);
		if (compare(a,b)<=0)
		{
			DeleteFirst(&La,ha,&q);
			InsertFirst(Lc,(*Lc).tail,q);
			pb = NextPos(hb);
		}
		else {
			DeleteFirst(&Lb, hb, &q);
			InsertFirst(Lc,(*Lc).tail,q);
			pb = NextPos(hb);
		}
	}
	if (!ListEmpty(La))
	{
		Append(Lc, pa);
	}
	else {
		Append(Lc,pb);
	}
	FreeNode(&ha);
	FreeNode(&hb);
	return OK;
}

int comp(ElemType c1, ElemType c2) {
	return c1 - c2;
}

void visit(ElemType c) {
	printf("%d",c);
}

void main() {
	LinkList La, Lb, Lc;
	int j;
	InitList(&La);
	for ( j = 1; j <= 5; j++)
	{
		ListInsert_L(&La,j,j);//˳�����12345
	}
	printf("La=");
	ListTraverse(La, visit);
	InitList(&Lb);
	for (j = 1; j <= 5; j++)
	{
		ListInsert_L(&Lb,j,2*j);
	}
	printf("Lb=");
	ListTraverse(Lb,visit);
	InitList(&Lc);
	MergeList_L(La,Lb,&Lc,comp);
	printf("Lc=");
	ListTraverse(Lc,visit);
	DestroyList(&Lc);
	system("pause");
}