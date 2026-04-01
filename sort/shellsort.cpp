#include <iostream>
#include <time.h>

// 希尔排序可以看做是插入排序的优化,不断地分组插入排序使数据逐渐全局有序
//最坏O(n),平均O(n^1.3)

using namespace std;

//可以对比一下希尔排序和插入排序的代码差在哪里了
void ShellSort(int arr[], int len)
{
    for (int gap = len / 2; gap > 0;gap/=2){
        for (int i = gap; i < len; i++)
        {
            int val = arr[i];
            int j = i - gap;
            for (; j >= 0; j-=gap)
            {
                if (arr[j] <= val)
                {
                    break;
                }
                arr[j + gap] = arr[j];
            }
            arr[j + gap] = val;
        }
    }
}

void InsertSort(int arr[], int len)
{
    for (int i = 1; i < len; i++)
    {
        int val = arr[i];
        int j = i - 1;
        for (; j >= 0; j--)
        {
            if (arr[j] <= val)
            {
                break;
            }
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = val;
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
    ShellSort(arr, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
}