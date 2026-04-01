#include <iostream>
#include <time.h>

//时间复杂度稳定在O(nlogn),每次下沉都是logn,下沉n次.空间就是O(1).
//不稳定

using namespace std;

void HeapSort_(int *arr,int len){
    int k = len - 1;
    while (k > 0){
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
        int temp = arr[0];
        arr[0] = arr[k];
        arr[k] = temp;
        len--;
        k = len - 1;
    }
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

        for (int k = len - 1; ;){
            int temp = arr[0];
            arr[0] = arr[k];
            arr[k] = temp;
            k--;
            if(k==0){
                break;
            }
            int i = 0;
            int val = arr[i];
            while (i <= (k+1 - 2) / 2)
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

int main(){
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
    HeapSort(arr, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
}