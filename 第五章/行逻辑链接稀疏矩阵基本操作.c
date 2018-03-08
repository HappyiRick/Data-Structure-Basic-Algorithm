/* 5-3 稀疏矩阵的三元组行逻辑链接的顺序表存储表示 */
#define MAXSIZE 100 //非零元个数的最大值
#define MAXRC 20 //最大行列数
typedef ElemType int;
typedef struct{
	int i,j;/*行下标，列下标*/
	ElemType e;/*非零元素值*/
}Triple;

typedef struct{
	Triple data[MAXSIZE+1];/* 非零元三元组表，data[0]未用 */ 
	int rpos[MAXRC+1];/* 各行第一个非零元素的位置表，比5-2增加的项 */
	int mu,nu,tu;/* 矩阵的行数，列数和非零元个数 */
}RLSMatrix;

/* 行逻辑链接稀疏矩阵的基本操作8个 */
Status CreateSMatrix(RLSMatrix *M){
	int i;
	Triple T;
	Status k;
	printf("请输入矩阵的行数，列数，非零元素数：");
	scanf("%d,%d,%d",&(*M).mu,&(*M).nu,&(*M).tu);
	(*M).data[0].i = 0;
	for (i = 1; i <= (*M).tu; ++i)
	{
		do
		{
			printf("请按行序顺序输入第%d个非零元素所在的行(1~%d)，列(1~%d),元素值：",i,(*M).mu,(*M).nu);
			scanf("%d,%d,%d",&T.i,&T.j,&T.e);
			k = 0;
			if (T.i<1||T.i>(*M).mu||T.j<1||T.j>(*M).nu)
			{
				k = 1;
			}
			if (T.i<(*M).data[i-1].i||T.i == (*M).data[i-1].i&&T.j<=(*M).data[i-1].j)
			{
				k = 1;
			}
		} while (k);
		(*M).data[i] = T;
	}
	for (i = 1; i <= (*M).tu; ++i)
	{
		if ((*M).data[i].i>(*M).data[i-1].i)
		{
			for (T.i = 0; T.i < (*M).data[i].i-(*M).data[i-1].i; T.i++)
			{
				(*M).rpos[(*M).data[i]-T.i] = i;
			}
		}
	}
	for (i = (*M).data[(*M).tu].i+1; i <= (*M).mu; ++i)
	{
		(*M).rpos[i] = (*M).tu+1;/*给最后没有非零元素的几行赋值*/
	}
	return OK;
}

void DestroySMatrix(RLSMatrix *M){
	(*M).mu = 0;
	(*M).nu = 0;
	(*M).tu = 0;
}

void PrintSMatrix(RLSMatrix M){
	INT I;
	printf("%d行%d列%d个非零元素。\n",M.mu,M.nu,M.tu);
	printf("行 列 元素值\n");
	for (i = 1; i <= M.tu; i++)
	{
		printf("%2d%4d%8d\n",M.data[i].i,M.data[i].j,M.data[i].e);
	}
	for (i = 1; i <= M.mu; ++i)
	{
		printf("第%d行的第一个非零元素是本矩阵第%d个元素\n", i,M.rpos[i]);
	}
}

Status CopySMatrix(RLSMatrix M,RLSMatrix *T){
	*T = M;
	return OK; 
}

Status AddSMatrix(RLSMatrix M,RLSMatrix N, RLSMatrix *Q){
	int k,p,q;
	if (M.mu != N.mu || M.nu != N.nu)
	{
		reutn ERROR;
	}
	(*Q).mu = M.mu;
	(*Q).nu = M.nu;
	(*Q).tu = 0;
	M.rpos[M.mu+1] = M.tu + 1;
	N.rpos[N.mu+1] = N.tu + 1;
	for (k = 1; l <= M.mu; ++k)
	{
		(*Q).rpos[k] = (*Q).tu+1;
		p = M.rpos[k];
		q = N.rpos[k];	
		while(p<M.rpos[k+1]&&q<N.rpos[k+1]){
			if (M.data[p].j == N.data[p].j)
			{
				(*Q).data[(*Q).tu+1].e = M.data[p].e + N.data[q].e;
				if ((*Q).data[(*Q).tu+1].e != 0)
				{
					++(*Q).tu;
					(*Q).data[(*Q).tu].i = k;
					(*Q).data[(*Q).tu].j = M.data[p].j;
 				}
				++p;
				++q;
			}
			else if (M.data[p].j < N.data[q].j)
			{
				++(*Q).tu;
				(*Q).data[(*Q).tu].e = M.data[p].e;
				(*Q).data[(*Q).tu].i = k;
				(*Q).data[(*Q).tu].j = M.data[p].j;
				++p;
			}
			else
			{
				++(*Q).tu;
				(*Q).data[(*Q).tu].e = N.data[q].e;
				(*Q).data[(*Q).tu].i = k;
				(*Q).data[(*Q).tu].j = N.data[q].j;
				++q;
 			}
		}
		while (p < M.rpos[k+1])
		{
			++(*Q).tu;
			(*Q).data[(*Q).tu].e = M.data[p].e;
			(*Q).data[(*Q).tu].i = k;
			(*Q).data[(*Q).tu].j = M.data[p].j;
			++p;
		}
		while (q < N.rpos[k+1])
		{
			++(*Q).tu;
			(*Q).data[(*Q).tu].e = N.data[q].e;
			(*Q).data[(*Q).tu].i = k;
			(*Q).data[(*Q).tu].j = N.data[q].j;
			++q;
		}
		
	}
	return OK;
}

Status SubSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q) {
	int i;
	if (M.mu != N.mu || M.nu != N.nu)
	{
		return ERROR;
	}
	for ( i = 1; i <= N.tu; i++)
	{
		N.data[i].e *= -1;/* 对于N的每一元素,其值乘以-1 */
	}
	AddSMatrix(M, N, Q);/* Q=M+(-N) */
	return OK;
}

Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q) {
	int arow, brow, p, q, ccol, ctemp[MAXRC + 1];
	if (M.nu != N.mu)
	{
		return ERROR;
	}
	(*Q).mu = M.mu;
	(*Q).nu = N.nu;
	(*Q).tu = 0;
	M.rpos[M.mu + 1] = M.tu + 1;
	N.rpos[N.mu + 1] = N.tu + 1;
	if (M.tu*N.tu != 0)
	{
		for ( arow = 1; arow <= M.mu; arow++)
		{
			for ( ccol = 1; ccol <= (*Q).mu; ccol++)
			{
				ctemp[ccol] = 0;
			}
			(*Q).rpos[arow] = (*Q).tu + 1;
			for ( p = M.rpos[arow]; p < M.rpos[arow+1]; p++)
			{
				brow = M.data[p].j;
				for ( q = N.rpos[brow]; q < N.rpos[brow+1]; q++)
				{
					ccol = N.data[q].j;
					ctemp[ccol] += M.data[p].e * N.data[q].e;
				}
			}
			for (ccol = 1; ccol <= (*Q).nu; ccol++)
			{
				if (ctemp[ccol])
				{
					if (++(*Q).tu > MAXSIZE)
					{
						return ERROR;
					}
					(*Q).data[(*Q).tu].i = arow;
					(*Q).data[(*Q).tu].j = col;
					(*Q).data[(*Q).tu].e = ctemp[ccol];
				}
			}
		}
	}
	return OK;
}


Status TransposeSMatrix(RLSMatrix M, RLSMatrix *T)
{ /* 求稀疏矩阵M的转置矩阵T */
	int p, q, t, col, *num;
	num = (int *)malloc((M.nu + 1) * sizeof(int));
	(*T).mu = M.nu;
	(*T).nu = M.mu;
	(*T).tu = M.tu;
	if ((*T).tu)
	{
		for (col = 1; col <= M.nu; ++col)
			num[col] = 0;  /* 设初值 */
		for (t = 1; t <= M.tu; ++t) /* 求M中每一列非零元个数 */
			++num[M.data[t].j];
		(*T).rpos[1] = 1;
		for (col = 2; col <= M.nu; ++col) /* 求M中第col中第一个非零元在(*T).data中的序号 */
			(*T).rpos[col] = (*T).rpos[col - 1] + num[col - 1];
		for (col = 1; col <= M.nu; ++col)
			num[col] = (*T).rpos[col];
		for (p = 1; p <= M.tu; ++p)
		{
			col = M.data[p].j;
			q = num[col];
			(*T).data[q].i = M.data[p].j;
			(*T).data[q].j = M.data[p].i;
			(*T).data[q].e = M.data[p].e;
			++num[col];
		}
	}
	free(num);
	return OK;
}