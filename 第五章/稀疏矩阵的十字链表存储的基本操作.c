 /* c5-4.h 稀疏矩阵的十字链表存储表示 */
typedef struct OLNode
{
	int i, j;
	ElemType e;
	struct OLNode *right, *down;
}OLNode, *OLink;

typedef struct 
{
	OLink *rhead, *chead;
	int mu, nu, tu;
}CrossList;

// 稀疏矩阵的十字链表存储的基本操作（9个）
Status InitSMatrix(CrossList *M){
	(*M).rhead = (*M).chead = NULL;
	(*M).mu = (*M).nu = (*M).tu = 0;
	return OK;
}

Status DestroySMatrix(CrossList *M){
	int i;
	OLNode *p, *q;
	for (int i = 0; i <= (*M).mu; ++i)
	{
		p = *((*M).rhead + i);
		while(p){
			q = p;
			p = p->right;
			free(q);
		}
	}
	free((*M).rhead);
	free((*M).chead);
	(*M).rhead = (*M).chead = NULL;
	(*M).mu = (*M).nu = (*M).tu = 0;
	return OK;
}


Status CreateSMatrix(CrossList *M){
	int i,j,k,m,n,t;
	ElemType e;
	OLNode *p, *q;
	if ((*M).rhead)
	{
		DestroySMatrix(M);哦O
	}
	printf("请输入稀疏矩阵的行数 列数 非零元个数:");
	scanf("%d%d%d",&m,&n,&t);
	(*M).mu = m;
	(*M).nu = n;
	(*M).tu = t;
	(*M).rhead = (OLink *)malloc((m+1)*sizeof(OLink));
	if (!(*M).rhead)
	{
		exit(OVERFLOW);
	}
	(*M).chead = (OLink *)malloc((n+1)*sizeof(OLink));
	if (!(*M).chead)
	{
		exit(OVERFLOW);
	}
	for (k = 1; i <= m; k++)
	{
		(*M).rhead[k] = NULL;
	}
	for (k = 1; k <= n; k++)
	{
		(*M).chead[k] = NULL; 
	}
	printf("请按任意次序输入%d个非零元的行 列 元素值\n", (*M).tu);
	for (k = 0; i < t; k++)
	{
		scanf("%d%d%d",&i,&j,&e);
		p = (OLNode *)malloc(sizeof(OLNode));
		if (!p)
		{
			exit(OVERFLOW);
		}
		p -> i = i;
		p -> j = j;
		p -> e = e;
		if ((*M).rhead[i] == NULL || (*M).rhead[i]->j > j)
		{
			p -> right = (*M).rhead[i];
			(*M).rhead[i] = p;
		}else{
			for (q = (*M).rhead[i]; q->right && q->right->j < j; q=q->right);
			p->right = q->right;
			q->right = p;
		}
		if ((*M).chead[j] == NULL || (*M).chead[j] ->i > i)
		{
			p->down = (*M).chead[j];
			(*M).chead[j] = p;
		}else{
			for (q = (*M).chead[j]; q->down && q->down->i < i; q = q->down);
			p->down = q->down;
			q->down = p;
		}
	}
	return OK;
} 

Status PrintSMatrix(CrossList M){
	int i,j;
	OLink p;
	printf("%d行%d列%d个非零元素", M.mu, M.nu, M.tu);
	printf("请输入选择(1.按行输出 2.按列输出)：");
	scanf("%d",&i);
	switch(i){
		case 1:
		for (j = 1; j <= M.mu; j++)
		{
			p = M.rhead[j];
			while(p){
				printf("%d行%d列值为%d\n", p->i, p->j, p->e);
				p = p->right;
			}
		}
		break;
		case 2:
		for ( j = 1; j <= M.nu; j++)
		{
			p = M.chead[j];
			while(p){
				printf("%d行%d列值为%d\n", p->i, p->j, p->e);
				p = p->down;
			}
		}
	}
	return OK;
}

