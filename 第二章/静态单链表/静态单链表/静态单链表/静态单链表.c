/*�̿�����ͼ2.10 ��̬����ʾ�� */
#include "predefine.h"
#define MAXSIZE 100 /* �������󳤶� */
#define N 6
typedef char ElemType[N];

/*���Ա�ľ�̬������洢�ṹ */
typedef struct
{
	ElemType data;
	int cur;
}component, SLinkList[MAXSIZE];

void main() {
	SLinkList s = {
		{"",1},{"zhao",2},{"qian",3},{"sun",4},{"LI",5},{"zhou",6},{"wu",7},{"zheng",8},{"wang",0}
	};
	int i;
	i = s[0].cur;
	while (i)/* ����̿�����ͼ2.10(a)��״̬ */
	{
		printf("%s ",s[i].data);/* �������ĵ�ǰֵ */
		i = s[i].cur;/* �ҵ���һ�� */
	}
	printf("\n");
	s[4].cur = 9;/* ���̿�����ͼ2.10(b)�޸� */
	s[6].cur = 8;
	s[9].cur = 5;
	strcpy(s[9].data,"SHI");
	i = s[0].cur;
	while (i)/* ����̿�����ͼ2.10(b)��״̬ */
	{
		printf("%s ",s[i].data);/* �������ĵ�ǰֵ */
		i = s[i].cur;/* �ҵ���һ�� */
	}
	printf("\n");
	system("pause");
}