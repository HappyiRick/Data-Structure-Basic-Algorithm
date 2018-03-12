//广义表的头尾链表存储表示
typedef enum{ATOM,LIST}ElemTag;
typedef struct GLNode{
	ElemTag tag;
	union{
		AtomType atom;
		struct{
			struct GLNode *hp, *tp;
		}ptr;
	}a;
}*GList, GLNode;

//广义表的头尾链表存储的基本操作
Status InitGList(GList *L){
	*L = NULL;
	return OK;
}

void DestroyGList(GList *L){
	Glist q1, q2;
	if(*L){
		if((*L)->tag == ATOM){
			free(*L);
			*L = NULL;
		}else{
			q1 = (*L)->a.ptr.hp;
			q2 = (*L)->a.ptr.tp;
			free(*L);
			*L = NULL;
			DestroyGList(&q1);
			DestroyGList(&q2);
		}
	}
}

Status CopyGList(GList *T, GList L){
	if(!L){
		*T = NULL;
	}else{
		*T = (GList)malloc(sizeof(GLNode));
		if(!*T){
			exit(OVERFLOW);
		}
		(*T)->tag = L->tag;
		if(L->tag == ATOM){
			(*T)->a.atom = L->a.atom;
		}else{
			CopyGList(&((*T)->a.ptr.hp), L->a.ptr.hp);
			CopyGList(&((*T)->a.ptr.tp),L->a.ptr.tp);
		}
	}
	return OK;
}

int GListLength(GList L){
	int len = 0;
	if(!L){
		return 0;
	}
	if(L->tag == ATOM){
		return 1;
	}
	while(L){
		L = L->a.ptr.tp;
		len++;
	}
	return len;
}

int GListDepth(GList L){
	int max, dep;
	GList pp;
	if (!L)
	{
		return 1;
	}
	if(L->tag == ATOM){
		return 0;
	}
	for (max = 0, pp = L; pp; pp = pp->a.ptr.tp)
	{
		dep = GListDepth(pp->a.ptr.hp);//以求pp->a.ptr头指针的子表深度
		if (dep > max)
		{
			max = dep;
		}
	}
	return max+1; //非空表的深度是个元素的深度的最大值+1
}


Status GListEmpty(GList L){
	if (!L)
	{
		return TRUE;
	}else{
		return FALSE;
	}
}

GList GetHead(GList L){
	GList h,p;
	if (!L)
	{
		printf("空表无表头\n");
		exit(0);
	}
	p = L->a.ptr.tp;
	L->a.ptr.tp = NULL;
	CopyGList(&h,L);
	L->a.ptr.tp = p;
	return h;
}

GList GetTail(GList L){
	GList t;
	if (!L)
	{
		printf("空表无表尾\n", );
		exit(0);
	}
	CopyGList(&t,L->a.ptr.tp);
	return t;
}

Status InsertFirst_GL(GList *L, GList e){
	GList p = (GList)malloc(sizeof(GLNode));
	if (!p)
	{
		exit(OVERFLOW);
	}
	p->tag = LIST;
	p->a.ptr.hp = e;
	p->a.ptr.tp = *L;
	*L = p;
	return OK;
}

Status DeleteFirst_GL(GList *L, GList *e){
	GList p;
	*e = (*L)->a.ptr.hp;
	p = *L;
	*L = (*L)->a.ptr.tp;
	free(p);
	retrun OK;
}

void Traverse_GL(GList L, void(*V)(AtomType)){
	if (L)
	{
		if (L->tag == ATOM)
		{
			v(L->a.atom);
		}else{
			Traverse_GL(L->a.ptr.hp, v);
			Traverse_GL(L->a.ptr.tp, v);
		}
	}
}
