#include <iostream>
#include <time.h>
#include <functional>
//堆实现的优先级序列
using namespace std;

class PriorityQueue{
    public:
        using Comp = function<bool(int, int)>;
    public:
        PriorityQueue(int val=20,Comp comp=greater<int>()):
            size_(0),
            cap_(val),
            comp_(comp){
            que_ = new int[cap_];
            }
        ~PriorityQueue(){
            delete[] que_;
            que_ = nullptr;
        }
    public:
        void push(int val){
            if(size_==cap_){
                int *p = new int[2 * cap_];
                memcpy(p, que_, sizeof(int) * cap_);//用为这里存储的知识整数,不涉及地址的深拷贝,所以可以直接用这个
                delete[] que_;
                que_ = p;
                cap_ *= 2;
            }
            if(size_==0){
                que_[size_] = val;
                size_++;
            }else{
                for (int i = size_; i > 0;){
                    int f = (i - 1) / 2;//找到子节点的父亲
                    if(comp_(val,que_[f])){
                        que_[i] = que_[f];
                        i = f;
                        if(i==0){
                            que_[i] = val;
                            size_++;
                        }
                    }else{
                        que_[i] = val;
                        size_++;
                        break;
                    }
                }
            }
        }
        void pop(){
            if(size_==0){
                throw "container is empty";
            }else{
                size_--;
                int val = que_[size_];
                for (int i = 0;i<=(size_-2)/2;){
                    int child = 2 * i + 1;
                    if(comp_(que_[child+1],que_[child])&&child+1<size_){
                        child++;
                    }
                    if (comp_(que_[child], val))
                    {
                        que_[i] = que_[child];
                        i = child;
                    }else{
                        que_[i] = val;
                        break;
                    }
                    if (i > (size_ - 2) / 2){
                        que_[i] = val;
                    }
                }
            }
        }
        int top(){
            if (size_ == 0)
            {
                throw "container is empty";
            }else{
                return que_[0];
            }
        }
        bool empty(){
            return size_ == 0;
        }
        int size(){
            return size_;
        }
    private:
        int *que_;
        int size_;
        int cap_;
        Comp comp_;
};

int main(){
    srand(time(NULL));
    //大根堆(默认)
    PriorityQueue que(10);
    for (int i = 0; i < 20;i++){
        int val = rand() % 100;
        que.push(val);
        cout << val << " ";
    }
    cout << endl;
    while(!que.empty()){
        cout << que.top() << " ";
        que.pop();
    }
    cout << endl;
    //小跟堆(自己写比较函数)
    PriorityQueue ques(10,[](int a,int b){return a<b;});
    for (int i = 0; i < 20; i++)
    {
        int val = rand() % 100;
        ques.push(val);
        cout << val << " ";
    }
    cout << endl;
    while (!ques.empty())
    {
        cout << ques.top() << " ";
        ques.pop();
    }
}