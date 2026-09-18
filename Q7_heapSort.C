#include<stdio.h>

void swap(int *a, int *b){
    int temp = *a;
    *a=*b;
    *b=temp;
    return;
}

void heapify(int arr[], int n, int i){
    int maxx = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && arr[left] > arr[maxx])
        maxx = left;
    if(right < n && arr[right] > arr[maxx])
        maxx = right;

    if(maxx != i){
        swap(&arr[maxx], &arr[i]);
        heapify(arr, n, maxx);
    }
}

void heap(int arr[],int n){
    for(int i = n / 2; i >= 0; i--)
        heapify(arr, n, i);
    for(int i = n - 1; i > 0; i--){
        swap(&arr[0],&arr[i]);
        heapify(arr, i, 0);
    }
}

int main(){
    int arr[5]={54,76,2,6,10};
    heap(arr,5);
    for(int i=0;i<5;i++){
        printf("%d ",arr[i]);
    }
}