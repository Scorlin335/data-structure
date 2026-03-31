#include <iostream>

using namespace std;

class Deque{
public:
    //在队尾加入元素item
    void inject(int item)
    {
        if ((rear_ + 1) % cap_ == front_)
        {
            expand(2 * cap_);
        }
        pQue_[rear_] = item;
        rear_ = (rear_ + 1) % cap_;
    }
    //在队尾取出队尾值放入item,之后删除队尾元素
    void eject(int &item){
        if (front_ == rear_)
        {
            throw "queue is empty!";
        }
        item= pQue_[(rear_ - 1 + cap_) % cap_];
        rear_ = (rear_ - 1 + cap_) % cap_;
    }
    //在队首加入元素item
    void push(int item){
        if ((rear_ + 1) % cap_ == front_)
        {
            expand(2 * cap_);
        }
        front_ = (front_ - 1 + cap_) % cap_;
        pQue_[front_] = item;
    }
    // 在队首取出队尾值放入item,之后删除队首元素
    void pop(int &item)
    {
        item = pQue_[front_];
        if (front_ == rear_)
        {
            throw "queue is empty!";
        }
        front_ = (front_ + 1) % cap_;
    }
    bool empty()
    {
        return front_ == rear_;
    }
    int size()
    {
        if (rear_ >= front_)
        {
            return rear_ - front_;
        }
        else
        {
            return rear_ + cap_ - front_;
        }
    }

private:
    void expand(int nsize)
    {
        int *newp = new int[nsize];
        for (int i = 0, j = front_; j != rear_; j = (j + 1) % cap_, i++)
        {
            newp[i] = pQue_[j];
        }
        rear_ = size();
        front_ = 0;
        delete[] pQue_;
        pQue_ = newp;
        cap_ = nsize;
    }

public:
    Deque(int size = 10)
        : cap_(size), front_(0), rear_(0)
    {
        pQue_ = new int[size];
    }
    ~Deque()
    {
        delete[] pQue_;
        pQue_ = nullptr;
    }

private:
    int *pQue_; // 数组头指针
    int cap_;   // 数组容积
    int front_; // 队头下标
    int rear_;  // 队尾下一个位置的下标
};

int main(){
    Deque deq(10);
    for(int i = 0; i < 10; i++){
        deq.inject(i);
    }
    for (int i = 0; i < 5;i++){
        int item;
        deq.eject(item);
        cout << item << " ";
    }
    cout << endl;
    for (int i = 10; i < 15;i++){
        deq.push(i);
    }
    while(!deq.empty())
    {
        int item;
        deq.pop(item);
        cout << item << " ";
    }
    cout << endl;
}