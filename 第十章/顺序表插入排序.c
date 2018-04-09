//顺序表插入排序的函数
void InsertSort(SqList *L){
	int i, j;
	for (i = 2; i <= (*L).length; ++i)
	{
		if (LT((*L).r[i].key,(*L).r[i-1].key)) // LT = "<"
		{
			(*L).r[0] = (*L).r[i];//复制为哨兵
			for (j = i-1;LT((*L).r[0].key,(*L).r[j].key); --j)
			{
				(*L).r[j+1] = (*L).r[j];
			}
			(*L).r[j+1] = (*L).r[0];
		}
	}
}

void BInsertSort(SqList *L){
	int i,j,m,low,high;
	for (i = 2; i <= (*L).length; ++i)
	{
		(*L).r[0] = (*L).r[i];
		low = 1;
		high = i - l;
		while(low < high){
			m = (low+high)/2;
			if (LT((*L).r[0].key,(*L).r[m].key))
			{
				high = m-1;
			}else{
				low = m+1;
			}
		}
		for (j = i-1; j >= high+1; --j){
			(*L).r[j+1] = (*L).r[j];
		}
		(*L).r[high+1] = (*L).r[0];
	}
}

void P2_InsertSort(SqList *L){
	int i,j,first,final;
	RedType *d;
	d = (RedType *)malloc((*L).length*sizeof(RedType));
	d[0] = (*L).r[1];
	first = final = 0;
	for (i = 2; i <=(*L).length; ++i)
	{
		if ((*L).r[i].key<d[first].key)
		{
			first = (first-1+(*L).length)%(*L).length;
			d[first] = (*L).r[i];
		}else if ((*L).r[i].key>d[final].key){
			final = final + 1;
			d[final] = (*L).r[i];
		}else{
			j = final++;
			while((*L).r[i].key<d[j].key){
				d[(j+1)%(*L).length] = d[j];
				j = (j-1+(*L).length)%(*L).length;
			}
			d[j+1] = (*L).r[i];
		}
	}
	for (i = 1; i <= (*L).length; ++i)
	{
		(*L).r[i] = d[(i+first-1)%(*L).length];
	}
}
