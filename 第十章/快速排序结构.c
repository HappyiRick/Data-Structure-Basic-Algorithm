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