#include<stdio.h>

//merging the array
void mergesort(int arr[], int s, int mid, int e){
    int i = s, j = mid + 1, k = 0;
    int b[e-s+1];
        while(i<=mid && j<=e){
            if(arr[i]<=arr[j]){
                b[k++]=arr[i++];
            }
            else{
                b[k++]=arr[j++];
            }
        }
        while(i<=mid){
            b[k++]=arr[i++];
        }
        while(j<=e){
            b[k++]=arr[j++];
        }
        for(int i=0; i<k; i++){
            arr[s + i]=b[i];
        }
    }

//diving the arr
void merge(int arr[], int start, int end){
        if(start >= end) return;
        int mid = start + (end - start) / 2;
        merge(arr, start, mid);
        merge(arr, mid + 1, end);
        mergesort(arr, start, mid, end);
    }


int main(){
    int arr[5]={54,76,2,6,10};
    merge(arr,0,4);
    for(int i=0;i<5;i++){
        printf("%d ",arr[i]);
    }
}