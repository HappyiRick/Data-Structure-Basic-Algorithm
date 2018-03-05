#include "predefine.h"

typedef int ElemType;
#define MAXSIZE 100
/* ϡ��������Ԫ��˳���洢��ʾ */
typedef struct {
	int i, j;/* ���±�,���±� */
	ElemType e; /* ����Ԫ��ֵ */
}Triple;
typedef struct {
	Triple data[MAXSIZE+1]; /* ����Ԫ��Ԫ���,data[0]δ�� */
	int mu, nu, tu;/* ����������������ͷ���Ԫ���� */
}TSMatrix;

/* ��Ԫ��ϡ�����Ļ�������,�����㷨5.1 */
Status CreateMatrix(TSMatrix *M) {
	int i, m, n;
	ElemType e;
	Status k;
	printf("��������������,����,����Ԫ������");
	scanf("%d,%d,%d",&(*M).mu,&(*M).nu,&(*M).tu);
	(*M).data[0].i = 0;
	for ( i = 1; i <= (*M).tu; i++)
	{
		do
		{
			printf("�밴����˳�������%d������Ԫ�����ڵ���(1-%d),��(1-%d),Ԫ��ֵ��",i,(*M).mu,(*M).nu);
			scanf("%d,%d,%d",&m,&n,&e);
			k = 0;
			if (m<1||m>(*M).mu||n<1||n>(*M).nu)
			{
				k = 1;
			}
			if (m<(*M).data[i-1].i||m==(*M).data[i-1].i&&n<=(*M).data[i-1].j)
			{
				k = 1;
			}
		} while (k);
		(*M).data[i].i = m;
		(*M).data[i].j = n;
		(*M).data[i].e = e;
	}
	return OK;
}

void DestroySMatrix(TSMatrix *M) {
	(*M).mu = 0;
	(*M).nu = 0;
	(*M).tu = 0;
}

void PrintSMatrix(TSMatrix M) {
	int i;
	printf("%d��%d��%d������Ԫ�ء�\n",M.mu,M.nu,M.tu);
	printf("��  ��  Ԫ��ֵ\n");
	for ( i = 1; i <= M.tu; i++)
	{
		printf("%2d%4d%8d\n",M.data[i].i,M.data[i].j,M.data[i].e);
	}
}

Status CopySMatrix(TSMatrix M,TSMatrix *T) {
	(*T) = M;
	return OK;
}

int comp(int c1,int c2) {
	int i;
	if (c1<c2)
	{
		i = 1;
	}
	else if (c1 == c2)
	{
		i = 0;
	}
	else {
		i = -1;
	}
	return i;
}

Status AddSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q) {
	Triple *Mp, *Me, *Np, *Ne, *Qh, *Qe;
	if (M.mu != N.mu)
	{
		return ERROR;
	}
	if (M.nu != N.nu)
	{
		return ERROR;
	}
	(*Q).mu = M.mu;
	(*Q).nu = M.nu;
	Mp = &M.data[1];
	Np = &N.data[1];
	Me = &M.data[M.tu];
	Ne = &N.data[N.tu];
	Qh = Qe = (*Q).data;
	while (Mp <= Me &&Np <= Ne) {
		Qe++;
		switch (comp(Mp->i,Np->i))
		{
		case 1:
			*Qe = *Mp;
			Mp++;
			break;
		case 0:
			switch (comp(Mp->j, Np->j)) /* M��N����ǰ����Ԫ�ص������,�����Ƚ��� */
			{
			case  1: *Qe = *Mp;
				Mp++;
				break;
			case  0: *Qe = *Mp;
				Qe->e += Np->e;
				if (!Qe->e) /* Ԫ��ֵΪ0��������ѹ������ */
					Qe--;
				Mp++;
				Np++;
				break;
			case -1: *Qe = *Np;
				Np++;
			}
			break;
		case -1:
			*Qe = *Np;
			Np++;
			break;
		}
	}
	if (Mp > Me)
	{
		while (Np <= Ne)
		{		
			Qe++;
			*Qe = *Np;
			Np++;
		}
	}
	if (Np>Ne)
	{
		while(Mp<=Me){
			Qe++;
			*Qe = *Mp;
			Mp++;
		}
	}
	(*Q).tu = Qe - Qh;
	return OK;
}

Status SubtSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q) {
	int i;
	for ( i = 1; i <= N.tu; i++)
	{
		N.data[i].e *= -1;
	}
	AddSMatrix(M,N,Q);
	return OK;
}

Status MultSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q) {
	int i, j, h = M.mu, l = N.nu, Qn = 0;
	ElemType *Qe;
	if (M.nu != N.mu)
	{
		return ERROR;
	}
	(*Q).mu = M.mu;
	(*Q).nu = N.nu;
	Qe = (ElemType *)malloc(h*l*sizeof(ElemType));
	for ( i = 0; i < h*l; i++)
	{
		*(Qe + i) = 0;
	}
	for ( i = 1; i <= M.tu; i++)
	{
		for ( j = 0; j <= N.tu; j++)
		{
			if (M.data[i].j == N.data[j].i)
			{
				*(Qe + (M.data[i].i - 1)*l + N.data[j].j - 1) += M.data[i].e*N.data[j].e;
			}
		}
	}
	for ( i = 1; i <= M.mu; i++)
	{
		for ( j = 1; j <= N.nu; j++)
		{
			if (*(Qe+(i-1)*l+j-1)!=0)
			{
				Qn++;
				(*Q).data[Qn].e = *(Qe + (i - 1)*l + j - 1);
				(*Q).data[Qn].i = i;
				(*Q).data[Qn].j = j;
			}
		}
	}
	free(Qe);
	(*Q).tu = Qn;
	return OK;
}

Status TransposeSMatrix(TSMatrix M,TSMatrix *T) {
	int p, q, col;
	(*T).mu = M.nu;
	(*T).nu = M.mu;
	(*T).tu = M.tu;
	if ((*T).tu)
	{
		q = 1;
		for ( col = 1; col <= M.nu; col++)
		{
			for ( p = 1; p <= M.tu ; p++)
			{
				if (M.data[p].j == col)
				{
					(*T).data[q].i = M.data[p].j;
					(*T).data[q].j = M.data[p].i;
					(*T).data[q].e = M.data[p].e;
					++q;
				}
			}
		}
	}
	return OK;
}

//������ת�þ���
Status FastTransposeSMatrix(TSMatrix M,TSMatrix *T){
	int p, q, t, col, *num, *cpot;
	num = (int *)malloc((M.nu+1)*sizeof(int));
	cpot = (int *)malloc((M.nu + 1) * sizeof(int));
	(*T).mu = M.nu;
	(*T).nu = M.mu;
	(*T).tu = M.tu;
	if ((*T).tu)
	{
		for ( col = 1; col <= M.nu; col++)
		{
			num[col] = 0;
		}
		for ( t = 1; t <= M.tu; t++)
		{
			++num[M.data[t].j];
		}
		cpot[1] = 1;
		for ( col = 2; col <= M.nu; col++)
		{
			cpot[col] = cpot[col-1]+num[col-1];
		}
		for (p = 0; p <= M.tu ; p++)
		{
			col = M.data[p].j;
			q = cpot[col];
			(*T).data[q].i = M.data[p].j;
			(*T).data[q].j = M.data[p].i;
			(*T).data[q].e = M.data[p].e;
			++cpot[col];
		}
	}
	free(num);
	free(cpot);
	return OK;
}

void main() {
	TSMatrix A, B;
	printf("��������A��");
	CreateMatrix(&A);
	PrintSMatrix(A);
	FastTransposeSMatrix(A,&B);
	printf("����B��A�Ŀ���ת�ã�");
	PrintSMatrix(B);
	DestroySMatrix(&A);
	DestroySMatrix(&B);

}