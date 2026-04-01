#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

class Array{
    private:
        int *mpArr;
        int mCap_;
        int mCur;
    public:
        Array(int size = 10) : mCap_(size), mCur(0)
        {
            mpArr = new int[size]();
        }
        ~Array(){
            delete[] mpArr;
            mpArr = nullptr;
        }
    public:
        //末尾增加元素O(1)
        void push_back(int val){
            if(mCur==mCap_){
                expand(mCap_ * 2);//O(n)
            }
            mpArr[mCur] = val;
            mCur++;
        }
        //末尾删除元素O(1)
        void pop_back(){
            if(mCur>0){
                mCur--;
            }else{
                return;
            }
        }
        //按位置增加元素O(n)
        void insert(int pos, int val){
            if(pos>=0&&pos<=mCur){
                if (mCur == mCap_)
                {
                    expand(mCap_ * 2);
                }
                for (int i = mCur - 1; i >= pos;i--){
                    mpArr[i + 1] = mpArr[i];
                }
                mpArr[pos] = val;
                mCur++;
            }else{
                return;
            }
        }
        //按位置删除元素O(n)
        void erase(int pos){
            if(pos<0||pos>=mCur){
                return;
            }
            for (int i = pos + 1; i < mCur;i++){
                mpArr[i - 1] = mpArr[i];
            }
            mCur--;
        }
        //元素查询O(n)
        int find(int val){
            for (int i = 0; i < mCur;i++){
                if(mpArr[i]==val){
                    return i;
                }
            }
            return -1;
        }
        //数组打印O(n)
        void show(){
            for (int i = 0; i < mCur; i++)
            {
                printf("%d ", mpArr[i]);
            }
            printf("\n");
        }
    private:
        void expand(int size){
            int *p = new int[size]();
            memcpy(p, mpArr, mCap_ * sizeof(int));
            delete[] mpArr;
            mpArr = p;
            mCap_ = size;
        }
};

int main(){
    Array arr(15);
    srand(time(0));
    for (int i = 0; i < 15;i++){
        arr.push_back(rand() % 100);
    }
    arr.show(); // 87 73 38 38 10 68 96 59 14 3 3 79 90 69 78
    arr.pop_back();
    arr.show(); // 87 73 38 38 10 68 96 59 14 3 3 79 90 69
    arr.insert(0, 100);
    arr.show(); // 100 87 73 38 38 10 68 96 59 14 3 3 79 90 69
    cout << arr.find(100) << endl; // 0
    arr.erase(arr.find(100));
    arr.show(); // 87 73 38 38 10 68 96 59 14 3 3 79 90 69
}