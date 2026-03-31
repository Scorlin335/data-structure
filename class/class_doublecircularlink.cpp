#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h> //用于设置中文编码
using namespace std;

// 双向循环链表节点
struct Node
{
    Node(int data = 0)
        : data_(data), pre_(nullptr), next_(nullptr)
    {}
    int data_;
    Node *pre_;
    Node *next_;
};

// 双向链表类
class DoubleCircularLink
{
public:
    // 头插法O(1)
    void InsertHead(int val)
    {
        Node *newnode = new Node(val);
        newnode->next_ = head_->next_;
        newnode->pre_ = head_;
        head_->next_->pre_ = newnode;
        head_->next_ = newnode;
    }
    // 尾插法O(1)
    void InsertTail(int val)
    {
        Node *newnode = new Node(val);
        head_->pre_->next_ = newnode;
        newnode->pre_ = head_->pre_;
        newnode->next_ = head_;
        head_->pre_ = newnode;
    }
    // 删除第一个值为val的节点
    void Remove(int val)
    {
        Node *p = head_->next_;
        while (p != head_)
        {
            if (p != head_ && p->data_ == val)
            {
                p->pre_->next_ = p->next_;
                p->next_->pre_ = p->pre_;
                delete p;
                p = nullptr;
                return;
            }
            p = p->next_;
        }
    }
    // 删除所有值为val的节点(没改成循环的)
    // void RemoveAll(int val)
    // {
    //     Node *p = head_;
    //     while (p != nullptr)
    //     {
    //         p = p->next_;
    //         if (p != nullptr && p->data_ == val)
    //         {
    //             p->pre_->next_ = p->next_;
    //             if (p->next_ != nullptr)
    //             {
    //                 p->next_->pre_ = p->pre_;
    //             }
    //             Node *pre = p->pre_;
    //             delete p;
    //             p = pre;
    //         }
    //     }
    // }
    // 打印链表
    void Show()
    {
        Node *curnode = head_->next_;
        while (curnode != head_)
        {
            cout << curnode->data_ << " ";
            curnode = curnode->next_;
        }
        cout << endl;
    }

public:
    DoubleCircularLink()
    {
        head_ = new Node();
        head_->pre_ = head_;
        head_->next_ = head_;
    }
    ~DoubleCircularLink()
    {
        Node *p = head_->next_;
        while (p!= head_)
        {
            head_->next_ = p->next_;
            p->next_->pre_ = head_;
            delete p;
            p = head_->next_;
        }
        delete head_;
        p = nullptr;
        head_ = nullptr;
    }

private:
    Node *head_;
};

int main()
{
    SetConsoleOutputCP(CP_UTF8); // 设置中文编码
    DoubleCircularLink dlink;
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
    // dlink.RemoveAll(87);
    // dlink.Show();
}