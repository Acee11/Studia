#include <stdio.h>
#include <stdbool.h>

void heapify(int *dst, int *src, int size, int n, int i) 
{
  if(i >= size)
    return;
  dst[i] = src[n/2];
  heapify(dst, src, size, n/2, 2*i+1) ;
  heapify(dst, src + (n/2) + 1, size, n/2 - (n%2 == 0), 2*i+2); 
}

bool heap_search(int *arr, int size, int x) 
{
  int i = 0;
  while(i < size)
  {
    if(arr[i] == x)
      return true;
    i = 2 * i + (x > arr[i] ? 2 : 1);  
  } 
  return false;
}

int main()
{
  int arr[10] = {1,4,6,8,88,190,1337, 2000, 9000, 10000};

  int arr1[10];

  heapify(arr1, arr, 10, 10, 0);

  int i;
  //for(i = 0; i < 10; ++i)
  //  printf("%d  ",arr1[i]);
  //printf("\n");
  for(i = 0; i < 10; i++)  
    printf("%d\n", heap_search(arr1, 10, i));

  return 0;
}