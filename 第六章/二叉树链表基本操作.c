//二叉树链表存储基本操作
Status InitBiTree(BiTree *T){
	*T = NULL;
	return OK;
}

void DestroyBiTree(BiTree *T){
	if (*T)
	{
		if ((*T)->lchild)
		{
			DestroyBiTree(&(*T)->lchild);
		}
		if ((*T)->rchild)
		{
			DestroyBiTree(&(*T)->rchild);
		}
		free(*T);
		*T = NULL;
	}
}

void CreateBiTree(BiTree *T){
	TElemType ch;
	#ifdef CHAR
		scanf("%c",&ch);
	#endif
	#ifdef INT
		scanf("%d",&ch);
	#endif
		if (ch == Nil)
		{
			*T = NULL;
		}else{
			*T = (BiTree)malloc(sizeof(BiTNode));
			if (!*T)
			{
				exit(OVERFLOW);
			}
			(*T)->data = ch;
			CreateBiTree(&(*T)->lchild);
			CreateBiTree(&(*T)->rchild);
		}
}

Status BiTreeEmpty(BiTree T){
	if (T)
	{
		return FALSE;
	}else{
		return TRUE;
	}
}

 #define ClearBiTree DestroyBiTree

 int BiTreeDepth(BiTree T){
 	int i , j;
 	if (!T)
 	{
 		return 0;
 	}
 	if (T->lchild)
 	{
 		i = BiTreeDepth(T->lchild);
 	}else{
 		i = 0;
 	}
 	if (T->rchild)
 	{
 		j = BiTreeDepth(T->rchild);
 	}else{
 		j = 0;
 	}
 	return i>j?i+1:j+1;
 }

 TElemType Root(BiTree T){
 	if (BiTreeEmpty(T))
 	{
 		return Nil;
 	}else{
 		return T->data;
 	}
 }

 TElemType Value(BiTree p){
 	return p->data;
 }

 void Assign(BiTree p,TElemType value){
 	p->data = value;
 }

 typedef BiTree QElemType;
  /* c3-2.h 单链队列－－队列的链式存储结构 */
 typedef struct QNode
 {
   QElemType data;
   struct QNode *next;
 }QNode,*QueuePtr;

 typedef struct
 {
   QueuePtr front,rear; /* 队头、队尾指针 */
 }LinkQueue;
 #include "bo3-2" //队列9个操作
 TElemType Parent(BiTree T,TElemType e){
 	LinkQueue q;
 	QElemType a;
 	if (T)
 	{
 		InitQueue(&q);
 		EnQueue(&q,T);
 		while(!QueueEmpty(q)){
 			DeQueue(&q,&a);
 			if (a->lchild&&a->lchild->data==e||a->rchild&&a->rchild->data==e)
 			{
 				return a->data;
 			}else{
 				if(a->lchild)
 					EnQueue(&q,a->lchild);
 				if (a->rchild)
 					EnQueue(&q,a->rchild);
 			}
 		}
 	}
 	return Nil;
 }

 BiTree Point(BiTree T,TElemType s){
 	LinkQueue q;
 	QElemType A;
 	if(T){
 		InitQueue(&q);
 		EnQueue(&q,T);
 		while(!QueueEmpty(q)){
 			DeQueue(&q,&a);
 			if(a->data == s)
 				return a;
 			if(a->lchild)
 				EnQueue(&q,a->lchild);
 			if(a->rchild)
 				EnQueue(&q,a->rchild);
 		}
 	}
 	return NULL;
 }

 TElemType LeftChild(BiTree T,TElemType e){
 	BiTree a;
 	if (T)
 	{
 		a = Point(T,e);
 		if (a&&a->lchild)
 		{
 			return a->lchild->data;
 		}
 	}
 	return Nil;
 }


TElemType RightChild(BiTree T,TElemType e){
	BiTree a;
	if (T)
	{
		/* code */
		a = Point(T,e);
		if (a&&a->rchild)
		{
			return a->rchild->data;
		}
	}
	return Nil;
}

TElemType LeftSibling(BiTree T,TElemType e){
	TElemType a;
	BiTree p;
	if (T)
	{
		a = Parent(T,e);
		p = Point(T,a);
		if (p->lchild&&p->rchild&&p->rchild->data==e)
		{
			return p->lchild->data;
		}
	}
	return Nil;
}

TElemType RightSibling(BiTree T,TElemType e){
	TElemType a;
	BiTree p;
	if (T)
	{
		a = Parent(T,e);
		p = Point(T,a);
		if (p->lchild&&p->rchild&&p->lchild->data==e)
		{
			return p->rchild->data;
		}
	}
	return Nil;
}


Status InsertChild(BiTree p,int LR,BiTree c){
	if (p)
	{
		if (LR==0)
		{
			c->rchild=p->lchild;
			p->lchild=c;
		}else{
			c->rchild=p->rchild;
			p->rchild=c;
		}
		return OK;
	}
	return ERROR;
}

Status DeleteChild(BiTree p,int LR){
	if (p)
	{
		if (LR==0)
		{
			ClearBiTree(&p->lchild);
		}else{
			ClearBiTree(&p->rchild);
		}
		return OK;
	}
	return ERROR;
}

void PreOrderTraverse(BiTree T,Status(*Visit)(TElemType)){
	if (T)
	{
		Visit(T->data);
		PreOrderTraverse(T->lchild,Visit);
		PreOrderTraverse(T->rchild,Visit);
	}
}

void InOrderTraverse(BiTree T,Status(*Visit)(TElemType)){
	if (T)
	{
		InOrderTraverse(T->lchild,Visit);
		Visit(T->data);
		InOrderTraverse(T->rchild,Visit);
	}
}

typedef BiTree SElemType; 
 /* c3-1.h 栈的顺序存储表示 */
 #define STACK_INIT_SIZE 10 /* 存储空间初始分配量 */
 #define STACKINCREMENT 2 /* 存储空间分配增量 */
 typedef struct SqStack
 {
   SElemType *base; /* 在栈构造之前和销毁之后，base的值为NULL */
   SElemType *top; /* 栈顶指针 */
   int stacksize; /* 当前已分配的存储空间，以元素为单位 */
 }SqStack; /* 顺序栈 */
#include"bo3-1.c" //栈操作

 Status InOrderTraversel(BiTree T,Status(*Visit)(TElemType)){
 	SqStack S;
 	InitStack(&S);
 	while(T||!StackEmpty(S)){
 		if (T)
 		{
 			Push(&S,T);
 			T = T->lchild;
 		}else{
 			Pop(&S,&T);
 			if(!Visti(T->data))
 				return ERROR;
 			T = T->rchild;
 		}
 	}
 	printf("\n");
 	return OK;
 }

Status InOrderTraverse2(BiTree t,Status(*Visit)(TElemType)){
	SqStack S;
	BiTree p;
	InitStack(&S);
	Push(&S,T);
	while(!StackEmpty(S)){
		while(GetTop(S,&p)&&p){
			Push(&S,lchild);
		}
		Pop(&S,&p);
		if (!StackEmpty(S))
		{
			Pop(&S,&p);
			if (!Visit(p->data))
			{
				return ERROR;
			}
			Push(&S,p->rchild);
		}
	}
	printf("\n");
	return OK;
}

void PostOrderTraverse(BiTree T,Status(*Visit)(TElemType))
 { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
   /* 操作结果: 后序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
   if(T) /* T不空 */
   {
     PostOrderTraverse(T->lchild,Visit); /* 先后序遍历左子树 */
     PostOrderTraverse(T->rchild,Visit); /* 再后序遍历右子树 */
     Visit(T->data); /* 最后访问根结点 */
   }
 }


void LevelOrderTraverse(BiTree T,Status(*Visit)(TElemType)){
	LinkQueue q;
	QElemType a;
	if (T)
	{
		InitQueue(&q);
		EnQueue(&q,T);
		while(!QueueEmpty(q)){
			DeQueue(&q,&a);
			Visit(a->data);
			if (a->lchild!=NULL)
			{
				EnQueue(&q,a->lchild);
			}
			if (a->rchild!=NULL)
			{
				EnQueue(&q,a->rchild);
			}
		}
		printf("\n");
	}
}



