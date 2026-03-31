#include<iostream>
#include<time.h>

using namespace std;

void ShellSort(int arr[], int len)
{
    for (int gap = len / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < len; i++)
        {
            int val = arr[i];
            int j = i - gap;
            for (; j >= 0; j -= gap)
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

void BubbleSort(int arr[], int len)
{
    for (int i = len - 1; i >= 0; i--)
    {
        bool flag = false; // 对冒泡排序的一个简单小优化,如果一趟下来没有交换过,就说明数据已经有序了,直接终止
        for (int j = 0; j < i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                flag = true;
            }
        }
        if (!flag)
        {
            return;
        }
    }
}

void ChoiseSort(int arr[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        int min = arr[i];
        int k = i;
        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < min)
            {
                min = arr[j];
                k = j;
            }
        }
        if (arr[i] != min)
        {
            arr[k] = arr[i];
            arr[i] = min;
        }
    }
}

int main(){
    srand(time(NULL));
    int count = 100000;
    int *arr = new int[count];
    int *brr = new int[count];
    int *crr = new int[count];
    int *drr = new int[count];
    for (int i = 0; i < count;i++){
        int val = rand() % count;
        arr[i] = val;
        brr[i] = val;
        crr[i] = val;
        drr[i] = val;
    }
    clock_t begin, end;
    begin = clock();
    BubbleSort(arr, count);
    end = clock();
    cout << "bubblesort: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
    begin = clock();
    ChoiseSort(brr, count);
    end = clock();
    cout << "ChoiseSort: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
    begin = clock();
    InsertSort(crr, count);
    end = clock();
    cout << "InsertSort: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
    begin = clock();
    ShellSort(drr, count);
    end = clock();
    cout << "ShellSort: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
    delete[] arr;
    delete[] brr;
    delete[] crr;
    delete[] drr;
}