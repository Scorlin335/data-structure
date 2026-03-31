#include <iostream>
#include <time.h>

//不稳定,平均和最好时间复杂度O(nlogn),空间复杂度O(logn)~O(n),最差时间复杂度O(n^2)
using namespace std;

//自己写的版本
void QuickSort_(int arr[], int begin, int end){
    if(begin>=end){
        return;
    }
    int pb = begin;
    int pe = end;
    int val = arr[begin];
    int flag = 0;
    while(begin<end){
        if(flag==0){
            while (arr[end] >= val&&end>begin)
            {
                end--;
            }
            if (begin == end)
            {
                break;
            }
            arr[begin] = arr[end];
            begin++;
            flag = 1;
            continue;
        }else{
            while (arr[begin] <= val&&begin<end)//=?
            {
                begin++;
            }
            if (begin == end)
            {
                break;
            }
            arr[end] = arr[begin];
            end--;
            flag = 0;
            continue;
        }
    }
    arr[begin] = val;
    QuickSort_(arr, pb, begin-1);
    QuickSort_(arr, begin+1,pe);
}

//分割函数
int Partation(int arr[], int begin, int end){
    //可以加入三数取中法进行优化
    int val = arr[begin];
    while(begin<end){
        while(arr[end]>val&&end>begin){
            end--;
        }
        if(end>begin){
            arr[begin] = arr[end];
            begin++;
        }
        while (arr[begin] < val && begin < end) {
            begin++;
        }
        if(begin<end){
            arr[end] = arr[begin];
            end--;
        }
    }
    arr[begin] = val;
    return begin;
}

// 函数重载
void QuickSort(int arr[], int begin, int end)
{
    //可以加入最大递归层数后使用插入排序进行优化
    if(begin>=end){
        return;
    }
    int pos = Partation(arr, begin, end);
    QuickSort(arr, begin, pos - 1);
    QuickSort(arr, pos + 1, end);
}

void QuickSort(int arr[], int len)
{
    QuickSort(arr, 0, len - 1);
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
    QuickSort(arr, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
}