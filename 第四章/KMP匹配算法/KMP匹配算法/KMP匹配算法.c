#include "predefine.h"
/* ���Ķ���˳��洢��ʾ */
#define MAXSTRLEN 40 /* �û�����255���ڶ�����󴮳���1���ֽڣ� */
typedef char SString[MAXSTRLEN + 1]; /* 0�ŵ�Ԫ��Ŵ��ĳ��� */

/* �����ö���˳��洢�ṹ�Ļ�������14��*/
Status StrAssign(SString T,char *chars) {
	int i;
	if (strlen(chars)>MAXSTRLEN)
	{
		return ERROR;
	}
	else {
		T[0] = strlen(chars);
		for (i = 1; i <= T[0]; i++)
		{
			T[i] = *(chars + i - 1);
		}
		return OK;
	}
}

Status StrCopy(SString T,SString S) {
	int i;
	for ( i = 0; i <=S[0]; i++)
	{
		T[i] = S[i];
	}
	return OK;
}

Status StrEmpty(SString S) {
	if (S[0]==0)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}

int StrCompare(SString S,SString T) {
	int i;
	for ( i = 1; i <= S[0]&&i<=T[0]; i++)
	{
		if (S[i]!=T[i]) {
			return S[i] - T[i];
		}
	}
	return S[0] - T[0];
}

int StrLength(SString S) {
	return S[0];
}

Status ClearString(SString S) {
	S[0] = 0;
	return OK;
}

Status Concat(SString T,SString S1,SString S2) {
	int i;
	if (S1[0]+S2[0]<=MAXSTRLEN)
	{	//δ���ض�
		for ( i = 1; i <= S1[0]; i++)
		{
			T[i] = S1[i];
		}
		for ( i = 1; i <= S2[0]; i++)
		{
			T[S1[0] + i] = S2[i];
		}
		T[0] = S1[0] + S2[0];
		return TRUE;
	}
	else {
		for ( i = 1; i <= S1[0]; i++)
		{
			T[i] = S1[i];
		}
		for ( i = 1; i <= MAXSTRLEN-S1[0]; i++)
		{
			T[S1[0] + i] = S2[i];
		}
		T[0] = MAXSTRLEN;
		return FALSE;
	}
}

Status SubString(SString Sub,SString S,int pos,int len) {
	int i;
	if (pos<1||pos>S[0]||len<0||len>S[0]-pos+1)
	{
		return ERROR;
	}
	for ( i = 1; i <=len ;i++)
	{
		Sub[i] = S[pos+i-1];
	}
	Sub[0] = len;
	return OK;
}

int Index(SString S,SString T,int pos) {
	int i, j;
	if (1<=pos&&pos<=S[0])
	{
		i = pos;
		j = 1;
		while (i<=S[0]&&j<=T[0])
		{
			if (S[i]==T[j])
			{
				++i;
				++j;
			}
			else {
				i = i - j + 2;
				j = 1;
			}
		}
		if (j>T[0])
		{
			return i - T[0];
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

Status StrInsert(SString S,int pos,SString T) {
	int i;
	if (pos<1||pos>S[0]+1)
	{
		return ERROR;
	}
	if (S[0]+T[0]<=MAXSTRLEN)
	{
		for ( i = S[0]; i >= pos; i--)
		{
			S[i + T[0]] = S[i];
		}
		for ( i = pos; i < pos+T[0]; i++)
		{
			S[i] = T[i - pos + 1];
		}
		S[0] = S[0] + T[0];
		return TRUE;
	}
	else {
		for ( i = MAXSTRLEN; i <= pos; i--)
		{
			S[i] = S[i-T[0]];
		}
		for ( i = pos; i < pos+T[0]; i++)
		{
			S[i] = T[i-pos+1];
		}
		S[0] = MAXSTRLEN;
		return FALSE;
	}
}

Status StrDelete(SString S,int pos,int len) {
	int i;
	if (pos<1||pos>S[0]-len||len<0)
	{
		return ERROR;
	}
	for ( i = pos+len; i <= S[0]; i++)
	{
		S[i - len] = S[i];
	}
	S[0] -= len;
	return OK;
}

Status Replace(SString S,SString T,SString V) {
	int i = 0;
	if (StrEmpty(T))
	{
		return ERROR;
	}
	do
	{
		i = Index(S,T,i);
		if (i)
		{
			StrDelete(S, i, StrLength(T));
			StrInsert(S,i,V);
			i += StrLength(V);
		}
	} while (i);
	return OK;
}

void DestroyString() {
	//����SString�Ƕ������ͣ��޷�����
}

void StrPrint(SString T)
{ /* ����ַ���T����� */
	int i;
	for (i = 1; i <= T[0]; i++) {
		printf("%c", T[i]);
	}
	printf("\n");
}

/* ��ģʽ��T��next����ֵ����������next */
void get_next(SString T,int next[]) {
	int i = 1, j = 0;
	next[1] = 0;
	while (i<T[0])
	{
		if (j==0||T[i]==T[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else {
			j = next[j];
		}
	}
}
/* ����ģʽ��T��next������T������S�е�pos���ַ�֮���λ�õ�KMP�㷨�� */
/* ����,T�ǿ�,1��pos��StrLength(S)���㷨 4.6 */
int Index_KMP(SString S,SString T,int pos,int next[]) {
	int i = pos, j = 1;
	while (i <= S[0]&&j<=T[0])
	{
		if (j==0||S[i]==T[j])/* �����ȽϺ���ַ� */
		{
			++i;
			++j;
		}
		else {/* ģʽ�������ƶ� */
			j = next[j];
		}
	}
	if (j>T[0])/* ƥ��ɹ� */
	{
		return i - T[0];
	}
	else {
		return 0;
	}
}


void main() {
	int i, j, *p;
	SString s1, s2;
	StrAssign(s1,"acabaabaabcacaabc");
	printf("����Ϊ��");
	StrPrint(s1);
	StrAssign(s2, "abaabcac");
	printf("�Ӵ�Ϊ: ");
	StrPrint(s2);
	i = StrLength(s2);
	p = (int*)malloc((i + 1) * sizeof(int)); /* ����s2��next���� */
	get_next(s2, p);
	printf("�Ӵ���next����Ϊ: ");
	for (j = 1; j <= i; j++)
		printf("%d ", *(p + j));
	printf("\n");
	i = Index_KMP(s1, s2, 1, p);
	if (i)
		printf("�������Ӵ��ڵ�%d���ַ����״�ƥ��\n", i);
	else
		printf("�������Ӵ�ƥ�䲻�ɹ�\n");
	system("pause");
}