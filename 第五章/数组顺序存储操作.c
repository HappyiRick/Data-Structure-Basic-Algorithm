/*数组的顺序存储表示*/
#include <stdarg.h>/*标准头文件，提供宏va_start,va_arg和va_end*/
				   /*用于存取变长参数表*/
#define MAX_ARRAY_DIM 8
typedef struct 
{
	ElemType *base;
	int dim;
	int *bounds;
	int *constants;
}Array;

//状态码包含于predefine.h中
Status InitArray(Array *A,int dim,...){
	int elemtotal = 1, i;
	va_list ap;
	if (dim<1||dim>MAX_ARRAY_DIM)
	{
		return ERROR;
	}
	(*A).dim = dim;
	(*A).bounds = (int *)malloc(dim*sizeof(int));
	if (!(*A).bounds)
	{
		exit(OVERFLOW);
	}
	va_start(ap,dim);
	for (int i = 0; i < dim; ++i)
	{
		(*A).bounds[i] = va_arg(ap,int);
		if ((*A).bounds[i]<0)
		{
			return UNDERFLOW;
		}
		elemtotal *= (*A).bounds[i];
	}
	va_end(ap);
	(*A).base = (ElemType *)malloc(elemtotal*sizeof(ElemType));
	if (!(*A).base)
	{
		exit(OVERFLOW);
	}
	(*A).constants = (int *)malloc(dim*sizeof(int));
	if (!(*A).constants)
	{
		exit(OVERFLOW);
	}
	(*A).constants[dim-1] = 1;
	for (int i = dim-2; i >=0; --i)
	{
		(*A).constants[i] = (*A).bounds[i+1]*(*A).constants[i+1];
	}
	return OK;
}


Status DestroyArray(Array *A){
	if ((*A).base)
	{
		free((*A).base);
		(*A).base = NULL;
	}else{
		return ERROR;
	}
	if ((*A).bounds)
	{
		free((*A).bounds);
		(*A).bounds = NULL;
	}else{
		return ERROR;
	}
	if ((*A).constants)
	{
		free((*A).constants);
		(*A).constants = NULL;
	}else{
		return ERROR;
	}
	return OK;
}


Status Locate(Array A,va_list ap,int *off){
	int i,ind;
	*off = 0;
	for (int i = 0; i < A.dim; ++i)
	{
		ind = va_arg(ap,int);
		if (ind<0||ind>=A.bounds[i])
		{
			return OVERFLOW;
		}
		*off += A.constants[i]*ind;
	}
	return OK;
}

Status Value(ElemType *e,Array A,...){
	va_list ap;
	Status result;
	int off;
	va_start(ap,A);
	if ((result = Locate(A,ap,&off)) == OVERFLOW)
	{
		return result;
	}
	*e = *(A.base+off);
	return OK;
}

Status Assign(Array *A,ElemType e,...){
	va_list ap;
	Status result;
	int off;
	va_start(ap,e);
	if ((result=Locate(*A,ap,&off))==OVERFLOW)
	{
		return result;
	}
	*((*A).base+off) = e;
	return OK;
}