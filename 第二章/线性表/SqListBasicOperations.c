//线性表的动态分配顺序存储结构
#include <PreDefine.h>

 #define LIST_INIT_SIZE 10  /* 线性表存储空间的初始分配量 */
 #define LISTINCREMENT 2 /* 线性表存储空间的分配增量 */
 typedef struct
 {
   ElemType *elem; /* 存储空间基址 */
   int length; /* 当前长度 */
   int listsize; /* 当前分配的存储容量(以sizeof(ElemType)为单位) */
 }SqList;


  /*顺序表示的线性表的基本操作(12个) */
 //构建一个空的顺序表
Status InitList(SqList *L){
	(*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!(*L).elem)
	{
		exit(OVERFLOW);
	}
	(*L).length = 0;
	(*L).listsize = LIST_INIT_SIZE;
}

//销毁顺序表
Status DestroyList(SqList *L){
	free((*L).elem);
	(*L).elem = NULL;
	(*L).length = 0;
	(*L).listsize = 0;
	return OK;
}

//重置顺序表
Status ClearList(SqList *L){
	(*L).length = 0;
	return OK;
}

//判断顺序表是否为空
Status listEmpty(SqList *L){
	if (L.length == 0)
	{
		return TRUE;
	}
	return FALSE;
}

//顺序表长度
int ListLength(SqList L){
	return L.length;
}

//用e返回L中第i个数据元素的值
Status GetElem(SqList L,int i,ElemType *e){
	if (i<1||i>L.length)
	{
		exit(ERROR);
	}
	*e = *(L.elem+i-1);
	return OK;
}

//