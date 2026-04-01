#include<iostream>
#include<stdlib.h>
#include<time.h>
#include <windows.h> //用于设置中文编码
using namespace std;

struct Node{
    Node(int data=0):data_(data),next_(nullptr){}
    int data_;
    Node *next_;
};

//单向链表
class Clink{
    public:
        //普通尾插节点O(n)
        void InsertTail_on(int val){
            Node *curnode = head_;
            while(curnode->next_!=nullptr){
                curnode = curnode->next_;
            }
            Node *newnode = new Node(val);
            curnode->next_ = newnode;
            num_++;
            tail_ = tail_->next_;
        }
        //使用尾节点成员变量tail_的尾插,时间复杂度O(1)
        void InsertTail_o1(int val)
        {
            Node *newnode = new Node(val);
            tail_->next_ = newnode;
            num_++;
            tail_ = tail_->next_;
        }
        //头插节点O(1)
        void InsertHead(int val){
            Node *newnode = new Node(val);
            newnode->next_ = head_->next_;
            head_->next_ = newnode;
            num_++;
            if(tail_->next_!=nullptr){
                tail_ = tail_->next_;
            }
        }
        //删除第一个值为val的节点0(n)
        void Remove(int val){
            Node *prenode = head_;
            Node *curnode = prenode->next_;
            while(curnode!=nullptr){
                if(curnode->next_==tail_&&tail_->data_==val){
                    delete tail_;
                    num_--;
                    tail_ = curnode;
                    return;
                }
                if(curnode->data_==val){
                    prenode->next_ = curnode->next_;
                    delete curnode;
                    num_--;
                    return;
                }else{
                    prenode = curnode;
                    curnode = curnode->next_;
                }
            }
        }
        //删除所有值为val的节点O(n)
        void RemoveAll(int val)
        {
            Node *prenode = head_;
            Node *curnode = prenode->next_;
            while (curnode != nullptr)
            {
                if (curnode->next_ == tail_ && tail_->data_ == val)
                {
                    delete tail_;
                    num_--;
                    tail_ = curnode;
                    curnode->next_ = nullptr;
                    return;
                }
                if (curnode->data_ == val)
                {
                    prenode->next_ = curnode->next_;
                    delete curnode;
                    num_--;
                    //重置指针curnode
                    curnode = prenode->next_;
                }
                else
                {
                    prenode = curnode;
                    curnode = curnode->next_;
                }
            }
        }
        //返回val是否在链表中
        bool find(int val){
            Node *curnode = head_->next_;
            while(curnode!=nullptr){
                if(curnode->data_==val){
                    return true;
                }
                curnode = curnode->next_;
            }
            return false;
        }
        //链表原地逆序
        void Reverse(){
            tail_ = head_->next_;
            Node *curnode = head_->next_;
            Node *nextnode = curnode->next_;
            head_->next_ = nullptr;
            while(curnode!=nullptr){
                curnode->next_ = head_->next_;
                head_->next_ = curnode;
                curnode = nextnode;
                if(curnode!=nullptr)
                    nextnode = nextnode->next_;
            }
        }
        //输出倒数第k个节点中的数值(不使用num_,使用双指针)
        bool daiding(int k,int& val){
            if(k<=0){
                return false;
            }
            Node *quick = head_;
            Node *slow = head_;
            for (int i = 0; quick != nullptr && i < k;i++)
            {
                quick = quick->next_;
            }
            if(quick==nullptr){
                return false;
            }
            while (quick != nullptr){
                slow = slow->next_;
                quick = quick->next_;
            }
            val=slow->data_;
            return true;
        }
        //删除倒数第k个节点
        void RemoveKthFromEnd(int k){
            if(k>num_){
                return;
            }
            Node *curnode = head_;
            for (int i = 0; i < num_ - k ;i++){
                curnode = curnode->next_;
            }
            Node *delnode = curnode->next_;
            if(k==num_){
                tail_ = curnode;
            }
            curnode->next_ = curnode->next_->next_;
            delete delnode;
            delnode = nullptr;
            num_--;
        }
        //访问有效节点个数
        int getnum(){
            return num_;
        }
        //访问尾节点的值
        int gettail(){
            return tail_->data_;
        }
        //打印链表
        void Show(){
            Node *curnode = head_->next_;
            while(curnode!=nullptr){
                cout << curnode->data_ << " ";
                curnode = curnode->next_;
            }
            cout << endl;
        }
    public:
        Clink(){
            head_ = new Node();
            tail_ = head_;
            num_ = 0;
        }
        ~Clink(){
            Node *curnode, *nextnode;
            curnode = head_;
            nextnode = curnode->next_;
            while(curnode!=nullptr){
                delete curnode;
                curnode = nextnode;
                if(nextnode!=nullptr)
                    nextnode = nextnode->next_;
            }
            head_ = nullptr;
            tail_ = nullptr;
        }
    private:
        Node *head_;
        Node *tail_;    //尾节点指针
        int num_;     // 节点个数(不算头节点)
        friend void MergeLink(Clink &link1, Clink &link2);
        friend bool IsLinkHasCircle(Node *link, int &val);
        friend void RotateRight(int k, Clink &link);
        friend void RotateRight_(int k, Clink &link);//已经不用了
        friend void YSF(int m, Clink &link);
};

//将两个递增链表融合成一个递增连表
void MergeLink(Clink &link1,Clink &link2){
    Node *p1 = link1.head_->next_;
    Node *p2 = link2.head_->next_;
    Node *last=link1.head_;
    while(p1!=nullptr&&p2!=nullptr){
        if(p1->data_<p2->data_){
            last->next_ = p1;
            p1 = p1->next_;
            last = last->next_;
        }else{
            last->next_ = p2;
            p2 = p2->next_;
            last = last->next_;
        }
    }
    if (p1 == nullptr)
    {
        last->next_ = p2;
    }
    if (p2 == nullptr)
    {
        last->next_ = p1;
    }
    link2.head_ = link1.head_;
}

//判断链表是否有环,如果有环则返回环起点所储存的数值
bool IsLinkHasCircle(Node *link,int &val){
    Node *quick = link;
    Node *slow = link;
    do{
        if(quick==nullptr||quick->next_==nullptr){
            return false;
        }
        quick=quick->next_->next_;
        slow = slow->next_;
    } while (quick != slow);
    quick = link;
    while(quick!=slow){
        quick = quick->next_;
        slow = slow->next_;
    }
    val = quick->data_;
    return true;
}

//判断链表是否相交,如果相交则返回交点所存储的数值
bool IsLinkHasMerge(Node *link1,Node *link2,int &val){
    Node *p1 = link1;
    Node *p2 = link2;
    int len1 = 0, len2 = 0;
    while(p1->next_!=nullptr){
        p1 = p1->next_;
        len1++;
    }
    while (p2->next_ != nullptr)
    {
        p2 = p2->next_;
        len2++;
    }
    int differ = 0;
    p1 = link1;
    p2 = link2;
    if(len1>len2){
        differ = len1 - len2;
        for (int i = 0; i < differ;i++){
            p1 = p1->next_;
        }
    }else{
        differ = len2 - len1;
        for (int i = 0; i < differ; i++)
        {
            p2 = p2->next_;
        }
    }
    while(p1!=nullptr&&p2!=nullptr){
        if(p1==p2){
            val = p1->data_;
            return true;
        }
        p1 = p1->next_;
        p2 = p2->next_;
    }
    return false;
}

//旋转链表 例:k=1时, 1-2-3-4=>4-1-2-3
void RotateRight_(int k, Clink &link){
    k = k % link.num_;
    Node *start = link.head_->next_;
    link.head_->next_ = nullptr;
    link.tail_ = link.head_;
    Node *last = link.head_;
    for (int i = 0; i < link.num_ - k; i++)
    {
        last->next_ = start;
        last = last->next_;
        link.tail_ = last;
        start = start->next_;
        last->next_ = nullptr;
    }
    last = link.head_;
    Node *end = last->next_;
    last->next_ = start;
    while(start->next_!=nullptr){
        start = start->next_;
    }
    start->next_ = end;
}
//更好的逻辑,可以直接连成环
void RotateRight(int k, Clink &link){
    k %= link.num_;
    Node *p1 = link.head_;
    for (int i = 0; i < link.num_ - k;i++){
        p1 = p1->next_;
    }
    link.tail_->next_ = link.head_->next_;
    link.head_->next_ = p1->next_;
    link.tail_ = p1;
    link.tail_->next_ = nullptr;
}

//约瑟夫环问题(此函数会将单向链表连成单向循环链表,一旦调用,则传入的link的部分成员函数再不能使用!!!!)
//这个只是为了临时做题,没有实用意义
void YSF(int m, Clink &link){
    link.tail_->next_ = link.head_->next_;//连成环了
    Node *curnode = link.head_->next_;
    Node *prenode = link.head_;
    while(curnode!=curnode->next_){
        for (int i = 0; i < m - 1; i++)
        {
            curnode = curnode->next_;
            prenode = prenode->next_;
        }
        cout << curnode->data_ << " ";
        prenode->next_ = prenode->next_->next_;
        if(curnode==link.tail_){
            link.tail_ = prenode;
        }
        if (curnode == link.head_->next_)
        {
            link.head_->next_ = prenode->next_;
        }
        link.tail_->next_ = link.head_->next_;
        delete curnode;
        link.num_--;
        curnode = prenode->next_;
    }
    cout << curnode->data_ << endl;
    delete curnode;
    link.num_--;
    link.tail_ = link.head_;
    link.head_->next_ = nullptr;
    curnode = nullptr;
    prenode = nullptr;
}

int main111()
{
    SetConsoleOutputCP(CP_UTF8); // 设置中文编码
    Clink link;
    srand(time(0));
    for (int i = 0; i < 10;i++){
        int val = rand() % 100;
        cout << val << " ";
        link.InsertHead(val);
    }
    cout << endl;
    link.InsertTail_o1(100);
    link.InsertTail_o1(999);
    link.InsertTail_o1(100);
    link.Show();
    link.RemoveAll(100);
    link.Show();
    cout << link.find(999)<<endl;
    link.Reverse();
    link.Show();
    // int kval;
    // if(link.daiding(4,kval)){
    //     cout << kval << endl;
    // };
    cout << link.getnum() << " " << link.gettail() << endl;
    link.RemoveKthFromEnd(4);
    link.Show();
    cout << link.getnum() << " " << link.gettail() << endl;
    RotateRight(0, link);
    link.Show();
    cout << link.getnum() << " " << link.gettail() << endl;
}

int main222(){
    SetConsoleOutputCP(CP_UTF8); // 设置中文编码
    Clink link1, link2;
    int arr[] = {2, 23, 25, 38, 48, 59};
    int brr[] = {14, 28, 43, 45, 67};
    for(int i:arr){
        link1.InsertTail_o1(i);
    }
    for (int i : brr)
    {
        link2.InsertTail_o1(i);
    }
    link1.Show();
    link2.Show();
    MergeLink(link1, link2);
    link1.Show();
    link2.Show();
}

int main333(){
    SetConsoleOutputCP(CP_UTF8); // 设置中文编码
    Node head;
    Node n1(25), n2(67), n3(32), n4(18);
    head.next_ = &n1;
    n1.next_ = &n2;
    n2.next_ = &n3;
    n3.next_ = &n4;
    n4.next_ = &n4;
    int n;
    if(IsLinkHasCircle(&head,n)){
        cout << n << endl;
    }
    cout << "运行结束" << endl;
}

int main444()
{
    SetConsoleOutputCP(CP_UTF8); // 设置中文编码
    Node head1;
    Node n1(25), n2(67), n3(32), n4(18);
    head1.next_ = &n1;
    n1.next_ = &n2;
    n2.next_ = &n3;
    n3.next_ = &n4;
    n4.next_ = nullptr;
    Node head2;
    Node n5(26), n6(68);
    head2.next_ = &n5;
    n5.next_ = &n6;
    n6.next_ = &n3;
    int n;
    if(IsLinkHasMerge(&head1,&head2,n)){
        cout << n << endl;
    }
    cout << "运行完毕" << endl;
}

int main(){
    Clink link;
    for (int i = 1; i <= 6;i++){
        link.InsertTail_o1(i);
    }
    link.Show();
    cout << link.getnum() << " " << link.gettail() << endl;
    YSF(2, link);
    cout << link.getnum() << " " << link.gettail() << endl;
}