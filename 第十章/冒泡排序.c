#define N 8
void bubble_sort(int a[],int n){
	int i,j,t;
	Status change;
	for (i = n-1, change = 1; i>1&&change; --i)
	{
		change = 0;
		for (j = 0; j < i; ++j)
		{
			if (a[j]<a[j+1])
			{
				t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
				change = 1;
			}
		}
	}
}

void print(int r[],int n){
	int i ;
	for (i = 0; i < n; ++i)
	{
		printf("%d",r[i]);
	}
	printf("\n");
}

int main(void)
{
	int d[N] = {49,38,65,97,76,13,27,49};
	printf("排序前:\n");
	print(d,N);
	bubble_sort(d,N);
	printf("排序后:\n");
	print(d,N);
	return 0;
}