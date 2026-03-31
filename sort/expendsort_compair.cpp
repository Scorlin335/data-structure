#include <iostream>
#include <time.h>

using namespace std;

// 分割函数
int Partation(int arr[], int begin, int end)
{
    // 可以加入三数取中法进行优化
    int val = arr[begin];
    while (begin < end)
    {
        while (arr[end] > val && end > begin)
        {
            end--;
        }
        if (end > begin)
        {
            arr[begin] = arr[end];
            begin++;
        }
        while (arr[begin] < val && begin < end)
        {
            begin++;
        }
        if (begin < end)
        {
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
    // 可以加入最大递归层数后使用插入排序进行优化
    if (begin >= end)
    {
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

void Merge(int arr[], int begin, int mid, int end, int *p)
{
    // int *p = new int[end - begin + 1];
    int i = begin;
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= end)
    {
        if (arr[i] <= arr[j])
        {
            p[k++] = arr[i++];
        }
        else
        {
            p[k++] = arr[j++];
        }
    }
    while (i <= mid)
    {
        p[k++] = arr[i++];
    }
    while (j <= end)
    {
        p[k++] = arr[j++];
    }
    for (i = begin, j = 0; i <= end; i++, j++)
    {
        arr[i] = p[j];
    }
    // delete[] p;
}

// 函数重载
void MergeSort(int arr[], int begin, int end, int *p)
{
    if (begin >= end)
    {
        return;
    }
    int mid = (begin + end) / 2;
    // 先递
    MergeSort(arr, begin, mid, p);
    MergeSort(arr, mid + 1, end, p);
    // 再归,递之后的部分就是归的时候做的操作
    Merge(arr, begin, mid, end, p);
}

void MergeSort(int arr[], int len)
{
    int *p = new int[len];
    MergeSort(arr, 0, len - 1, p);
    delete[] p;
}

void HeapSort(int *arr, int len)
{
    for (int j = (len - 2) / 2; j >= 0; j--)
    {
        int i = j;
        int val = arr[i];
        while (i <= (len - 2) / 2)
        {
            int child = 2 * i + 1;
            if (arr[child] < arr[child + 1] && (child + 1) < len)
            {
                child++;
            }
            if (arr[child] > val)
            {
                arr[i] = arr[child];
                i = child;
            }
            else
            {
                break;
            }
        }
        arr[i] = val;
    }

    for (int k = len - 1;;)
    {
        int temp = arr[0];
        arr[0] = arr[k];
        arr[k] = temp;
        k--;
        if (k == 0)
        {
            break;
        }
        int i = 0;
        int val = arr[i];
        while (i <= (k + 1 - 2) / 2)
        {
            int child = 2 * i + 1;
            if (arr[child] < arr[child + 1] && (child + 1) <= k)
            {
                child++;
            }
            if (arr[child] > val)
            {
                arr[i] = arr[child];
                i = child;
            }
            else
            {
                break;
            }
        }
        arr[i] = val;
    }
}

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

int main()
{
    cout << RAND_MAX << endl;
    srand(time(NULL));
    int count = 100000000;
    int *arr = new int[count];
    int *brr = new int[count];
    int *crr = new int[count];
    int *drr = new int[count];
    for (int i = 0; i < count; i++)
    {
        int val = (int)((double)rand() / (RAND_MAX +1.0)*count+1);
        arr[i] = val;
        brr[i] = val;
        crr[i] = val;
        drr[i] = val;
    }
    clock_t begin, end;
    begin = clock();
    QuickSort(arr, count);
    end = clock();
    cout << "QuickSort: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
    begin = clock();
    MergeSort(brr, count);
    end = clock();
    cout << "MergeSort: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
    begin = clock();
    HeapSort(crr, count);
    end = clock();
    cout << "HeapSort: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
    begin = clock();
    ShellSort(drr, count);
    end = clock();
    cout << "ShellSort: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
    delete[] arr;
    delete[] brr;
    delete[] crr;
    delete[] drr;
}