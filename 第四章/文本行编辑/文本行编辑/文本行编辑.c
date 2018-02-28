#include "predefine.h"
/* 串的堆分配存储 */
typedef struct
{
	char *ch; /* 若是非空串,则按串长分配存储区,否则ch为NULL */
	int length; /* 串长度 */
}HString;

/* 串采用堆分配存储结构的基本操作(15个) */
Status StrAssign(HString *T,char *chars) {
	int i, j;
	if ((*T).ch)
	{
		free((*T).ch);
	}
	i = strlen(chars);
	if (!i)
	{
		(*T).ch = NULL;
		(*T).length = 0;
	}
	else {
		(*T).ch = (char*)malloc(i*sizeof(char));
		if (!(*T).ch)
		{
			exit(OVERFLOW);
		}
		for (j = 0; j < i; j++)
		{
			(*T).ch[j] = chars[j];
		}
		(*T).length = i;
	}
	return OK;
}

Status StrCopy(HString *T,HString S) {
	int i;
	if ((*T).ch)
	{
		free((*T).ch);
	}
	(*T).ch = (char*)malloc(S.length*sizeof(char));
	if (!(*T).ch)
	{
		exit(OVERFLOW);
	}
	for ( i = 0; i < S.length; i++)
	{
		(*T).ch[i] = S.ch[i];
	}
	(*T).length = S.length;
	return OK;
}

Status StrEmpty(HString S) {
	if (S.length == 0&&S.ch==NULL){
		return TRUE;
	}
	return FALSE;
}

int StrCompare(HString S,HString T) {
	int i;
	for ( i = 0; i < S.length&&i<T.length; i++)
	{
		if (S.ch[i]!=T.ch[i])
		{
			return S.ch[i] - T.ch[i];
		}
	}
	return S.length - T.length;
}

int StrLength(HString S) {
	return S.length;
}

Status ClearString(HString *S){
	if ((*S).ch)
	{
		free((*S).ch);
		(*S).ch = NULL;
	}
	(*S).length = 0;
	return OK;
}

Status Concat(HString *T,HString S1,HString S2) {
	int i;
	if ((*T).ch)
	{
		free((*T).ch);
	}
	(*T).length = S1.length + S2.length;
	(*T).ch = (char *)malloc((*T).length*sizeof(char));
	if (!(*T).ch)
	{
		exit(OVERFLOW);
	}
	for ( i = 0; i <S1.length; i++)
	{
		(*T).ch[i] = S1.ch[i];
	}
	for ( i = 0; i < S2.length; i++)
	{
		(*T).ch[S1.length + i] = S2.ch[i];
	}
	return OK;
}

Status SubString(HString *Sub,HString S,int pos,int len) {
	int i;
	if (pos<1||pos>S.length||len<0||len>S.length-pos+1)
	{
		return ERROR;
	}
	if ((*Sub).ch) {
		free((*Sub).ch);
	}
	if (!len)
	{
		(*Sub).ch = NULL;
		(*Sub).length = 0;
	}
	else {
		(*Sub).ch = (char *)malloc(len*sizeof(char));
		if (!(*Sub).ch)
		{
			exit(OVERFLOW);
		}
		for ( i = 0; i <= len-1; i++)
		{
			(*Sub).ch[i] = S.ch[pos-1+i];
		}
		(*Sub).length = len;
	}
	return OK;
}

void InitString(HString *T) {
	(*T).length = 0;
	(*T).ch = NULL;
}

int Index(HString S,HString T,int pos) {
	int n, m, i;
	HString sub;
	InitString(&sub);
	if (pos>0)
	{
		n = StrLength(S);
		m = StrLength(T);
		i = pos;
		while (i<=n-m+1)
		{
			SubString(&sub,S,i,m);
			if (StrCompare(sub,T)!=0)
			{
				++i;
			}
			else {
				return i;
			}
		}
	}
	return 0;
}

Status StrInsert(HString *S,int pos,HString T) {
	int i;
	if (pos<1||pos>(*S).length+1)
	{
		return ERROR;
	}
	if (T.length)
	{
		(*S).ch=(char*)realloc((*S).ch,((*S).length+T.length)*sizeof(char));
		if (!(*S).ch)
		{
			exit(OVERFLOW);
		}
		for ( i = (*S).length-1; i >= pos-1; --i)
		{
			(*S).ch[i + T.length] = (*S).ch[i];
		}
		for ( i = 0; i < T.length; i++)
		{
			(*S).ch[pos - 1 + i] = T.ch[i];
		}
		(*S).length += T.length;
	}
	return OK;
}

Status StrDelete(HString *S,int pos,int len) {
	int i;
	if ((*S).length<pos+len-1)
	{
		exit(ERROR);
	}
	for ( i = pos-1; i <= (*S).length-len; i++)
	{
		(*S).ch[i] = (*S).ch[i + len];
	}
	(*S).length -= len;
	(*S).ch = (char *)realloc((*S).ch,(*S).length*sizeof(char));
	return OK;
}

Status Replace(HString *S,HString T,HString V) {
	int i = 1;
	if (StrEmpty(T))
	{
		return ERROR;
	}
	do
	{
		i = Index(*S,T,i);
		if (i)
		{
			StrDelete(S,i,StrLength(T));
			StrInsert(S,i,V);
			i += StrLength(V);
		}
	} while (i);
	return OK;
}

void DestroyString() {
	//堆分配类型的字符串无法销毁
}

void StrPrint(HString T) {
	int i;
	for ( i = 0; i < T.length; i++)
	{
		printf("%c",T.ch[i]);
	}
	printf("\n");
}

#define MAX_LEN 25 /* 文件最大行数 */
#define LINE_LEN 75 /* 每行字符数最大值+1 */
#define NAME_LEN 20 /* 文件名最大长度(包括盘符、路径)+1 */

/* 全局变量 */
HString T[MAX_LEN];
char str[LINE_LEN], filename[NAME_LEN] = "";
FILE *fp;
int n = 0; /* 文件行数 */

void Open()
{ /* 打开文件(新或旧) */
	int i;
	if (filename[0]) /* 文件已打开 */
		printf("已存在打开的文件\n");
	else
	{
		printf("请输入文件名(可包括盘符、路径，不超过%d个字符): ", NAME_LEN - 1);
		scanf("%s%*c", filename);
		fp = fopen(filename, "r");
		if (fp) /* 已存在此文件 */
		{
			do
			{
				fgets(str, LINE_LEN, fp);
				i = strlen(str);
				str[i - 1] = 0; /* 将10强制改为0 */
				i--;
				if (i>0)
				{
					StrAssign(&T[n], str);
					n++;
					if (n>MAX_LEN)
					{
						printf("文件太大\n");
						return;
					}
				}
			} while (i>0);
			fclose(fp);
		}
		else
			printf("新文件\n");
	}
}

void List()
{ /* 显示文件内容 */
	int i;
	for (i = 0; i<n; i++)
	{
		printf("%d: ", i + 1);
		StrPrint(T[i]);
	}
	getchar();
}

void Insert()
{ /* 插入行 */
	int i, l, m;
	printf("在第l行前插m行,请输入l m: ");
	scanf("%d%d%*c", &l, &m);
	if (n + m>MAX_LEN)
	{
		printf("插入行太多\n");
		return;
	}
	if (n >= l - 1 && l>0)
	{
		for (i = n - 1; i >= l - 1; i--)
			T[i + m] = T[i];
		n += m;
		printf("请顺序输入待插入内容:\n");
		for (i = l - 1; i<l - 1 + m; i++)
		{
			gets(str);
			InitString(&T[i]);
			StrAssign(&T[i], str);
		}
	}
	else
		printf("行超出范围\n");
}

void Delete()
{ /* 删除行 */
	int i, l, m;
	printf("从第l行起删除m行,请输入l m: ");
	scanf("%d%d%*c", &l, &m);
	if (n >= l + m - 1 && l>0)
	{
		for (i = l - 1 + m; i<n; i++)
			T[i - m] = T[i];
		for (i = n - m; i<n; i++)
			InitString(&T[i]);
		n -= m;
	}
	else
		printf("行超出范围\n");
}

void Copy()
{ /* 拷贝行 */
	int i, l, m, k;
	printf("把第l行开始的m行插在原k行之前,请输入l m k: ");
	scanf("%d%d%d%*c", &l, &m, &k);
	if (n + m>MAX_LEN)
	{
		printf("拷贝行太多\n");
		return;
	}
	if (n >= k - 1 && n >= l - 1 + m && (k >= l + m || k <= l))
	{
		for (i = n - 1; i >= k - 1; i--)
			T[i + m] = T[i];
		n += m;
		if (k <= l)
			l += m;
		for (i = l - 1; i<l - 1 + m; i++)
		{
			InitString(&T[i + k - l]);
			StrCopy(&T[i + k - l], T[i]);
		}
	}
	else
		printf("行超出范围\n");
}

void Modify()
{ /* 修改行 */
	int i;
	printf("请输入待修改的行号: ");
	scanf("%d%*c", &i);
	if (i>0 && i <= n) /* 行号合法 */
	{
		printf("%d: ", i);
		StrPrint(T[i - 1]);
		printf("请输入新内容: ");
		gets(str);
		StrAssign(&T[i - 1], str);
	}
	else
		printf("行号超出范围\n");
}

void Search()
{ /* 查找字符串 */
	int i, k, f = 1; /* f为继续查找标志 */
	char b;
	HString s;
	printf("请输入待查找的字符串: ");
	scanf("%s%*c", str);
	InitString(&s);
	StrAssign(&s, str);
	for (i = 0; i<n&&f; i++) /* 逐行查找 */
	{
		k = 1; /* 由每行第1个字符起查找 */
		while (k)
		{
			k = Index(T[i], s, k); /* 由本行的第k个字符开始查找 */
			if (k) /* 找到 */
			{
				printf("第%d行: ", i + 1);
				StrPrint(T[i]);
				printf("第%d个字符处找到。继续查找吗(Y/N)? ", k);
				b = getchar();
				getchar();
				if (b != 'Y'&&b != 'y') /* 中断查找 */
				{
					f = 0;
					break;
				}
				else
					k++;
			}
		}
	}
	if (f)
		printf("没找到\n");
}

void Replace1()
{ /* 替换字符串 */
	int i, k, f = 1; /* f为继续替换标志 */
	char b;
	HString s, t;
	printf("请输入待替换的字符串: ");
	scanf("%s%*c", str);
	InitString(&s);
	StrAssign(&s, str);
	printf("替换为: ");
	scanf("%s%*c", str);
	InitString(&t);
	StrAssign(&t, str);
	for (i = 0; i<n&&f; i++) /* 逐行查找、替换 */
	{
		k = 1; /* 由每行第1个字符起查找 */
		while (k)
		{
			k = Index(T[i], s, k); /* 由本行的第k个字符开始查找 */
			if (k) /* 找到 */
			{
				printf("第%d行: ", i + 1);
				StrPrint(T[i]);
				printf("第%d个字符处找到。是否替换(Y/N)? ", k);
				b = getchar();
				getchar();
				if (b == 'Y' || b == 'y')
				{
					StrDelete(&T[i], k, StrLength(s));
					StrInsert(&T[i], k, t);
				}
				printf("继续替换吗(Y/N)?");
				b = getchar();
				getchar();
				if (b != 'Y'&&b != 'y') /* 中断查找、替换 */
				{
					f = 0;
					break;
				}
				else
					k += StrLength(t);
			}
		}
	}
	if (f)
		printf("没找到\n");
}

void Save()
{ /* 存盘 */
	int i;
	getchar();
	fp = fopen(filename, "w");
	if (fp)
	{
		for (i = 0; i<n; i++)
		{
			T[i].ch[T[i].length] = 0;
			fputs(T[i].ch, fp);
			fputc(10, fp);
		}
		fputc(10, fp);
		fclose(fp);
	}
	else
		printf("存盘失败\n");
}

void main()
{
	Status s = TRUE;
	int i, k;
	for (i = 0; i<MAX_LEN; i++) /* 初始化串 */
		InitString(&T[i]);
	while (s)
	{
		printf("请选择: 1.打开文件(新或旧)  2.显示文件内容\n");
		printf("        3.插入行  4.删除行  5.拷贝行  6.修改行\n");
		printf("        7.查找字符串        8.替换字符串\n");
		printf("        9.存盘退出          0.放弃编辑\n");
		scanf("%d", &k);
		switch (k)
		{
		case 1: Open();
			break;
		case 2: List();
			break;
		case 3: Insert();
			break;
		case 4: Delete();
			break;
		case 5: Copy();
			break;
		case 6: Modify();
			break;
		case 7: Search();
			break;
		case 8: Replace1();
			break;
		case 9: Save();
		case 0: s = FALSE;
		}
	}
}