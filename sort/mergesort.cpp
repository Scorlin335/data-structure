#include <iostream>
#include <time.h>
//稳定,时间复杂度固定为O(nlogn),空间复杂度为O(n+logn)
using namespace std;

void Merge(int arr[],int begin,int mid,int end, int *p){
    //int *p = new int[end - begin + 1];
    int i = begin;
    int j = mid + 1;
    int k = 0;
    while(i<=mid&&j<=end){
        if(arr[i]<=arr[j]){
            p[k++] = arr[i++];
        }else{
            p[k++] = arr[j++];
        }
    }
    while(i<=mid){
        p[k++] = arr[i++];
    }
    while(j<=end){
        p[k++] = arr[j++];
    }
    for (i = begin, j = 0; i <= end;i++,j++){
        arr[i] = p[j];
    }
    //delete[] p;
}

// 函数重载
void MergeSort(int arr[], int begin, int end, int *p)
{
    if (begin >= end)
    {
        return;
    }
    int mid = (begin + end) / 2;
    //先递
    MergeSort(arr, begin, mid, p);
    MergeSort(arr, mid + 1, end, p);
    //再归,递之后的部分就是归的时候做的操作
    Merge(arr, begin, mid, end, p);
}

void MergeSort(int arr[], int len)
{
    int *p = new int[len];
    MergeSort(arr, 0, len - 1,p);
    delete[] p;
}

int main()
{
    srand(time(NULL));
    int arr[10];
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    MergeSort(arr, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
}