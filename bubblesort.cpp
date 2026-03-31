#include <iostream>
#include <time.h>

//冒泡排序复杂度O(n),因为是两个循环嵌套.冒泡排序是稳定的.

using namespace std;

void BubbleSort(int arr[],int len){
    for (int i = len - 1; i >= 0; i--)
    {
        bool flag = false;//对冒泡排序的一个简单小优化,如果一趟下来没有交换过,就说明数据已经有序了,直接终止
        for (int j = 0; j < i;j++){
            if(arr[j]>arr[j+1]){
                int temp=arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                flag = true;
            }
        }
        if(!flage){
            return;
        }
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
    BubbleSort(arr, 10);
    for (int i = 0; i < 10;i++){
        cout << arr[i] << " " ;
    }
}