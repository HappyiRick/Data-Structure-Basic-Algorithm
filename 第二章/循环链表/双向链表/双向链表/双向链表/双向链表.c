#include "predefine.h"

typedef int ElemType;
/*带头结点的线性链表类型*/
/* 结点类型 */
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*Link,*Position;

/* 链表类型 */
typedef struct LinkList {
	Link head, tail;/* 分别指向线性链表中的头结点和最后一个结点 */
	int len;/* 指示线性链表中数据元素的个数 */
}LinkList;

/*具有实用意义的线性链表*/
/* 分配由p指向的值为e的结点，并返回OK；若分配失败。则返回ERROR */
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
	/*释放p所指结点*/
	free(*p);
	*p = NULL;
}

/* 构造一个空的线性链表 */
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

/* 将线性链表L重置为空表，并释放原链表的结点空间 */
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

/* 销毁线性链表L，L不再存在 */
Status DestroyList(LinkList *L) {
	ClearList(L);
	FreeNode(&(*L).head);
	(*L).tail = NULL;
	(*L).len = 0;
	return OK;
}

/* 形参增加L,因为需修改L */
/* h指向L的一个结点，把h当做头结点，将s所指结点插入在第一个结点之前 */
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

/* 形参增加L,因为需修改L */
Status DeleteFirst(LinkList *L,Link h,Link *q) {
	/* h指向L的一个结点，把h当做头结点，删除链表中的第一个结点并以q返回。 */
	/* 若链表为空(h指向尾结点)，q=NULL，返回FALSE */
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
	/* 将指针s(s->data为第一个数据元素)所指(彼此以指针相链,以NULL结尾)的 */
	/* 一串结点链接在线性链表L的最后一个结点之后,并改变链表L的尾指针指向新 */
	/* 的尾结点 */
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

/* 已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置 */
/* 若无前驱，则返回NULL */
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

/* 删除线性链表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点 */
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

/* 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前， */
/* 并修改指针p指向新插入的结点 */
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

/* 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后， */
/* 并修改指针p指向新插入的结点 */
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
{ /* 已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值 */
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

/* 已知L为有序线性链表，将元素e按非降序插入在L中。（用于一元多项式） */
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

/* 若升序链表L中存在与e满足判定函数compare()取值为0的元素，则q指示L中 */
/* 第一个值为e的结点的位置，并返回TRUE；否则q指示第一个与e满足判定函数 */
/* compare()取值>0的元素的前驱的位置。并返回FALSE。（用于一元多项式） */
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
	/* 已知单链线性表La和Lb的元素按值非递减排列。归并La和Lb得到新的单链 */
	/* 线性表Lc，Lc的元素也按值非递减排列。（不改变La、Lb）算法2.21 */
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
		ListInsert_L(&La,j,j);//顺序插入12345
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