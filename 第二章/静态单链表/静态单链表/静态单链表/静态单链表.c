/*教科书中图2.10 静态链表示例 */
#include "predefine.h"
#define MAXSIZE 100 /* 链表的最大长度 */
#define N 6
typedef char ElemType[N];

/*线性表的静态单链表存储结构 */
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
	while (i)/* 输出教科书中图2.10(a)的状态 */
	{
		printf("%s ",s[i].data);/* 输出链表的当前值 */
		i = s[i].cur;/* 找到下一个 */
	}
	printf("\n");
	s[4].cur = 9;/* 按教科书中图2.10(b)修改 */
	s[6].cur = 8;
	s[9].cur = 5;
	strcpy(s[9].data,"SHI");
	i = s[0].cur;
	while (i)/* 输出教科书中图2.10(b)的状态 */
	{
		printf("%s ",s[i].data);/* 输出链表的当前值 */
		i = s[i].cur;/* 找到下一个 */
	}
	printf("\n");
	system("pause");
}