#include "predefine.h"
/* ���Ķѷ���洢 */
typedef struct
{
	char *ch; /* ���Ƿǿմ�,�򰴴�������洢��,����chΪNULL */
	int length; /* ������ */
}HString;

/* �����öѷ���洢�ṹ�Ļ�������(15��) */
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
	//�ѷ������͵��ַ����޷�����
}

void StrPrint(HString T) {
	int i;
	for ( i = 0; i < T.length; i++)
	{
		printf("%c",T.ch[i]);
	}
	printf("\n");
}

#define MAX_LEN 25 /* �ļ�������� */
#define LINE_LEN 75 /* ÿ���ַ������ֵ+1 */
#define NAME_LEN 20 /* �ļ�����󳤶�(�����̷���·��)+1 */

/* ȫ�ֱ��� */
HString T[MAX_LEN];
char str[LINE_LEN], filename[NAME_LEN] = "";
FILE *fp;
int n = 0; /* �ļ����� */

void Open()
{ /* ���ļ�(�»��) */
	int i;
	if (filename[0]) /* �ļ��Ѵ� */
		printf("�Ѵ��ڴ򿪵��ļ�\n");
	else
	{
		printf("�������ļ���(�ɰ����̷���·����������%d���ַ�): ", NAME_LEN - 1);
		scanf("%s%*c", filename);
		fp = fopen(filename, "r");
		if (fp) /* �Ѵ��ڴ��ļ� */
		{
			do
			{
				fgets(str, LINE_LEN, fp);
				i = strlen(str);
				str[i - 1] = 0; /* ��10ǿ�Ƹ�Ϊ0 */
				i--;
				if (i>0)
				{
					StrAssign(&T[n], str);
					n++;
					if (n>MAX_LEN)
					{
						printf("�ļ�̫��\n");
						return;
					}
				}
			} while (i>0);
			fclose(fp);
		}
		else
			printf("���ļ�\n");
	}
}

void List()
{ /* ��ʾ�ļ����� */
	int i;
	for (i = 0; i<n; i++)
	{
		printf("%d: ", i + 1);
		StrPrint(T[i]);
	}
	getchar();
}

void Insert()
{ /* ������ */
	int i, l, m;
	printf("�ڵ�l��ǰ��m��,������l m: ");
	scanf("%d%d%*c", &l, &m);
	if (n + m>MAX_LEN)
	{
		printf("������̫��\n");
		return;
	}
	if (n >= l - 1 && l>0)
	{
		for (i = n - 1; i >= l - 1; i--)
			T[i + m] = T[i];
		n += m;
		printf("��˳���������������:\n");
		for (i = l - 1; i<l - 1 + m; i++)
		{
			gets(str);
			InitString(&T[i]);
			StrAssign(&T[i], str);
		}
	}
	else
		printf("�г�����Χ\n");
}

void Delete()
{ /* ɾ���� */
	int i, l, m;
	printf("�ӵ�l����ɾ��m��,������l m: ");
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
		printf("�г�����Χ\n");
}

void Copy()
{ /* ������ */
	int i, l, m, k;
	printf("�ѵ�l�п�ʼ��m�в���ԭk��֮ǰ,������l m k: ");
	scanf("%d%d%d%*c", &l, &m, &k);
	if (n + m>MAX_LEN)
	{
		printf("������̫��\n");
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
		printf("�г�����Χ\n");
}

void Modify()
{ /* �޸��� */
	int i;
	printf("��������޸ĵ��к�: ");
	scanf("%d%*c", &i);
	if (i>0 && i <= n) /* �кźϷ� */
	{
		printf("%d: ", i);
		StrPrint(T[i - 1]);
		printf("������������: ");
		gets(str);
		StrAssign(&T[i - 1], str);
	}
	else
		printf("�кų�����Χ\n");
}

void Search()
{ /* �����ַ��� */
	int i, k, f = 1; /* fΪ�������ұ�־ */
	char b;
	HString s;
	printf("����������ҵ��ַ���: ");
	scanf("%s%*c", str);
	InitString(&s);
	StrAssign(&s, str);
	for (i = 0; i<n&&f; i++) /* ���в��� */
	{
		k = 1; /* ��ÿ�е�1���ַ������ */
		while (k)
		{
			k = Index(T[i], s, k); /* �ɱ��еĵ�k���ַ���ʼ���� */
			if (k) /* �ҵ� */
			{
				printf("��%d��: ", i + 1);
				StrPrint(T[i]);
				printf("��%d���ַ����ҵ�������������(Y/N)? ", k);
				b = getchar();
				getchar();
				if (b != 'Y'&&b != 'y') /* �жϲ��� */
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
		printf("û�ҵ�\n");
}

void Replace1()
{ /* �滻�ַ��� */
	int i, k, f = 1; /* fΪ�����滻��־ */
	char b;
	HString s, t;
	printf("��������滻���ַ���: ");
	scanf("%s%*c", str);
	InitString(&s);
	StrAssign(&s, str);
	printf("�滻Ϊ: ");
	scanf("%s%*c", str);
	InitString(&t);
	StrAssign(&t, str);
	for (i = 0; i<n&&f; i++) /* ���в��ҡ��滻 */
	{
		k = 1; /* ��ÿ�е�1���ַ������ */
		while (k)
		{
			k = Index(T[i], s, k); /* �ɱ��еĵ�k���ַ���ʼ���� */
			if (k) /* �ҵ� */
			{
				printf("��%d��: ", i + 1);
				StrPrint(T[i]);
				printf("��%d���ַ����ҵ����Ƿ��滻(Y/N)? ", k);
				b = getchar();
				getchar();
				if (b == 'Y' || b == 'y')
				{
					StrDelete(&T[i], k, StrLength(s));
					StrInsert(&T[i], k, t);
				}
				printf("�����滻��(Y/N)?");
				b = getchar();
				getchar();
				if (b != 'Y'&&b != 'y') /* �жϲ��ҡ��滻 */
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
		printf("û�ҵ�\n");
}

void Save()
{ /* ���� */
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
		printf("����ʧ��\n");
}

void main()
{
	Status s = TRUE;
	int i, k;
	for (i = 0; i<MAX_LEN; i++) /* ��ʼ���� */
		InitString(&T[i]);
	while (s)
	{
		printf("��ѡ��: 1.���ļ�(�»��)  2.��ʾ�ļ�����\n");
		printf("        3.������  4.ɾ����  5.������  6.�޸���\n");
		printf("        7.�����ַ���        8.�滻�ַ���\n");
		printf("        9.�����˳�          0.�����༭\n");
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