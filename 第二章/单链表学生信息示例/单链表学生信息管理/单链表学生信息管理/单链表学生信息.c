#include "predefine.h"
#define _CRT_SECURE_NO_WARNINGS //去除C4996错误


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

char sta[3][9] = {"健康","一般","神经衰弱"};
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
		printf("男");
	}
	else {
		printf("女");
	}
	printf("%5d %-4s",e.age,e.Class);
	printf("%9s\n",sta[e.health]);
}

void ReadIn(struct stud *e) {
	printf("请输入姓名(<=%d个字符)",NAMELEN);
	scanf("%s", e->name);
	printf("请输入学号：");
	scanf("%ld",&e->name);
	printf("请输入性别(m:男 f:女)");
	scanf("%*c%c",&e->sex);
	printf("请输入年龄:");
	scanf("%d",&e->age);
	printf("请输入班级(<=%d个字符)",CLASSLEN);
	scanf("%s",e->Class);
	printf("请输入健康状况(0:%s 1:%s 2:%s)",sta[0],sta[1],sta[2]);
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
	printf("请输入待修改项的内容，不修改的项按回车键保持原值：\n");
	printf("请输入姓名(<=%d个字符)：",NAMELEN);
	gets(s);
	if (strlen(s))
	{
		strcpy(e->name,s);
	}
	printf("请输入学号：");
	gets(s);
	if (strlen(s))
	{
		e->num = atol(s);
	}
	printf("请输入性别(m:男 f:女)：");
	gets(s);
	if (strlen(s))
	{
		e->sex = s[0];
	}
	printf("请输入班级(<=%d个字符)：",CLASSLEN);
	gets(s);
	if (strlen(s))
	{
		strcpy(e->Class,s);
	}
	printf("请输入健康状况(0：%s 1：%s 2：%s):",sta[0],sta[1],sta[2]);
	gets(s);
	if (strlen(s))
	{
		e->health = atoi(s);
	}
}

#define N 4 //student 记录的个数
void main() {
	struct stud student[N] = {
		{ "张三",110011,'m',18,"信14",0 },
		{ "李四",220011,'f',19,"信14",1 },
		{ "王五",330011,'m',18,"信14",0 },
		{ "啥六",440011,'f',20,"信14",0 },
	};
	int i, j, flag = 1;
	long num;
	char filename[13], name[NAMELEN + 1];
	ElemType e;
	LinkList T, p, q;
	InitList(&T);
	while (flag)
	{
		printf("1:将结构体数组student中的数据按学号非降序插入链表\n");
		printf("2:将文件中的记录按学号非降序插入链表\n");
		printf("3:键盘输入新记录，并将其按学号非降序插入链表\n");
		printf("4:删除链表中第一个有给定学号的记录\n");
		printf("5:删除链表中第一个有给定姓名的记录\n");
		printf("6:修改链表中第一个有给定学号的记录\n");
		printf("7:修改链表中第一个有给定学号的记录\n");
		printf("8:查找链表黑总第一个有给定学号的记录\n");
		printf("9:查找链表黑总第一个有给定姓名的记录\n");
		printf("10:显示所有记录\n");
		printf("11:将链表中的所有记录存入文件\n");
		printf("12:结束\n");
		printf("请选择操作命令：\n");
		scanf("%d",&i);
		switch (i)
		{
			case 1:
				for (j = 0; j < N; j++){
					InsertAscend(T,student[j]);
					}
				   break;
			case 2:
				printf("请输入文件名：");
				scanf("%s",filename);
				if ((fp=fopen(filename,"rb"))==NULL)
				{
					printf("打开文件失败!\n");
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
				printf("请输入待删除记录的学号：");
				scanf("%ld",&num);
				if (!DeleteElemNum(T,num))
				{
					printf("没有学号为%ld的记录\n",num);
				}
				break;
			case 5:
				printf("请输入待删除记录的姓名:");
				scanf("%s",name);
				if (!DeleteElemName(T,name))
				{
					printf("没有学号为%ld的记录\n",num);
				}
				break;
			case 6:
				printf("请输入待修改记录的学号：");
				scanf("%ld%*c",&num);//%*c吃掉回车符
				if (!FindFromNum(T,num,&p,&q))
				{
					printf("没有序号为%ld的记录\n",num);
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
				printf("请输入待修改记录的姓名：");
				scanf("%s%*c",name);
				if (!FindFromName(T,name,&p,&q))
				{
					printf("没有姓名为%s的记录\n",name);
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
				printf("请输入待查找记录的学号：");
				scanf("%ld",&num);
				if (!FindFromNum(T,num,&p,&q))
				{
					printf("没有学号为%ld的记录\n",num);
				}
				else {
					Print(q->data);
				}
				break;
			case 9:
				printf("请输入待查找记录的姓名：");
				scanf("%s",name);
				if (!FindFromName(T,name,&p,&q))
				{
					printf("没有姓名为%s的记录\n",name);
				}
				else {
					Print(q->data);
				}
			case 10:
				printf("姓名 学号 性别 年龄 班级 健康状况\n");
				ListTraverse(T, Print);
				break;
			case 11:
				printf("请输入文件名:");
				scanf("%s",filename);
				if ((fp=fopen(filename,"wb"))==NULL)
				{
					printf("打开文件失败!\n");
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