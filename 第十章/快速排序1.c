#include <stdio.h>
typedef int InfoType;
#define N 8
 /* c10-1.h 待排记录的数据类型 */
 #define MAXSIZE 20 /* 一个用作示例的小顺序表的最大长度 */
 typedef int KeyType; /* 定义关键字类型为整型 */
 typedef struct
 {
   KeyType key; /* 关键字项 */
   InfoType otherinfo; /* 其它数据项，具体类型在主程中定义 */
 }RedType; /* 记录类型 */

 typedef struct
 {
   RedType r[MAXSIZE+1]; /* r[0]闲置或用作哨兵单元 */
   int length; /* 顺序表长度 */
 }SqList; /* 顺序表类型 */

 int Patition(SqList *L,int low,int high){
 	RedType t;
 	KeyType pivotkey;
 	pivotkey = (*L).r[low].key;
 	while(low < high){
 		while(low < high && (*L).r[high].key>=pivotkey){
 			--high;
 		}
 		t = (*L).r[low];
 		(*L).r[low] = (*L).r[high];
 		(*L).r[high] = t;
 		while(low<high&&(*L).r[low].key<=pivotkey){
 			++low;
 		}
 		t = (*L).r[low];
 		(*L).r[low] = (*L).r[high];
 		(*L).r[high] = t;
 	}
 	return low;
 }

 void QSort(SqList *L,int low,int high){
	int pivotloc;
	if (low < high)
	{
		pivotloc = Partition(L, low, high);
		QSort(L, low, pivotloc-1);
		QSort(L, pivotloc-1, high);
	}
}

void QuickSort(SqList *L){
	QSort(L, 1, (*L).length);
}

void print(SqList L){
	int i;
	for (i = 1; i <= L.length; ++i)
	{
		printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
	}
	printf("\n");
}

void main(){
	RedType d[N] = {{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
	SqList l;
	int i;
	for (i = 0; i < N; ++i)
	{
		l.r[i+1] = d[i];
	}
	l.length = N;
	printf("排序前:\n");
	print(l);
	QuickSort(&l);
	printf("排序后:\n");
	print(l);
}