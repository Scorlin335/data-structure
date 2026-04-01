#include <iostream>
#include <time.h>

// 插入排序是在数据趋于有序时所有排序算法中效率最好的

using namespace std;

void InsertSort_(int arr[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        int j = i + 1;
        for (int k = i; k >= 0; k--)
        {
            if (arr[k] <= arr[j])
            {
                int temp = arr[j];
                for (int m = j; m > k + 1; m--)
                {
                    arr[m] = arr[m - 1];
                }
                arr[k + 1] = temp;
                break;
            }
        }
        if (arr[0] > arr[j])
        {
            int temp = arr[j];
            for (int m = j; m > 0; m--)
            {
                arr[m] = arr[m - 1];
            }
            arr[0] = temp;
        }
    }
}

void InsertSort(int arr[],int len){
    for (int i = 1; i < len;i++){
        int val = arr[i];
        int j = i - 1;
        for (; j >= 0;j--){
            if(arr[j]<=val){
                break;
            }
            arr[j+1] = arr[j];
        }
        arr[j+1] = val;
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
    InsertSort(arr, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
}