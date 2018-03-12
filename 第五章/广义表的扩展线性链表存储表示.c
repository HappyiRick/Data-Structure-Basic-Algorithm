//广义表的扩展线性链表存储表示
typedef enum{ATOM,LIST}ElemTag;
typedef struct GLNode{
	ElemTag tag;
	union{
		AtomType atom;
		struct GLNode *hp;
	}a;
	struct GLNode *tp;
}*GList, GLNode;
 /* c4-2.h 串的堆分配存储 */
 typedef struct
 {
   char *ch; /* 若是非空串,则按串长分配存储区,否则ch为NULL */
   int length; /* 串长度 */
 }HString;
 /* bo4-2.c 串采用堆分配存储结构(由c4-2.h定义)的基本操作(15个) */
 /* 包括算法4.1、4.4 */
 Status StrAssign(HString *T,char *chars)
 { /* 生成一个其值等于串常量chars的串T */
   int i,j;
   if((*T).ch)
     free((*T).ch); /* 释放T原有空间 */
   i=strlen(chars); /* 求chars的长度i */
   if(!i)
   { /* chars的长度为0 */
     (*T).ch=NULL;
     (*T).length=0;
   }
   else
   { /* chars的长度不为0 */
     (*T).ch=(char*)malloc(i*sizeof(char)); /* 分配串空间 */
     if(!(*T).ch) /* 分配串空间失败 */
       exit(OVERFLOW);
     for(j=0;j<i;j++) /* 拷贝串 */
       (*T).ch[j]=chars[j];
     (*T).length=i;
   }
   return OK;
 }

 Status StrCopy(HString *T,HString S)
 { /* 初始条件:串S存在。操作结果: 由串S复制得串T */
   int i;
   if((*T).ch)
     free((*T).ch); /* 释放T原有空间 */
   (*T).ch=(char*)malloc(S.length*sizeof(char)); /* 分配串空间 */
   if(!(*T).ch) /* 分配串空间失败 */
     exit(OVERFLOW);
   for(i=0;i<S.length;i++) /* 拷贝串 */
     (*T).ch[i]=S.ch[i];
   (*T).length=S.length;
   return OK;
 }

 Status StrEmpty(HString S)
 { /* 初始条件: 串S存在。操作结果: 若S为空串,则返回TRUE,否则返回FALSE */
   if(S.length==0&&S.ch==NULL)
     return TRUE;
   else
     return FALSE;
 }

 int StrCompare(HString S,HString T)
 { /* 若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0 */
   int i;
   for(i=0;i<S.length&&i<T.length;++i)
     if(S.ch[i]!=T.ch[i])
       return S.ch[i]-T.ch[i];
   return S.length-T.length;
 }

 int StrLength(HString S)
 { /* 返回S的元素个数,称为串的长度 */
   return S.length;
 }

 Status ClearString(HString *S)
 { /* 将S清为空串 */
   if((*S).ch)
   {
     free((*S).ch);
     (*S).ch=NULL;
   }
   (*S).length=0;
   return OK;
 }

 Status Concat(HString *T,HString S1,HString S2)
 { /* 用T返回由S1和S2联接而成的新串 */
   int i;
   if((*T).ch)
     free((*T).ch); /* 释放旧空间 */
   (*T).length=S1.length+S2.length;
   (*T).ch=(char *)malloc((*T).length*sizeof(char));
   if(!(*T).ch)
     exit(OVERFLOW);
   for(i=0;i<S1.length;i++)
     (*T).ch[i]=S1.ch[i];
   for(i=0;i<S2.length;i++)
     (*T).ch[S1.length+i]=S2.ch[i];
   return OK;
 }

 Status SubString(HString *Sub, HString S,int pos,int len)
 { /* 用Sub返回串S的第pos个字符起长度为len的子串。 */
   /* 其中,1≤pos≤StrLength(S)且0≤len≤StrLength(S)-pos+1 */
   int i;
   if(pos<1||pos>S.length||len<0||len>S.length-pos+1)
     return ERROR;
   if((*Sub).ch)
     free((*Sub).ch); /* 释放旧空间 */
   if(!len) /* 空子串 */
   {
     (*Sub).ch=NULL;
     (*Sub).length=0;
   }
   else
   { /* 完整子串 */
     (*Sub).ch=(char*)malloc(len*sizeof(char));
     if(!(*Sub).ch)
       exit(OVERFLOW);
     for(i=0;i<=len-1;i++)
       (*Sub).ch[i]=S.ch[pos-1+i];
     (*Sub).length=len;
   }
   return OK;
 }

 void InitString(HString *T)
 { /* 初始化(产生空串)字符串T。另加 */
   (*T).length=0;
   (*T).ch=NULL;
 }

 int Index(HString S,HString T,int pos) /* 算法4.1 */
 { /* T为非空串。若主串S中第pos个字符之后存在与T相等的子串, */
   /* 则返回第一个这样的子串在S中的位置,否则返回0 */
   int n,m,i;
   HString sub;
   InitString(&sub);
   if(pos>0)
   {
     n=StrLength(S);
     m=StrLength(T);
     i=pos;
     while(i<=n-m+1)
     {
       SubString(&sub,S,i,m);
       if(StrCompare(sub,T)!=0)
	 ++i;
       else
	 return i;
     }
   }
   return 0;
  }

 Status StrInsert(HString *S,int pos,HString T) /* 算法4.4 */
 { /* 1≤pos≤StrLength(S)+1。在串S的第pos个字符之前插入串T */
   int i;
   if(pos<1||pos>(*S).length+1) /* pos不合法 */
     return ERROR;
   if(T.length) /* T非空,则重新分配空间,插入T */
   {
     (*S).ch=(char*)realloc((*S).ch,((*S).length+T.length)*sizeof(char));
     if(!(*S).ch)
       exit(OVERFLOW);
     for(i=(*S).length-1;i>=pos-1;--i) /* 为插入T而腾出位置 */
       (*S).ch[i+T.length]=(*S).ch[i];
     for(i=0;i<T.length;i++)
       (*S).ch[pos-1+i]=T.ch[i]; /* 插入T */
     (*S).length+=T.length;
   }
   return OK;
 }

 Status StrDelete(HString *S,int pos,int len)
 { /* 从串S中删除第pos个字符起长度为len的子串 */
   int i;
   if((*S).length<pos+len-1)
     exit(ERROR);
   for(i=pos-1;i<=(*S).length-len;i++)
     (*S).ch[i]=(*S).ch[i+len];
   (*S).length-=len;
   (*S).ch=(char*)realloc((*S).ch,(*S).length*sizeof(char));
   return OK;
 }

 Status Replace(HString *S,HString T,HString V)
 { /* 初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关） */
   /* 操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串 */
   int i=1; /* 从串S的第一个字符起查找串T */
   if(StrEmpty(T)) /* T是空串 */
     return ERROR;
   do
   {
     i=Index(*S,T,i); /* 结果i为从上一个i之后找到的子串T的位置 */
     if(i) /* 串S中存在串T */
     {
       StrDelete(S,i,StrLength(T)); /* 删除该串T */
       StrInsert(S,i,V); /* 在原串T的位置插入串V */
       i+=StrLength(V); /* 在插入的串V后面继续查找串T */
     }
   }while(i);
   return OK;
 }

 void DestroyString()
 { /* 堆分配类型的字符串无法销毁 */
 }

 void StrPrint(HString T)
 { /* 输出T字符串。另加 */
   int i;
   for(i=0;i<T.length;i++)
     printf("%c",T.ch[i]);
   printf("\n");
 }

//广义表的扩展线性链表存储的基本操作
Status InitGList(GList *L){
	*L = NULL;
	return OK;
}

Status sever(HString *str, HString *hstr){
	int n, i=1, k=0;
	HString ch, c1, c2, c3;
	InitString(&ch);
	InitString(&c1);
	InitString(&c2);
	InitString(&c3);
	StrAssign(&c1, ",");
	StrAssign(&c2, "(");
	StrAssign(&c3, ")");
	n = StrLength(*str);
	do{
		SubString(&ch,*str,i,1);
		if (!StrCompare(ch,c2))
		{
			++k;
		}else if (!StrCompare(ch,c3))
		{
			--k;
		}
		++i;
	}while(i<=n&&StrCompare(ch,c1)||k!=0);
	if (i<=n)
	{
		StrCopy(hstr, *str);
		ClearString(str);
	}
	return OK;
}

Status CreateGList(GList *L, HString S){
	HString emp, sub, hsub;
	GList p;
	InitString(&emp);
	InitString(&sub);
	InitString(&hsub);
	StrAssign(&emp,"()");
	*L = (GList)malloc(sizeof(GLNode));
	if (!*L)
	{
		exit(OVERFLOW);
	}
	if (!StrCompare(S,emp))
	{
		(*L)->tag = LIST;
		(*L)->a.hp = NULL;
		(*L)->tp = NULL;
	}else if(StrLength(S)==1){
		(*L)->tag = ATOM;
		(*L)->a.atom = S.ch[0];
		(*L)->tp = NULL;
	}else{
		(*L)->tag = LIST;
		(*L)->tp = NULL;
		SubString(&sub,S,2,StrLength(S)-2);
		sever(&sub, &hsub);
		CreateGList(&(*L)->a.hp,husb);
		p = (*L)->a.hp;
		while(!StrEmpty(sub)){
			sever(&sub,&hsub);
			CreateGList(&p->tp,hsub);
			p = p->tp;
		}
	}
	return OK;
}

void DestroyGList(GList *L){
	GList ph,pt;
	if (*L)
	{
		if ((*L)->tag)
		{
			ph = (*L)->a.hp;
		}else{
			ph = NULL;
		}
	}
	pt = (*L)->tp;
	free(*L);
	*L = NULL;
	DestroyGList(&ph);
	DestroyGList(&pt);
}

Status CopyGList(GList *T,GList L){
	if(!L){
		*T = NULL;
		return OK;
	}
	*T = (GList)malloc(sizeof(GLNode));
	if (!*T)
	{
		exit(OVERFLOW);
	}
	(*T)->tag = L->tag;
	if (L->tag == ATOM)
	{
		(*T)->a.atom = L->a.atom;
	}else{
		CopyGList(&(*T)->a.hp,L->a.hp);
	}
	if (L->tp == NULL)
	{
		(*T)->tp = L->tp;
	}else{
		CopyGList(&(*T)->tp,L->tp);
	}
	return OK;
}

int GListLength(GList L){
	int len = 0;
	GList p;
	if (L->tag == LIST && !L->a.hp)
	{
		return 0;
	}else if (L->tag == ATOM)
	{
		return 1;
	}else{
		p = L->a.hp;
		do{
			len++;
			p = p->tp;
		}while(p);
		return len;
	}
}

int GListDepth(GList L){
	int max, dep;
	GList pp;
	if (L == NULL || L->tag == LIST && !L->a.hp)
	{
		return 1;
	}else if (L->tag == ATOM)
	{
		return 0;
	}else{
		for (max = 0, pp = L->a.hp; pp; pp=pp->tp)
		{
			dep = GListDepth(pp);
			if (dep>max)
			{
				max = dep;
			}
		}
	}
	return max+1;
}

Status GListEmpty(GList L){
	if (!L||L->tag == LIST && !L->a.hp)
	{
		return OK;
	}else{
		return ERROR;
	}
}

GList GetHead(GList L){
	GList h;
	InitGList(&h);
	if (!L||L->tag==LIST&&!L->a.hp)
	{
		printf("\n空表无表头");
		exit(0);
	}
	h = (GList)malloc(sizeof(GLNode));
	if (!h)
	{
		exit(OVERFLOW);
	}
	h->tag = L->a.hp->tag;
	h->tp = NULL;
	if (h->tag == ATOM)
	{
		h->a.atom = L->a.hp->a.atom;
	}else{
		CopyGList(&h->a.hp,L->a.hp->a.hp);
	}
	return h;
}

GList GetTail(GList L){
	GList T;
	if (!L)
	{
		printf("\n空表无表尾");
		exit(0);
	}
	T = (GList)malloc(sizeof(GLNode));
	if (!T)
	{
		exit(OVERFLOW);
	}
	T->tag == LIST;
	t->tp  = NULL;
	CopyGList(&T->a.hp,L->a.hp->tp);
	return T;
}

Status InsertFirst_GL(GList *L,GList e){
	GList p = (*L)->a.hp;
	(*L)->a.hp = e;
	e->tp = p;
	return OK;
}

Status DeleteFirst_GL(GList *L,GList *e){
	if (*L)
	{
		*e = (*L)->a.hp;
		(*L)->a.hp = (*e).tp;
		(*e)->tp = NULL;
	}else{
		*e = *L;
	}
	return OK;
}

void Traverse_GL(GList L, void (*v)(AtomType)){
	GList hp;
	if (L)
	{
		if (L->tag == ATOM)
		{
			v(L->a.atom);
			hp = NULL;
		}else{
			hp = L->a.hp;
		}
		Traverse_GL(hp,v);
		Traverse_GL(L->tp,v);
	}
}
