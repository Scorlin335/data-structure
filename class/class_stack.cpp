#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h> //用于设置中文编码
using namespace std;

//顺序栈,由数组实现
class SeqStack{
    public:
        void push(int val){
            if(mtop==mcap){
                expand(2 * mcap);
            }
            mpStack[mtop++] = val;
        }
        void pop(){
            if(mtop==0){
                throw "stack is empty!";
            }
            mtop--;
        }//出栈,但不返回元素,只是弹出一个元素
        int top()const{
            if (mtop == 0){
                throw "stack is empty!";
            }
            return mpStack[mtop-1];
        }//这个top是只读的,读元素但mtop不变
        bool empty()const{
            return mtop == 0;
        }
        int size()const{
            return mtop;
        }//返回栈内目前还有多少个元素
    private:
        void expand(int size){
            int *p = new int[size];
            memcpy(p, mpStack, mtop * sizeof(int));
            mcap = size;
            delete[] mpStack;
            mpStack = p;
        }//扩容函数,size为扩容后大小
    public:
        SeqStack(int size = 10)
            :mtop(0)
            ,mcap(size){
                mpStack = new int[mcap];
            }
        ~SeqStack(){
            delete []mpStack;
            mpStack = nullptr;//释放后注意处理野指针
        }
        //还应该写深拷贝函数,浅拷贝会出问题
    private:
        int *mpStack;//数组首地址
        int mtop;
        int mcap;
};

//链式栈,由链表实现,更慢一些,但内存分配灵活
class LinkStack{
    public:
        void push(int val){
            Node *newnode = new Node(val);
            newnode->next_ = head_->next_;
            head_->next_ = newnode;
            size_++;
        }
        void pop(){
            if(head_->next_==nullptr){
                throw "stack is empty!";
            }
            Node *p = head_->next_;
            head_->next_ = p->next_;
            delete p;
            size_--;
        }
        int top(){
            if (head_->next_ == nullptr){
                throw "stack is empty!";
            }
            return head_->next_->data_;
        }
        bool empty(){
            return size_ == 0;
        }
        int size(){
            return size_;
        }
    public:
        LinkStack()
        :size_(0){
            head_ = new Node();
        }
        ~LinkStack(){
            Node *p = head_;
            if(p!=nullptr){
                head_ = head_->next_;
                delete p;
                p = head_;
            }
        }
    private:
        struct Node{
            Node(int val=0):data_(val),next_(nullptr){}
            int data_;
            Node *next_;
        };
        Node *head_;
        int size_;
};

int main(){
    SetConsoleOutputCP(CP_UTF8); // 设置中文编码
    LinkStack s1,s2;
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int brr[] = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
    for(int v:arr){
        s1.push(v);
    }
    for (int v : brr)
    {
        s2.push(v);
    }
    while(!s1.empty()){
        cout << s1.top()<<" ";
        s1.pop();
    }
    cout << endl;
    while (!s2.empty())
    {
        cout << s2.top() << " ";
        s2.pop();
    }
    cout << endl;
    
    //对可能抛出异常的代码块尝试接受异常
    try{
        s1.pop();
    }catch (const char *msg){
        cerr << msg << endl;
    }
}