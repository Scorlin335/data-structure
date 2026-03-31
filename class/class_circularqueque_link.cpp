#include <iostream>

using namespace std;

//链式队列
class Queue{
    public:
        void push(int val){
            Node *newnode = new Node(val);
            head_->pre_->next_ = newnode;
            newnode->pre_ = head_->pre_;
            newnode->next_ = head_;
            head_->pre_ = newnode;
            size_++;
        }
        void pop(){
            if(head_->next_==head_){
                throw "queue is empty!";
            }
            Node *d = head_->next_;
            head_->next_ = head_->next_->next_;
            head_->next_->pre_ = head_;
            delete d;
            size_--;
        }
        int front(){
            if(head_->next_==head_){
                throw "queue is empty!";
            }
            return head_->next_->data_;
        }
        int back(){
            if (head_->next_ == head_)
            {
                throw "queue is empty!";
            }
            return head_->pre_->data_;
        }
        bool empty(){
            if(head_->next_==head_){
                return true;
            }
            return false;
        }
        int size(){
            return size_;
        }
    public:
        Queue():size_(0){
            head_ = new Node();
            head_->next_ = head_;
            head_->pre_ = head_;
        }
        ~Queue(){
            Node *p = head_->next_;
            Node *d = p;
            while(p!=head_){
                p = p->next_;
                delete d;
                d = p;
            }
            delete head_;
            head_ = nullptr;
        }
    private:
        struct Node{
            Node(int data=0)
                :data_(data)
                ,next_(nullptr)
                ,pre_(nullptr)
            {}
            int data_;
            Node *next_;
            Node *pre_;
        };
        Node *head_;
        int size_;
};

int main(){
    Queue q1;
    for (int i = 0; i < 9; i++)
    {
        q1.push(i);
    }
    cout << q1.size() << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << q1.front() << " ";
        q1.pop();
    }
    cout << endl;
    for (int i = 9; i < 15; i++)
    {
        q1.push(i);
    }
    cout << q1.size() << endl;
    while (!q1.empty())
    {
        cout << q1.front() << " ";
        q1.pop();
    }
}