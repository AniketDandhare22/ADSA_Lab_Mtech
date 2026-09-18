#include<stdio.h>

void swap(int *a ,int *b){
    int temp = *a;
    *a=*b;
    *b=temp;
    return;
}

int partition(int arr[], int l, int h){
    int i = l - 1;
    for(int j = l; j < h; j++){
        if(arr[j] <= arr[h]){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[h],&arr[i+1]);
    return i + 1;
}

void quick(int arr[], int low, int high){
    if(low < high){
        int pivotIndex = partition(arr, low, high);
        quick(arr, low, pivotIndex - 1);
        quick(arr, pivotIndex + 1, high);
    }
    else return;
}

int main(){
    int arr[5]={54,76,2,6,10};
    quick(arr, 0, 4);
    for(int i=0;i<5;i++){
        printf("%d ",arr[i]);
    }
}