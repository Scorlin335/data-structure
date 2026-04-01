#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h> //用于设置中文编码
using namespace std;

//双向链表节点
struct Node{
    Node(int data = 0)
        :data_(data)
        ,pre_(nullptr)
        ,next_(nullptr)
    {}
    int data_;
    Node *pre_;
    Node *next_;
};

//双向链表类
class DoubleLink{
    public:
        //头插法
        void InsertHead(int val){
            Node *newnode = new Node(val);
            newnode->next_ = head_->next_;
            newnode->pre_ = head_;
            if(head_->next_!=nullptr){
                head_->next_->pre_ = newnode;
            }
            head_->next_ = newnode;
        }
        //尾插法
        void InsertTail(int val){
            Node *newnode = new Node(val);
            Node *p = head_;
            while (p->next_!=nullptr)
            {
                p = p->next_;
            }
            p->next_ = newnode;
            newnode->pre_ = p;
        }
        //删除第一个值为val的节点
        void Remove(int val){
            Node *p = head_;
            while(p!=nullptr){
                p = p->next_;
                if(p!=nullptr && p->data_==val){
                    p->pre_->next_ = p->next_;
                    if (p->next_ != nullptr){
                        p->next_->pre_ = p->pre_;
                    }
                    delete p;
                    p = nullptr;
                    return;
                }
            }
        }
        // 删除所有值为val的节点
        void RemoveAll(int val){
            Node *p = head_;
            while (p != nullptr){
                p = p->next_;
                if (p != nullptr && p->data_ == val){
                    p->pre_->next_ = p->next_;
                    if (p->next_ != nullptr){
                        p->next_->pre_ = p->pre_;
                    }
                    Node *pre = p->pre_;
                    delete p;
                    p = pre;
                }
            }
        }
        //打印链表
        void Show(){
            Node *curnode = head_->next_;
            while (curnode!=nullptr)
            {
                cout << curnode->data_ << " ";
                curnode = curnode->next_;
            }
            cout << endl;
        }
    public:
        DoubleLink(){
            head_ = new Node();
        }
        ~DoubleLink(){
            Node *p = head_;
            while(head_!=nullptr){
                head_ = head_->next_;
                delete p;
                p = head_;
            }
        }
    private:
        Node *head_;
};

int main(){
    SetConsoleOutputCP(CP_UTF8); // 设置中文编码
    DoubleLink dlink;
    dlink.InsertHead(100);
    dlink.InsertHead(99);
    dlink.InsertHead(87);
    dlink.InsertHead(45);
    dlink.Show();
    dlink.InsertTail(77);
    dlink.InsertTail(87);
    dlink.InsertTail(87);
    dlink.Show();
    dlink.Remove(87);
    dlink.Show();
    dlink.RemoveAll(87);
    dlink.Show();
}