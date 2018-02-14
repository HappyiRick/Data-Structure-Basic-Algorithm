#include "predefine.h"

#define N 2
typedef char ElemType;
/*���Ա�ľ�̬������洢�ṹ */
#define MAXSIZE 100 /* �������󳤶� */
typedef struct
{
	ElemType data;
	int cur;
}component, SLinkList[MAXSIZE];

/*ʵ���㷨2.15 2.16�ĳ���*/
int Malloc(SLinkList space) {
	/* ����������ǿ�,�򷵻ط���Ľ���±�(��������ĵ�һ�����),���򷵻�0 */
	int i = space[0].cur;
	if (i)//��������ǿ�
	{
		space[0].cur = space[i].cur;//���������ͷ���ָ��ԭ��������ĵڶ������
	}
	return i;/*�����¿��ٽ�������*/
 }

void Free(SLinkList space, int k) {
	/*���±�Ϊk�Ŀ��н����յ���������(��Ϊ��������ĵ�һ�����)*/
	space[k].cur = space[0].cur;/*���׽��ġ��αꡱָ��������ĵ�һ�����*/
	space[0].cur = k;/*���������ͷ���ָ���»��յĽ��*/
}

void DestroyList() {
	//��̬���鲻�ܱ�����
}

/*һ��������������ɾ�̬�����12����������*/
void InitSpace(SLinkList L) {
	/*��һά����L�и���������һ����������,L[0].curΪͷָ��.��0����ʾ��ָ��*/
	int i;
	for (i = 0; i < MAXSIZE-1; i++)
	{
		L[i].cur = i + 1;
	}
	L[MAXSIZE - 1].cur = 0;
}

int InitList(SLinkList L) {
	/*����һ��������,����ֵΪ�ձ��������е�λ��*/
	int i;
	i = Malloc(L);/*����Malloc����,�򻯳���*/
	L[i].cur = 0;/*������ı�ͷָ��Ϊ��*/
	return i;
}

Status ClearList(SLinkList L,int n){
	/*��ʼ������L�б�ͷλ��Ϊn�ľ�̬�����Ѵ��ڣ�������������˱�����Ϊ�ձ�*/
	int j, k, i = L[n].cur;//�����һ������λ��
	L[n].cur = 0;//�����
	k = L[0].cur;//���������һ������λ��
	L[0].cur = i;//������Ľ��������������ı�ͷ
	while (i)/*û������β*/
	{
		j = i;
		i = L[i].cur;/*ָ����һ��Ԫ��*/
	}
	L[j].cur = k;
	return OK;
}

Status ListEmpty(SLinkList L,int n) {
	/*�ж�L�б�ͷλ��Ϊn�������Ƿ�գ����ǿձ���TRUE�����򷵻�FALSE*/
	if (L[n].cur == 0)//�ձ�
	{
		return TRUE;
	}
	return FALSE;
}

int ListLength(SLinkList L,int n) {
	/*����L�б�ͷλ��Ϊn�����������Ԫ�ظ���*/
	int j = 0, i = L[n].cur;/*iָ���һ��Ԫ��*/
	while (i)/*û����̬����β*/
	{
		i = L[i].cur;/*ָ����һ��Ԫ��*/
		j++;
	}
	return j;
}

Status GetElem(SLinkList L,int n, int i, ElemType *e) {
	/*��e����L�б�ͷλ��Ϊn������ĵ�i��Ԫ�ص�ֵ*/
	int l, k = n;/*kָ���ͷ���*/
	if (i<1||i>ListLength(L,n))/*iֵ������*/
	{
		return ERROR;
	}
	for ( l = 1; l <= i; l++)/*�ƶ�i-1��Ԫ��*/
	{
		k = L[k].cur;
	}
	*e = L[k].data;
	return OK;
}

int LocateElem(SLinkList L,int n,ElemType e) {
	/*��L�б�ͷλ��Ϊn�ľ�̬�������в��ҵ�1��ֵΪe��Ԫ�ء�*/
	/*���ҵ�,�򷵻�����L�е�λ�򣬷��򷵻�0*/
	int i = L[n].cur; /*iָʾ���е�һ�����*/
	while (i&&L[i].data!=e)//�ڱ���˳������
	{
		i = L[i].cur;
	}
	return i;
}

Status PriorElem(SLinkList L,int n,ElemType cur_e,ElemType *pre_e) {
	/*��ʼ��������L�б�ͷλ��Ϊn�ľ�̬�������Ѵ���*/
	/*�����������cur_e�Ǵ˵����������Ԫ�أ��Ҳ��ǵ�һ��
				����pre_e��������ǰ�����������ʧ�ܣ�pre_e�޶���
	*/
	int j, i = L[n].cur;
	do
	{//����ƶ����
		j = i;
		i = L[i].data;
	} while (i&&cur_e!=L[i].data);
	if (i)//�ҵ���Ԫ��
	{
		*pre_e = L[j].data;
		return OK;
	}
	return ERROR;
}

Status NextElem(SLinkList L,int n,ElemType cur_e,ElemType *next_e) {
	/*��ʼ��������L�б�ͷλ��Ϊn�ľ�̬�������Ѵ���*/
	/*�����������cur_e�Ǵ˵����������Ԫ�أ��Ҳ������һ��*/
	/*����next_e�������ĺ�̣��������ʧ�ܣ�next_e�޶���*/
	int i;
	i = LocateElem(L,n,cur_e);/*�������в��ҵ�һ��ֵΪcur_e��Ԫ�ص�λ��*/
	if (i)/* �ھ�̬�������д���Ԫ��cur_e */
	{
		i = L[i].cur; /* cur_e�ĺ�̵�λ�� */
		if (i)/* cur_e�к�� */
		{
			*next_e = L[i].data;
			return OK;/* cur_eԪ���к�� */
		}
	}
	return ERROR; /*L������cur_eԪ�أ�cur_eԪ���޺��*/
}

Status ListInsert(SLinkList L,int n,int i, ElemType e) {
	/*��L�б�ͷλ��Ϊn������ĵ�i��Ԫ��֮ǰ�����µ�����Ԫ��e*/
	int l, j, k = n;/* kָ���ͷ */
	if (i<1||i>ListLength(L,n)+1)
	{
		return ERROR;
	}
	j = Malloc(L);/* �����µ�Ԫ */
	if (j)/* ����ɹ� */
	{
		L[j].data = e;/* ��ֵ���µ�Ԫ */
		for (l = 1; l < i; l++)/* �ƶ�i-1��Ԫ�� */
		{
			k = L[k].cur;
		}
		L[j].cur = L[k].cur;
		L[k].cur = j;
		return OK;
	}
	return ERROR;
}

Status ListDelete(SLinkList L,int n,int i,ElemType *e) {
	//ɾ����L�б�ͷλ��Ϊn������ĵ�i������Ԫ��e,��������ֵ
	int j, k = n;//kָ���ͷ
	if (i<1||i>ListLength(L,n))
	{
		return ERROR;
	}
	for ( j = 01; j < i; j++)//�ƶ�i-1��Ԫ��
	{
		k = L[k].cur;
	}
	j = L[k].cur;
	L[k].cur = L[j].cur;
	*e = L[j].data;
	Free(L,j);
	return OK;
}

Status ListTraverse(SLinkList L,int n,void (*vi)(ElemType)) {
	/*���ζ�L�б�ͷλ��Ϊn�������ÿ������Ԫ�أ����ú���vi()��һ��vi()ʧ�ܣ������ʧ��*/
	int i = L[n].cur;/*ָ���һ��Ԫ��*/
	while (i)/*û����̬����β*/
	{
		vi(L[i].data);//����vi
		i = L[i].cur;//ָ����һ��Ԫ��
	}
	printf("\n");
	return OK;
}

/*�Ľ��㷨2.17���������û�������ʵ�֣�*/
//�������õ���visit �뽫visit����differenceǰ
void  visit(ElemType c) {
	printf("%c", c);
}


int difference(SLinkList space) {
	
	/*�������뼯��A��B��Ԫ�أ���һ������space�н�����ʾ����(A-B)��(B-A)
	  �ľ�̬������������ͷָ�룬���豸�ÿռ��㹻��space[0].curΪ���ÿռ��ͷָ��*/
	int m, n, i, j, k, S;
	ElemType b, c;
	InitSpace(space); /* ��ʼ�����ÿռ� */
	S = InitList(space); /* ��������S��ͷ��� */
	printf("�����뼯��A��B��Ԫ�ظ���m,n:");
	scanf("%d,%d%*c", &m, &n); /* %*c�Ե��س��� */
	printf("�����뼯��A��Ԫ�أ���%d����:", m);
	for (j = 1; j <= m; j++) /* ��������A������ */
	{
		scanf("%c", &b); /* ����A��Ԫ��ֵ */
		ListInsert(space, S, j, b); /* ���뵽��β */
	}
	scanf("%*c"); /* �Ե��س��� */
	printf("�����뼯��B��Ԫ�أ���%d����:", n);
	for (j = 1; j <= n; j++)
	{ /* ��������B��Ԫ��,�����ڵ�ǰ����,�����,����ɾ�� */
		scanf("%c", &b);
		k = LocateElem(space, S, b); /* kΪb��λ�� */
		if (k) /* b�ڵ�ǰ���� */
		{
			PriorElem(space, S, b, &c); /* b��ǰ��Ϊc */
			i = LocateElem(space, S, c); /* iΪc��λ�� */
			space[i].cur = space[k].cur; /* ��k��ָ�븳��i��ָ�� */
			Free(space, k); /* ���±�Ϊk�Ŀ��н����յ��������� */
		}
		else
			ListInsert(space, S, ListLength(space, S) + 1, b); /* �ڱ�β����b */
	}
	return S;
}


void main() {
	int k;
	SLinkList s;
	k = difference(s);
	ListTraverse(s,k,visit);
	system("pause");
}