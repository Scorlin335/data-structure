#include <iostream>
#include <time.h>

// 选择排序也是两个循环嵌套,且无法优化,所以时间复杂度为O(n),空间为O(1).选择排序是不稳定的.

using namespace std;

void ChoiseSort(int arr[], int len)
{
    for (int i = 0;i<len-1;i++){
        int min = arr[i];
        int k = i;
        for (int j = i+1; j < len;j++){
            if(arr[j]<min){
                min = arr[j];
                k = j;
            }
        }
        if(arr[i]!=min){
            arr[k] = arr[i];
            arr[i] = min;
        }
    }
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
    ChoiseSort(arr, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
}