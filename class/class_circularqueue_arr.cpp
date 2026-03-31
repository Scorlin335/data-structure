#include <iostream>

using namespace std;

// 环形数组队列(开n个空间可以存n-1个元素)
class Queue{
    public:
        void push(int val){
            if ((rear_ + 1) % cap_==front_){
                expand(2 * cap_);
            }
            pQue_[rear_] = val;
            rear_ = (rear_ + 1) % cap_;
        }
        void pop(){
            if(front_==rear_){
                throw "queue is empty!";
            }
            front_ = (front_ + 1) % cap_;
        }
        int front(){
            if (front_ == rear_)
            {
                throw "queue is empty!";
            }
            return pQue_[front_];
        }
        int back(){
            if (front_ == rear_)
            {
                throw "queue is empty!";
            }
            return pQue_[(rear_ - 1 + cap_) % cap_]; // 注意这里的写法,只是(rear_ - 1) % cap_处理不了rear_=0的情况
        }
        bool empty(){
            return front_ == rear_;
        }
        int size(){
            if(rear_>=front_){
                return rear_ - front_;
            }else{
                return rear_ + cap_ - front_;
            }
        }
    private:
        void expand(int nsize){
            int *newp = new int[nsize];
            for (int i = 0, j = front_; j != rear_;j=(j+1)%cap_,i++){
                newp[i] = pQue_[j];
            }
            rear_ = size();
            front_ = 0;
            delete[] pQue_;
            pQue_ = newp;
            cap_ = nsize;
        }
    public:
        Queue(int size=10)
            :cap_(size)
            ,front_(0)
            ,rear_(0){
                pQue_ = new int[size];
            }
        ~Queue(){
            delete[] pQue_;
            pQue_ = nullptr;
        }
    private:
        int *pQue_; //数组头指针
        int cap_;   //数组容积
        int front_; //队头下标
        int rear_;  //队尾下一个位置的下标
};

int main(){
    Queue q1;
    for (int i = 0; i < 9;i++){
        q1.push(i);
    }
    cout << q1.size() << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << q1.front() << " ";
        q1.pop();
    }
    cout << endl;
    for (int i = 9; i < 15;i++){
        q1.push(i);
    }
    cout << q1.size() << endl;
    while(!q1.empty()){
        cout << q1.front() << " ";
        q1.pop();
    }
}