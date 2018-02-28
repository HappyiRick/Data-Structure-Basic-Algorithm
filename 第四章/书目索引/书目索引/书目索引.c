#include "predefine.h"
typedef int ElemType;
/* ��ͷ���������������� */
typedef struct LNode /* ������� */
{
	ElemType data;
	struct LNode *next;
}LNode, *Link, *Position;

typedef struct LinkList /* �������� */
{
	Link head, tail; /* �ֱ�ָ�����������е�ͷ�������һ����� */
	int len; /* ָʾ��������������Ԫ�صĸ��� */
}LinkList;

/* bo2-6.c ����ʵ���������������(�洢�ṹ��c2-5.h����)��24���������� */
Status MakeNode(Link *p, ElemType e)
{ /* ������pָ���ֵΪe�Ľ�㣬������OK��������ʧ�ܡ��򷵻�ERROR */
	*p = (Link)malloc(sizeof(LNode));
	if (!*p)
		return ERROR;
	(*p)->data = e;
	return OK;
}

void FreeNode(Link *p)
{ /* �ͷ�p��ָ��� */
	free(*p);
	*p = NULL;
}

Status InitList(LinkList *L)
{ /* ����һ���յ��������� */
	Link p;
	p = (Link)malloc(sizeof(LNode)); /* ����ͷ��� */
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
{ /* ����������L����Ϊ�ձ����ͷ�ԭ����Ľ��ռ� */
	Link p, q;
	if ((*L).head != (*L).tail)/* ���ǿձ� */
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
{ /* ������������L��L���ٴ��� */
	ClearList(L); /* ������� */
	FreeNode(&(*L).head);
	(*L).tail = NULL;
	(*L).len = 0;
	return OK;
}

Status InsFirst(LinkList *L, Link h, Link s) /* �β�����L,��Ϊ���޸�L */
{ /* hָ��L��һ����㣬��h����ͷ��㣬��s��ָ�������ڵ�һ�����֮ǰ */
	s->next = h->next;
	h->next = s;
	if (h == (*L).tail) /* hָ��β��� */
		(*L).tail = h->next; /* �޸�βָ�� */
	(*L).len++;
	return OK;
}

Status DelFirst(LinkList *L, Link h, Link *q) /* �β�����L,��Ϊ���޸�L */
{ /* hָ��L��һ����㣬��h����ͷ��㣬ɾ�������еĵ�һ����㲢��q���ء� */
  /* ������Ϊ��(hָ��β���)��q=NULL������FALSE */
	*q = h->next;
	if (*q) /* ����ǿ� */
	{
		h->next = (*q)->next;
		if (!h->next) /* ɾ��β��� */
			(*L).tail = h; /* �޸�βָ�� */
		(*L).len--;
		return OK;
	}
	else
		return FALSE; /* ����� */
}

Status Append(LinkList *L, Link s)
{ /* ��ָ��s(s->dataΪ��һ������Ԫ��)��ָ(�˴���ָ������,��NULL��β)�� */
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

Position PriorPos(LinkList L, Link p)
{ /* ��֪pָ����������L�е�һ����㣬����p��ָ����ֱ��ǰ����λ�� */
  /* ����ǰ�����򷵻�NULL */
	Link q;
	q = L.head->next;
	if (q == p) /* ��ǰ�� */
		return NULL;
	else
	{
		while (q->next != p) /* q����p��ֱ��ǰ�� */
			q = q->next;
		return q;
	}
}

Status Remove(LinkList *L, Link *q)
{ /* ɾ����������L�е�β��㲢��q���أ��ı�����L��βָ��ָ���µ�β��� */
	Link p = (*L).head;
	if ((*L).len == 0) /* �ձ� */
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
{ /* ��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮ǰ�� */
  /* ���޸�ָ��pָ���²���Ľ�� */
	Link q;
	q = PriorPos(*L, *p); /* q��p��ǰ�� */
	if (!q) /* p��ǰ�� */
		q = (*L).head;
	s->next = *p;
	q->next = s;
	*p = s;
	(*L).len++;
	return OK;
}

Status InsAfter(LinkList *L, Link *p, Link s)
{ /* ��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮�� */
  /* ���޸�ָ��pָ���²���Ľ�� */
	if (*p == (*L).tail) /* �޸�βָ�� */
		(*L).tail = s;
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

ElemType GetCurElem(Link p)
{ /* ��֪pָ�����������е�һ����㣬����p��ָ���������Ԫ�ص�ֵ */
	return p->data;
}

Status ListEmpty(LinkList L)
{ /* ����������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
	if (L.len)
		return FALSE;
	else
		return TRUE;
}

int ListLength(LinkList L)
{ /* ������������L��Ԫ�ظ��� */
	return L.len;
}

Position GetHead(LinkList L)
{ /* ������������L��ͷ����λ�� */
	return L.head;
}

Position GetLast(LinkList L)
{ /* ������������L�����һ������λ�� */
	return L.tail;
}

Position NextPos(Link p)
{ /* ��֪pָ����������L�е�һ����㣬����p��ָ����ֱ�Ӻ�̵�λ�� */
  /* ���޺�̣��򷵻�NULL */
	return p->next;
}

Status LocatePos(LinkList L, int i, Link *p)
{ /* ����pָʾ��������L�е�i������λ�ã�������OK��iֵ���Ϸ�ʱ����ERROR */
  /* i=0Ϊͷ��� */
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
{ /* ������������L�е�1����e���㺯��compare()�ж���ϵ��Ԫ�ص�λ�ã� */
  /* ��������������Ԫ�أ��򷵻�NULL */
	Link p = L.head;
	do
		p = p->next;
	while (p && !(compare(p->data, e))); /* û����β��û�ҵ������ϵ��Ԫ�� */
	return p;
}

Status ListTraverse(LinkList L, void(*visit)(ElemType))
{ /* ���ζ�L��ÿ������Ԫ�ص��ú���visit()��һ��visit()ʧ�ܣ������ʧ�� */
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
{ /* ��֪LΪ��������������Ԫ��e���ǽ��������L�С�������һԪ����ʽ�� */
	Link o, p, q;
	q = (*L).head;
	p = q->next;
	while (p != NULL && comp(p->data, e)<0) /* p���Ǳ�β��Ԫ��ֵС��e */
	{
		q = p;
		p = p->next;
	}
	o = (Link)malloc(sizeof(LNode)); /* ���ɽ�� */
	o->data = e; /* ��ֵ */
	q->next = o; /* ���� */
	o->next = p;
	(*L).len++; /* ����1 */
	if (!p) /* ���ڱ�β */
		(*L).tail = o; /* �޸�β��� */
	return OK;
}

Status LocateElemP(LinkList L, ElemType e, Position *q, int(*compare)(ElemType, ElemType))
{ /* ����������L�д�����e�����ж�����compare()ȡֵΪ0��Ԫ�أ���qָʾL�� */
  /* ��һ��ֵΪe�Ľ���λ�ã�������TRUE������qָʾ��һ����e�����ж����� */
  /* compare()ȡֵ>0��Ԫ�ص�ǰ����λ�á�������FALSE��������һԪ����ʽ�� */
	Link p = L.head, pp;
	do
	{
		pp = p;
		p = p->next;
	} while (p && (compare(p->data, e)<0)); /* û����β��p->data.expn<e.expn */
	if (!p || compare(p->data, e)>0) /* ����β��compare(p->data,e)>0 */
	{
		*q = pp;
		return FALSE;
	}
	else /* �ҵ� */
	{
		*q = p;
		return TRUE;
	}
}

/* c4-2.h ���Ķѷ���洢 */
typedef struct
{
	char *ch; /* ���Ƿǿմ�,�򰴴�������洢��,����chΪNULL */
	int length; /* ������ */
}HString;

/* bo4-2.c �����öѷ���洢�ṹ(��c4-2.h����)�Ļ�������(15��) */
/* �����㷨4.1��4.4 */
Status StrAssign(HString *T, char *chars)
{ /* ����һ����ֵ���ڴ�����chars�Ĵ�T */
	int i, j;
	if ((*T).ch)
		free((*T).ch); /* �ͷ�Tԭ�пռ� */
	i = strlen(chars); /* ��chars�ĳ���i */
	if (!i)
	{ /* chars�ĳ���Ϊ0 */
		(*T).ch = NULL;
		(*T).length = 0;
	}
	else
	{ /* chars�ĳ��Ȳ�Ϊ0 */
		(*T).ch = (char*)malloc(i * sizeof(char)); /* ���䴮�ռ� */
		if (!(*T).ch) /* ���䴮�ռ�ʧ�� */
			exit(OVERFLOW);
		for (j = 0; j<i; j++) /* ������ */
			(*T).ch[j] = chars[j];
		(*T).length = i;
	}
	return OK;
}

Status StrCopy(HString *T, HString S)
{ /* ��ʼ����:��S���ڡ��������: �ɴ�S���Ƶô�T */
	int i;
	if ((*T).ch)
		free((*T).ch); /* �ͷ�Tԭ�пռ� */
	(*T).ch = (char*)malloc(S.length * sizeof(char)); /* ���䴮�ռ� */
	if (!(*T).ch) /* ���䴮�ռ�ʧ�� */
		exit(OVERFLOW);
	for (i = 0; i<S.length; i++) /* ������ */
		(*T).ch[i] = S.ch[i];
	(*T).length = S.length;
	return OK;
}

Status StrEmpty(HString S)
{ /* ��ʼ����: ��S���ڡ��������: ��SΪ�մ�,�򷵻�TRUE,���򷵻�FALSE */
	if (S.length == 0 && S.ch == NULL)
		return TRUE;
	else
		return FALSE;
}

int StrCompare(HString S, HString T)
{ /* ��S>T,�򷵻�ֵ>0;��S=T,�򷵻�ֵ=0;��S<T,�򷵻�ֵ<0 */
	int i;
	for (i = 0; i<S.length&&i<T.length; ++i)
		if (S.ch[i] != T.ch[i])
			return S.ch[i] - T.ch[i];
	return S.length - T.length;
}

int StrLength(HString S)
{ /* ����S��Ԫ�ظ���,��Ϊ���ĳ��� */
	return S.length;
}

Status ClearString(HString *S)
{ /* ��S��Ϊ�մ� */
	if ((*S).ch)
	{
		free((*S).ch);
		(*S).ch = NULL;
	}
	(*S).length = 0;
	return OK;
}

Status Concat(HString *T, HString S1, HString S2)
{ /* ��T������S1��S2���Ӷ��ɵ��´� */
	int i;
	if ((*T).ch)
		free((*T).ch); /* �ͷžɿռ� */
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
{ /* ��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ��� */
  /* ����,1��pos��StrLength(S)��0��len��StrLength(S)-pos+1 */
	int i;
	if (pos<1 || pos>S.length || len<0 || len>S.length - pos + 1)
		return ERROR;
	if ((*Sub).ch)
		free((*Sub).ch); /* �ͷžɿռ� */
	if (!len) /* ���Ӵ� */
	{
		(*Sub).ch = NULL;
		(*Sub).length = 0;
	}
	else
	{ /* �����Ӵ� */
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
{ /* ��ʼ��(�����մ�)�ַ���T����� */
	(*T).length = 0;
	(*T).ch = NULL;
}

int Index(HString S, HString T, int pos) /* �㷨4.1 */
{ /* TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ�, */
  /* �򷵻ص�һ���������Ӵ���S�е�λ��,���򷵻�0 */
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

Status StrInsert(HString *S, int pos, HString T) /* �㷨4.4 */
{ /* 1��pos��StrLength(S)+1���ڴ�S�ĵ�pos���ַ�֮ǰ���봮T */
	int i;
	if (pos<1 || pos>(*S).length + 1) /* pos���Ϸ� */
		return ERROR;
	if (T.length) /* T�ǿ�,�����·���ռ�,����T */
	{
		(*S).ch = (char*)realloc((*S).ch, ((*S).length + T.length) * sizeof(char));
		if (!(*S).ch)
			exit(OVERFLOW);
		for (i = (*S).length - 1; i >= pos - 1; --i) /* Ϊ����T���ڳ�λ�� */
			(*S).ch[i + T.length] = (*S).ch[i];
		for (i = 0; i<T.length; i++)
			(*S).ch[pos - 1 + i] = T.ch[i]; /* ����T */
		(*S).length += T.length;
	}
	return OK;
}

Status StrDelete(HString *S, int pos, int len)
{ /* �Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ� */
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
{ /* ��ʼ����: ��S,T��V����,T�Ƿǿմ����˺����봮�Ĵ洢�ṹ�޹أ� */
  /* �������: ��V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ� */
	int i = 1; /* �Ӵ�S�ĵ�һ���ַ�����Ҵ�T */
	if (StrEmpty(T)) /* T�ǿմ� */
		return ERROR;
	do
	{
		i = Index(*S, T, i); /* ���iΪ����һ��i֮���ҵ����Ӵ�T��λ�� */
		if (i) /* ��S�д��ڴ�T */
		{
			StrDelete(S, i, StrLength(T)); /* ɾ���ô�T */
			StrInsert(S, i, V); /* ��ԭ��T��λ�ò��봮V */
			i += StrLength(V); /* �ڲ���Ĵ�V����������Ҵ�T */
		}
	} while (i);
	return OK;
}

void DestroyString()
{ /* �ѷ������͵��ַ����޷����� */
}

void StrPrint(HString T)
{ /* ���T�ַ�������� */
	int i;
	for (i = 0; i<T.length; i++)
		printf("%c", T.ch[i]);
	printf("\n");
}

//������
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

/* �����Ϊbno�Ĺؼ��ʲ��������� */
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
	FILE *f; /* �κ�ʱ������һ���ļ� */
	IdxListType idxlist; /* ������ */
	int BookNo; /* ��ű��� */
	int k, l;
	f = fopen("NoIdx.txt", "r"); /* �򿪳��ô��ļ� */
	if (!f)
		exit(OVERFLOW);
	fscanf(f, "%d", &noidx.last); /* ���ôʸ��� */
	for (k = 0; k<noidx.last; k++) /* �ѳ��ô��ļ������ݿ���noidx�� */
	{
		fscanf(f, "%s", buf);
		l = strlen(buf);
		noidx.item[k] = (char*)malloc(l * sizeof(char));
		strcpy(noidx.item[k], buf);
	}
	fclose(f);
	f = fopen("BookInfo.txt", "r"); /* ����Ŀ�ļ� */
	if (!f)
		exit(FALSE);
	InitIdxList(&idxlist); /* ��ʼ��������idxlistΪ�� */
	wdlist.last = 0; /* �ʱ��ȳ�ֵΪ0 */
	while (!feof(f))
	{
		fgets(buf, MaxLineLen, f);
		l = strlen(buf);
		if (l <= 1)
			break;
		ExtractKeyWord(&BookNo); /* ��buf����ȡ�ؼ��ʵ��ʱ���Ŵ���BookNo */
		InsIdxList(&idxlist, BookNo);
	}
	fclose(f);
	f = fopen("BookIdx.txt", "w");
	if (!f)
		exit(INFEASIBLE);
	PutText(f, idxlist); /* �����ɵ�������idxlist������ļ�f */
	fclose(f);
	system("pause");
}