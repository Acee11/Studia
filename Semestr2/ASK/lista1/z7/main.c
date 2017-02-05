void insertion_sort(int *arr, int length)
{
	int j, temp;
    int i;
	i = 0;
	for_begin:
	if(i >= length) goto for_exit;
	j = i;
	while_begin:
	if (j <= 0 || arr[j] >= arr[j-1]) goto while_exit;
	temp = arr[j];
	arr[j] = arr[j-1];
	arr[j-1] = temp;
	j--;
    goto while_begin;
    while_exit:
    i++;
	goto for_begin;
	for_exit:
	return;
}

int main()
{
    int a[5];
    a[0] = 4;
    a[1] = 9;
    a[2] = 0;
    a[3] = 99;
    a[4] = 1;

    int i;
    insertion_sort(a,5);
    for(i=0;i<5;i++) printf("%d ",a[i]);
}
