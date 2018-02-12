#include "predefine.h"
#define _CRT_SECURE_NO_WARNINGS //ȥ��C4996����


#define NAMELEN 8
#define CLASSLEN 4
struct stud
{
	char name[NAMELEN+1];
	long num;
	char sex;
	int age;
	char Class[CLASSLEN+1];
	int health;
};
typedef struct stud ElemType;
struct LNode
{
	ElemType data;
	struct LNode *next;
};
typedef struct LNode *LinkList;

char sta[3][9] = {"����","һ��","��˥��"};
FILE *fp;

Status InitList(LinkList *L) {
	*L = (LinkList)malloc(sizeof(struct LNode));
	if (!*L)
	{
		exit(OVERFLOW);
	}
	(*L)->next = NULL;
	return OK;
}

Status ListTraverse(LinkList L,void (*vi)(ElemType)) {
	LinkList p = L->next;
	while (p)
	{
		vi(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

void InsertAscend(LinkList L,ElemType e) {
	LinkList q = L, p = L->next;
	while (p&&e.num> p->data.num)
	{
		q = p;
		p = p->next;
	}
	q->next = (LinkList)malloc(sizeof(struct LNode));
	q->next->data = e;
	q->next->next = p;
}

void Print(struct stud e) {
	printf("%-s %6ld",e.name,e.num);
	if (e.sex == 'm')
	{
		printf("��");
	}
	else {
		printf("Ů");
	}
	printf("%5d %-4s",e.age,e.Class);
	printf("%9s\n",sta[e.health]);
}

void ReadIn(struct stud *e) {
	printf("����������(<=%d���ַ�)",NAMELEN);
	scanf("%s", e->name);
	printf("������ѧ�ţ�");
	scanf("%ld",&e->name);
	printf("�������Ա�(m:�� f:Ů)");
	scanf("%*c%c",&e->sex);
	printf("����������:");
	scanf("%d",&e->age);
	printf("������༶(<=%d���ַ�)",CLASSLEN);
	scanf("%s",e->Class);
	printf("�����뽡��״��(0:%s 1:%s 2:%s)",sta[0],sta[1],sta[2]);
	scanf("%d",&e->health);
}

void WriteToFile(struct stud e) {
	fwrite(&e,sizeof(struct stud),1,fp);
}

Status ReadFromFile(struct stud *e) {
	int i;
	i = fread(e, sizeof(struct stud),1,fp);
	if (i == 1)
	{	
		return OK;
	}
	else {
		return ERROR;
	}
}

Status FindFromNum(LinkList L,long num,LinkList *p,LinkList *q) {
	*p = L;
	while (*p)
	{
		*q = (*p)->next;
		if (*q && (*q)->data.num >num)
		{
			break;
		}
		if (*q&&(*q)->data.num == num)
		{
			return TRUE;
		}
		*p = *q;
	}
	return FALSE;
}

Status FindFromName(LinkList L,char name[],LinkList *p,LinkList *q) {
	*p = L;
	while (*p)
	{
		*q = (*p)->next;
		if (*q&&!strcmp((*q)->data.name,name))
		{
			return TRUE;
		}
		*p = *q;
	}
	return FALSE;
}


Status DeleteElemNum(LinkList L,long num) {
	LinkList p, q;
	if (FindFromNum(L,num,&p,&q))
	{
		p->next = q->next;
		free(q);
		return TRUE;
	}
	return FALSE;
}

Status DeleteElemName(LinkList L,char name[]) {
	LinkList p, q;
	if (FindFromName(L,name,&p,&q))
	{
		p->next = q->next;
		free(q);
		return TRUE;
	}
	return FALSE;
}

void Modify(ElemType *e) {
	char s[80];
	Print(*e);
	printf("��������޸�������ݣ����޸ĵ���س�������ԭֵ��\n");
	printf("����������(<=%d���ַ�)��",NAMELEN);
	gets(s);
	if (strlen(s))
	{
		strcpy(e->name,s);
	}
	printf("������ѧ�ţ�");
	gets(s);
	if (strlen(s))
	{
		e->num = atol(s);
	}
	printf("�������Ա�(m:�� f:Ů)��");
	gets(s);
	if (strlen(s))
	{
		e->sex = s[0];
	}
	printf("������༶(<=%d���ַ�)��",CLASSLEN);
	gets(s);
	if (strlen(s))
	{
		strcpy(e->Class,s);
	}
	printf("�����뽡��״��(0��%s 1��%s 2��%s):",sta[0],sta[1],sta[2]);
	gets(s);
	if (strlen(s))
	{
		e->health = atoi(s);
	}
}

#define N 4 //student ��¼�ĸ���
void main() {
	struct stud student[N] = {
		{ "����",110011,'m',18,"��14",0 },
		{ "����",220011,'f',19,"��14",1 },
		{ "����",330011,'m',18,"��14",0 },
		{ "ɶ��",440011,'f',20,"��14",0 },
	};
	int i, j, flag = 1;
	long num;
	char filename[13], name[NAMELEN + 1];
	ElemType e;
	LinkList T, p, q;
	InitList(&T);
	while (flag)
	{
		printf("1:���ṹ������student�е����ݰ�ѧ�ŷǽ����������\n");
		printf("2:���ļ��еļ�¼��ѧ�ŷǽ����������\n");
		printf("3:���������¼�¼�������䰴ѧ�ŷǽ����������\n");
		printf("4:ɾ�������е�һ���и���ѧ�ŵļ�¼\n");
		printf("5:ɾ�������е�һ���и��������ļ�¼\n");
		printf("6:�޸������е�һ���и���ѧ�ŵļ�¼\n");
		printf("7:�޸������е�һ���и���ѧ�ŵļ�¼\n");
		printf("8:����������ܵ�һ���и���ѧ�ŵļ�¼\n");
		printf("9:����������ܵ�һ���и��������ļ�¼\n");
		printf("10:��ʾ���м�¼\n");
		printf("11:�������е����м�¼�����ļ�\n");
		printf("12:����\n");
		printf("��ѡ��������\n");
		scanf("%d",&i);
		switch (i)
		{
			case 1:
				for (j = 0; j < N; j++){
					InsertAscend(T,student[j]);
					}
				   break;
			case 2:
				printf("�������ļ�����");
				scanf("%s",filename);
				if ((fp=fopen(filename,"rb"))==NULL)
				{
					printf("���ļ�ʧ��!\n");
				}
				else {
					while (ReadFromFile(&e))
					{
						InsertAscend(T,e);
					}
					fclose(fp);
				}
				break;
			case 3:
				ReadIn(&e);
				InsertAscend(T,e);
				break;
			case 4:
				printf("�������ɾ����¼��ѧ�ţ�");
				scanf("%ld",&num);
				if (!DeleteElemNum(T,num))
				{
					printf("û��ѧ��Ϊ%ld�ļ�¼\n",num);
				}
				break;
			case 5:
				printf("�������ɾ����¼������:");
				scanf("%s",name);
				if (!DeleteElemName(T,name))
				{
					printf("û��ѧ��Ϊ%ld�ļ�¼\n",num);
				}
				break;
			case 6:
				printf("��������޸ļ�¼��ѧ�ţ�");
				scanf("%ld%*c",&num);//%*c�Ե��س���
				if (!FindFromNum(T,num,&p,&q))
				{
					printf("û�����Ϊ%ld�ļ�¼\n",num);
				}
				else {
					Modify(&q->data);
					if (q->data.num != num)
					{
						p->next = q->next;
						InsertAscend(T,q->data);
						free(q);
					}
				}
				break;
			case 7:
				printf("��������޸ļ�¼��������");
				scanf("%s%*c",name);
				if (!FindFromName(T,name,&p,&q))
				{
					printf("û������Ϊ%s�ļ�¼\n",name);
				}
				else {
					num = q->data.num;
					Modify(&q->data);
					if (q->data.num!=num)
					{
						p->next = q->next;
						InsertAscend(T,q->data);
						free(q);
					}
					break;
				}
			case 8:
				printf("����������Ҽ�¼��ѧ�ţ�");
				scanf("%ld",&num);
				if (!FindFromNum(T,num,&p,&q))
				{
					printf("û��ѧ��Ϊ%ld�ļ�¼\n",num);
				}
				else {
					Print(q->data);
				}
				break;
			case 9:
				printf("����������Ҽ�¼��������");
				scanf("%s",name);
				if (!FindFromName(T,name,&p,&q))
				{
					printf("û������Ϊ%s�ļ�¼\n",name);
				}
				else {
					Print(q->data);
				}
			case 10:
				printf("���� ѧ�� �Ա� ���� �༶ ����״��\n");
				ListTraverse(T, Print);
				break;
			case 11:
				printf("�������ļ���:");
				scanf("%s",filename);
				if ((fp=fopen(filename,"wb"))==NULL)
				{
					printf("���ļ�ʧ��!\n");
				}
				else {
					ListTraverse(T,WriteToFile);
				}
				fclose(fp);
				break;
			case 12:
				flag = 0;
				break;
		}


	}
}