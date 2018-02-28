#include "predefine.h"
typedef int ElemType;
/* 带头结点的线性链表类型 */
typedef struct LNode /* 结点类型 */
{
	ElemType data;
	struct LNode *next;
}LNode, *Link, *Position;

typedef struct LinkList /* 链表类型 */
{
	Link head, tail; /* 分别指向线性链表中的头结点和最后一个结点 */
	int len; /* 指示线性链表中数据元素的个数 */
}LinkList;

/* bo2-6.c 具有实用意义的线性链表(存储结构由c2-5.h定义)的24个基本操作 */
Status MakeNode(Link *p, ElemType e)
{ /* 分配由p指向的值为e的结点，并返回OK；若分配失败。则返回ERROR */
	*p = (Link)malloc(sizeof(LNode));
	if (!*p)
		return ERROR;
	(*p)->data = e;
	return OK;
}

void FreeNode(Link *p)
{ /* 释放p所指结点 */
	free(*p);
	*p = NULL;
}

Status InitList(LinkList *L)
{ /* 构造一个空的线性链表 */
	Link p;
	p = (Link)malloc(sizeof(LNode)); /* 生成头结点 */
	if (p)
	{
		p->next = NULL;
		(*L).head = (*L).tail = p;
		(*L).len = 0;
		return OK;
	}
	else
		return ERROR;
}

Status ClearList(LinkList *L)
{ /* 将线性链表L重置为空表，并释放原链表的结点空间 */
	Link p, q;
	if ((*L).head != (*L).tail)/* 不是空表 */
	{
		p = q = (*L).head->next;
		(*L).head->next = NULL;
		while (p != (*L).tail)
		{
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

Status DestroyList(LinkList *L)
{ /* 销毁线性链表L，L不再存在 */
	ClearList(L); /* 清空链表 */
	FreeNode(&(*L).head);
	(*L).tail = NULL;
	(*L).len = 0;
	return OK;
}

Status InsFirst(LinkList *L, Link h, Link s) /* 形参增加L,因为需修改L */
{ /* h指向L的一个结点，把h当做头结点，将s所指结点插入在第一个结点之前 */
	s->next = h->next;
	h->next = s;
	if (h == (*L).tail) /* h指向尾结点 */
		(*L).tail = h->next; /* 修改尾指针 */
	(*L).len++;
	return OK;
}

Status DelFirst(LinkList *L, Link h, Link *q) /* 形参增加L,因为需修改L */
{ /* h指向L的一个结点，把h当做头结点，删除链表中的第一个结点并以q返回。 */
  /* 若链表为空(h指向尾结点)，q=NULL，返回FALSE */
	*q = h->next;
	if (*q) /* 链表非空 */
	{
		h->next = (*q)->next;
		if (!h->next) /* 删除尾结点 */
			(*L).tail = h; /* 修改尾指针 */
		(*L).len--;
		return OK;
	}
	else
		return FALSE; /* 链表空 */
}

Status Append(LinkList *L, Link s)
{ /* 将指针s(s->data为第一个数据元素)所指(彼此以指针相链,以NULL结尾)的 */
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

Position PriorPos(LinkList L, Link p)
{ /* 已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置 */
  /* 若无前驱，则返回NULL */
	Link q;
	q = L.head->next;
	if (q == p) /* 无前驱 */
		return NULL;
	else
	{
		while (q->next != p) /* q不是p的直接前驱 */
			q = q->next;
		return q;
	}
}

Status Remove(LinkList *L, Link *q)
{ /* 删除线性链表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点 */
	Link p = (*L).head;
	if ((*L).len == 0) /* 空表 */
	{
		*q = NULL;
		return FALSE;
	}
	while (p->next != (*L).tail)
		p = p->next;
	*q = (*L).tail;
	p->next = NULL;
	(*L).tail = p;
	(*L).len--;
	return OK;
}

Status InsBefore(LinkList *L, Link *p, Link s)
{ /* 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前， */
  /* 并修改指针p指向新插入的结点 */
	Link q;
	q = PriorPos(*L, *p); /* q是p的前驱 */
	if (!q) /* p无前驱 */
		q = (*L).head;
	s->next = *p;
	q->next = s;
	*p = s;
	(*L).len++;
	return OK;
}

Status InsAfter(LinkList *L, Link *p, Link s)
{ /* 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后， */
  /* 并修改指针p指向新插入的结点 */
	if (*p == (*L).tail) /* 修改尾指针 */
		(*L).tail = s;
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

ElemType GetCurElem(Link p)
{ /* 已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值 */
	return p->data;
}

Status ListEmpty(LinkList L)
{ /* 若线性链表L为空表，则返回TRUE，否则返回FALSE */
	if (L.len)
		return FALSE;
	else
		return TRUE;
}

int ListLength(LinkList L)
{ /* 返回线性链表L中元素个数 */
	return L.len;
}

Position GetHead(LinkList L)
{ /* 返回线性链表L中头结点的位置 */
	return L.head;
}

Position GetLast(LinkList L)
{ /* 返回线性链表L中最后一个结点的位置 */
	return L.tail;
}

Position NextPos(Link p)
{ /* 已知p指向线性链表L中的一个结点，返回p所指结点的直接后继的位置 */
  /* 若无后继，则返回NULL */
	return p->next;
}

Status LocatePos(LinkList L, int i, Link *p)
{ /* 返回p指示线性链表L中第i个结点的位置，并返回OK，i值不合法时返回ERROR */
  /* i=0为头结点 */
	int j;
	if (i<0 || i>L.len)
		return ERROR;
	else
	{
		*p = L.head;
		for (j = 1; j <= i; j++)
			*p = (*p)->next;
		return OK;
	}
}

Position LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
{ /* 返回线性链表L中第1个与e满足函数compare()判定关系的元素的位置， */
  /* 若不存在这样的元素，则返回NULL */
	Link p = L.head;
	do
		p = p->next;
	while (p && !(compare(p->data, e))); /* 没到表尾且没找到满足关系的元素 */
	return p;
}

Status ListTraverse(LinkList L, void(*visit)(ElemType))
{ /* 依次对L的每个数据元素调用函数visit()。一旦visit()失败，则操作失败 */
	Link p = L.head->next;
	int j;
	for (j = 1; j <= L.len; j++)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

Status OrderInsert(LinkList *L, ElemType e, int(*comp)(ElemType, ElemType))
{ /* 已知L为有序线性链表，将元素e按非降序插入在L中。（用于一元多项式） */
	Link o, p, q;
	q = (*L).head;
	p = q->next;
	while (p != NULL && comp(p->data, e)<0) /* p不是表尾且元素值小于e */
	{
		q = p;
		p = p->next;
	}
	o = (Link)malloc(sizeof(LNode)); /* 生成结点 */
	o->data = e; /* 赋值 */
	q->next = o; /* 插入 */
	o->next = p;
	(*L).len++; /* 表长加1 */
	if (!p) /* 插在表尾 */
		(*L).tail = o; /* 修改尾结点 */
	return OK;
}

Status LocateElemP(LinkList L, ElemType e, Position *q, int(*compare)(ElemType, ElemType))
{ /* 若升序链表L中存在与e满足判定函数compare()取值为0的元素，则q指示L中 */
  /* 第一个值为e的结点的位置，并返回TRUE；否则q指示第一个与e满足判定函数 */
  /* compare()取值>0的元素的前驱的位置。并返回FALSE。（用于一元多项式） */
	Link p = L.head, pp;
	do
	{
		pp = p;
		p = p->next;
	} while (p && (compare(p->data, e)<0)); /* 没到表尾且p->data.expn<e.expn */
	if (!p || compare(p->data, e)>0) /* 到表尾或compare(p->data,e)>0 */
	{
		*q = pp;
		return FALSE;
	}
	else /* 找到 */
	{
		*q = p;
		return TRUE;
	}
}

/* c4-2.h 串的堆分配存储 */
typedef struct
{
	char *ch; /* 若是非空串,则按串长分配存储区,否则ch为NULL */
	int length; /* 串长度 */
}HString;

/* bo4-2.c 串采用堆分配存储结构(由c4-2.h定义)的基本操作(15个) */
/* 包括算法4.1、4.4 */
Status StrAssign(HString *T, char *chars)
{ /* 生成一个其值等于串常量chars的串T */
	int i, j;
	if ((*T).ch)
		free((*T).ch); /* 释放T原有空间 */
	i = strlen(chars); /* 求chars的长度i */
	if (!i)
	{ /* chars的长度为0 */
		(*T).ch = NULL;
		(*T).length = 0;
	}
	else
	{ /* chars的长度不为0 */
		(*T).ch = (char*)malloc(i * sizeof(char)); /* 分配串空间 */
		if (!(*T).ch) /* 分配串空间失败 */
			exit(OVERFLOW);
		for (j = 0; j<i; j++) /* 拷贝串 */
			(*T).ch[j] = chars[j];
		(*T).length = i;
	}
	return OK;
}

Status StrCopy(HString *T, HString S)
{ /* 初始条件:串S存在。操作结果: 由串S复制得串T */
	int i;
	if ((*T).ch)
		free((*T).ch); /* 释放T原有空间 */
	(*T).ch = (char*)malloc(S.length * sizeof(char)); /* 分配串空间 */
	if (!(*T).ch) /* 分配串空间失败 */
		exit(OVERFLOW);
	for (i = 0; i<S.length; i++) /* 拷贝串 */
		(*T).ch[i] = S.ch[i];
	(*T).length = S.length;
	return OK;
}

Status StrEmpty(HString S)
{ /* 初始条件: 串S存在。操作结果: 若S为空串,则返回TRUE,否则返回FALSE */
	if (S.length == 0 && S.ch == NULL)
		return TRUE;
	else
		return FALSE;
}

int StrCompare(HString S, HString T)
{ /* 若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0 */
	int i;
	for (i = 0; i<S.length&&i<T.length; ++i)
		if (S.ch[i] != T.ch[i])
			return S.ch[i] - T.ch[i];
	return S.length - T.length;
}

int StrLength(HString S)
{ /* 返回S的元素个数,称为串的长度 */
	return S.length;
}

Status ClearString(HString *S)
{ /* 将S清为空串 */
	if ((*S).ch)
	{
		free((*S).ch);
		(*S).ch = NULL;
	}
	(*S).length = 0;
	return OK;
}

Status Concat(HString *T, HString S1, HString S2)
{ /* 用T返回由S1和S2联接而成的新串 */
	int i;
	if ((*T).ch)
		free((*T).ch); /* 释放旧空间 */
	(*T).length = S1.length + S2.length;
	(*T).ch = (char *)malloc((*T).length * sizeof(char));
	if (!(*T).ch)
		exit(OVERFLOW);
	for (i = 0; i<S1.length; i++)
		(*T).ch[i] = S1.ch[i];
	for (i = 0; i<S2.length; i++)
		(*T).ch[S1.length + i] = S2.ch[i];
	return OK;
}

Status SubString(HString *Sub, HString S, int pos, int len)
{ /* 用Sub返回串S的第pos个字符起长度为len的子串。 */
  /* 其中,1≤pos≤StrLength(S)且0≤len≤StrLength(S)-pos+1 */
	int i;
	if (pos<1 || pos>S.length || len<0 || len>S.length - pos + 1)
		return ERROR;
	if ((*Sub).ch)
		free((*Sub).ch); /* 释放旧空间 */
	if (!len) /* 空子串 */
	{
		(*Sub).ch = NULL;
		(*Sub).length = 0;
	}
	else
	{ /* 完整子串 */
		(*Sub).ch = (char*)malloc(len * sizeof(char));
		if (!(*Sub).ch)
			exit(OVERFLOW);
		for (i = 0; i <= len - 1; i++)
			(*Sub).ch[i] = S.ch[pos - 1 + i];
		(*Sub).length = len;
	}
	return OK;
}

void InitString(HString *T)
{ /* 初始化(产生空串)字符串T。另加 */
	(*T).length = 0;
	(*T).ch = NULL;
}

int Index(HString S, HString T, int pos) /* 算法4.1 */
{ /* T为非空串。若主串S中第pos个字符之后存在与T相等的子串, */
  /* 则返回第一个这样的子串在S中的位置,否则返回0 */
	int n, m, i;
	HString sub;
	InitString(&sub);
	if (pos>0)
	{
		n = StrLength(S);
		m = StrLength(T);
		i = pos;
		while (i <= n - m + 1)
		{
			SubString(&sub, S, i, m);
			if (StrCompare(sub, T) != 0)
				++i;
			else
				return i;
		}
	}
	return 0;
}

Status StrInsert(HString *S, int pos, HString T) /* 算法4.4 */
{ /* 1≤pos≤StrLength(S)+1。在串S的第pos个字符之前插入串T */
	int i;
	if (pos<1 || pos>(*S).length + 1) /* pos不合法 */
		return ERROR;
	if (T.length) /* T非空,则重新分配空间,插入T */
	{
		(*S).ch = (char*)realloc((*S).ch, ((*S).length + T.length) * sizeof(char));
		if (!(*S).ch)
			exit(OVERFLOW);
		for (i = (*S).length - 1; i >= pos - 1; --i) /* 为插入T而腾出位置 */
			(*S).ch[i + T.length] = (*S).ch[i];
		for (i = 0; i<T.length; i++)
			(*S).ch[pos - 1 + i] = T.ch[i]; /* 插入T */
		(*S).length += T.length;
	}
	return OK;
}

Status StrDelete(HString *S, int pos, int len)
{ /* 从串S中删除第pos个字符起长度为len的子串 */
	int i;
	if ((*S).length<pos + len - 1)
		exit(ERROR);
	for (i = pos - 1; i <= (*S).length - len; i++)
		(*S).ch[i] = (*S).ch[i + len];
	(*S).length -= len;
	(*S).ch = (char*)realloc((*S).ch, (*S).length * sizeof(char));
	return OK;
}

Status Replace(HString *S, HString T, HString V)
{ /* 初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关） */
  /* 操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串 */
	int i = 1; /* 从串S的第一个字符起查找串T */
	if (StrEmpty(T)) /* T是空串 */
		return ERROR;
	do
	{
		i = Index(*S, T, i); /* 结果i为从上一个i之后找到的子串T的位置 */
		if (i) /* 串S中存在串T */
		{
			StrDelete(S, i, StrLength(T)); /* 删除该串T */
			StrInsert(S, i, V); /* 在原串T的位置插入串V */
			i += StrLength(V); /* 在插入的串V后面继续查找串T */
		}
	} while (i);
	return OK;
}

void DestroyString()
{ /* 堆分配类型的字符串无法销毁 */
}

void StrPrint(HString T)
{ /* 输出T字符串。另加 */
	int i;
	for (i = 0; i<T.length; i++)
		printf("%c", T.ch[i]);
	printf("\n");
}

//主程序
#define MaxKeyNum 25
#define MaxLineLen 51
#define MaxWordNum 10
#define MaxNoIdx 10
typedef struct {
	char *item[MaxWordNum];
	int last;
}WordListType;

typedef struct {
	HString key;
	LinkList bnolist;
}IdxTermType;

typedef struct {
	IdxTermType item[MaxKeyNum+1];
	int last;
}IdxListType;

typedef struct {
	char *item[MaxNoIdx];
	int last;
}NoIdxType;

char buf[MaxLineLen+1];
WordListType wdlist;
NoIdxType noidx;

void InitIdxList(IdxListType *idxlist) {
	(*idxlist).last = 0;
	InitString(&(*idxlist).item[0].key);
	InitList(&(*idxlist).item[0].bnolist);
}

void ExtractKeyWord(int *BookNo) {
	int i, l, f = 1;
	char *s1, *s2;
	if (buf[0]<'0'||buf[0]>'9')
	{
		exit(OVERFLOW);
	}
	for ( i = 1; i <= wdlist.last; i++)
	{
		free(wdlist.item[i]);
		wdlist.item[i] = NULL;
	}
	wdlist.last = 0;
	*BookNo = (buf[0]-'0')*100+(buf[1]-'0')*10+(buf[2]-'0');
	s2 = &buf[2];
	do
	{
		s1 = s2 + 1;
		s2 = strchr(s1,' ');
		if (!s2)
		{
			s2 = strchr(s1,'\12');
			f = 0;
		}
		l = s2 - s1;
		if (s1[0]>='A'&&s1[0]<='Z')
		{
			wdlist.item[wdlist.last] = (char*)malloc((l+1)*sizeof(char));
			for ( i = 0; i < l; i++)
			{
				wdlist.item[wdlist.last][i] = s1[i];
			}
			wdlist.item[wdlist.last][1] = 0;
			for ( i = 0; i < noidx.last; i++)
			{
				if (!strcmp(wdlist.item[wdlist.last],noidx.item[i]))
				{
					break;
				}
			}
			if (i!=noidx.last)
			{
				free(wdlist.item[wdlist.last]);
				wdlist.item[wdlist.last] = NULL;
			}
			else {
				wdlist.last++;
			}
		}
	} while (f);
}

void GetWord(int i,HString *wd) {
	StrAssign(wd,wdlist.item[i]);
}

int Locate(IdxListType *idxlist,HString wd,Status *b) {
	int i, m;
	for ( i = (*idxlist).last; (m = StrCompare((*idxlist).item[i].key,wd))>0; i--)
	{
		if (m == 0)
		{
			*b = TRUE;
			return i;
		}
		else {
			*b = FALSE;
			return i + 1;
		}
	}
}

void InsertNewKey(IdxListType *idxlist,int i,HString wd) {
	int j;
	InitList(&(*idxlist).item[(*idxlist).last+1].bnolist);
	for ( j = (*idxlist).last; j >= 1; --j)
	{
		(*idxlist).item[j + 1] = (*idxlist).item[j];
	}
	InitString(&(*idxlist).item[i].key);
	StrCopy(&(*idxlist).item[i].key,wd);
	InitList(&(*idxlist).item[i].bnolist);
	(*idxlist).last++;
}

void InsertBook(IdxListType *idxlist,int i,int bno) {
	Link p;
	if (!MakeNode(&p,bno))
	{
		exit(OVERFLOW);
	}
	p->next = NULL;
	Append(&(*idxlist).item[i].bnolist,p);
}

/* 将书号为bno的关键词插入索引表 */
void InsIdxList(IdxListType *idxlist,int bno) {
	int i, j;
	Status b;
	HString wd;
	InitString(&wd);
	for ( i = 0; i < wdlist.last; i++)
	{
		GetWord(i,&wd);
		j = Locate(idxlist,wd,&b);
		if (!b)
		{
			InsertNewKey(idxlist,j,wd);
		}
		InsertBook(idxlist,j,bno);
	}
}

void PutText(FILE *f,IdxListType idxlist) {
	int i, j;
	Link p;
	fprintf(f,"%d\n",idxlist.last);
	for ( i = 1; i <= idxlist.last; i++)
	{
		for ( j = 0; j < idxlist.item[i].key.length; j++)
		{
			fprintf(f, "%c", idxlist.item[i].key.ch[j]);
		}
		fprintf(f, "\n%d\n", idxlist.item[i].bnolist.len);
		p = idxlist.item[i].bnolist.head;
		for (j = 1; j <= idxlist.item[i].bnolist.len; j++)
		{
			p = p->next;
			fprintf(f, "%d ", p->data);
		}
		fprintf(f, "\n");
	}
}

void main()
{
	FILE *f; /* 任何时间最多打开一个文件 */
	IdxListType idxlist; /* 索引表 */
	int BookNo; /* 书号变量 */
	int k, l;
	f = fopen("NoIdx.txt", "r"); /* 打开常用词文件 */
	if (!f)
		exit(OVERFLOW);
	fscanf(f, "%d", &noidx.last); /* 常用词个数 */
	for (k = 0; k<noidx.last; k++) /* 把常用词文件的内容拷到noidx中 */
	{
		fscanf(f, "%s", buf);
		l = strlen(buf);
		noidx.item[k] = (char*)malloc(l * sizeof(char));
		strcpy(noidx.item[k], buf);
	}
	fclose(f);
	f = fopen("BookInfo.txt", "r"); /* 打开书目文件 */
	if (!f)
		exit(FALSE);
	InitIdxList(&idxlist); /* 初始化索引表idxlist为空 */
	wdlist.last = 0; /* 词表长度初值为0 */
	while (!feof(f))
	{
		fgets(buf, MaxLineLen, f);
		l = strlen(buf);
		if (l <= 1)
			break;
		ExtractKeyWord(&BookNo); /* 从buf中提取关键词到词表，书号存入BookNo */
		InsIdxList(&idxlist, BookNo);
	}
	fclose(f);
	f = fopen("BookIdx.txt", "w");
	if (!f)
		exit(INFEASIBLE);
	PutText(f, idxlist); /* 将生成的索引表idxlist输出到文件f */
	fclose(f);
	system("pause");
}