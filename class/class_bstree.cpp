#include <iostream>
#include <functional>
#include <stack>
#include <deque>
#include <vector>
#include <windows.h>
#include <functional>
#include <utility>//pair在里面

using namespace std;

/*
如果想要传入自定义的比较函数,可以用这个格式
#include <functional>
BSTree<int, std::function<bool(int,int)>> tree(
    [](int a, int b) { return a > b; }
);
*/

template <typename T, typename Compare = less<T>>

class BSTree
{
private:
    struct Node
    {
        Node(T data = T())
            : data_(data), left_(nullptr), right_(nullptr)
        {
        }
        T data_;
        Node *left_;
        Node *right_;
    };
    Node *root_;
    Compare comp_;

public:
    // 非递归插入节点
    void n_insert(const T &val)
    {
        // 如果根节点为空,则产生根节点
        if (root_ == nullptr)
        {
            root_ = new Node(val);
            return;
        }
        // 如果根节点已有,生成新节点
        Node *parent = nullptr;
        Node *curnode = root_;
        // 寻找位置(不插入相同值的节点)
        while (curnode != nullptr)
        {
            if (comp_(val, curnode->data_))
            {
                parent = curnode;
                curnode = curnode->left_;
                continue;
            }
            else if (comp_(curnode->data_, val))
            {
                parent = curnode;
                curnode = curnode->right_;
            }
            else
            {
                return; // 不插入重复值
            }
        }
        curnode = new Node(val);
        // 将新节点插入到遍历出的parent后
        if (comp_(val, parent->data_))
        {
            parent->left_ = curnode;
        }
        else
        {
            parent->right_ = curnode;
        }
    }
    // 递归插入节点接口
    void insert(const T &val)
    {
        root_ = insert(root_, val);
    }
    // 非递归删除节点
    void n_erase(const T &val)
    {
        // 如果根节点为空,报错
        if (root_ == nullptr)
        {
            throw "the tree is empty!";
        }
        Node *curnode = root_;
        Node *parent = nullptr;
        // 找到要删除的节点
        while (curnode != nullptr)
        {
            if (comp_(val, curnode->data_))
            {
                parent = curnode;
                curnode = curnode->left_;
                continue;
            }
            else if (comp_(curnode->data_, val))
            {
                parent = curnode;
                curnode = curnode->right_;
            }
            else
            {
                break;
            }
        }
        // 如果没有找到
        if (curnode == nullptr)
        {
            throw "did not find the value!";
        }
        // 开始删除:如果目标节点为双支节点,则把目标节点的数值换成其左子树的最大节点的值(或者右子树最小节点的值),然后删掉左子树的最大节点(右子树最小节点)
        if (curnode->left_ != nullptr && curnode->right_ != nullptr)
        {
            parent = curnode;
            Node *nextnode = curnode->left_;
            while (nextnode->right_ != nullptr)
            {
                parent = nextnode;
                nextnode = nextnode->right_;
            }
            curnode->data_ = nextnode->data_;
            curnode = nextnode;
        }
        // 统一处理删除末尾/单支节点以及双支节点的后半部分
        Node *child = curnode->left_;
        if (child == nullptr)
        {
            child = curnode->right_;
        }
        if (parent == nullptr)
        {
            delete root_;
            root_ = child;
            return;
        }
        if (parent->left_ == curnode)
        {
            parent->left_ = child;
        }
        else
        {
            parent->right_ = child;
        }
        delete curnode;
        // 下面是自己一开始写的版本
        //  if (comp_(parent->data_, curnode->data_)){
        //      if(curnode->left_==nullptr){
        //          parent->right_ = curnode->right_;
        //      }else{
        //          parent->right_ = curnode->left_;
        //      }
        //      delete curnode;
        //  }else{
        //      if(curnode->left_==nullptr){
        //          parent->left_ = curnode->right_;
        //      }else{
        //          parent->left_ = curnode->left_;
        //      }
        //      delete curnode;
        //  }
    }
    // 递归删除节点
    void erase(const T &val)
    {
        root_ = erase(root_, val);
    }
    // 非递归查询
    bool n_find(const T &val)
    {
        Node *curnode = root_;
        while (curnode != nullptr)
        {
            if (comp_(val, curnode->data_))
            {
                curnode = curnode->left_;
                continue;
            }
            else if (comp_(curnode->data_, val))
            {
                curnode = curnode->right_;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
    // 递归查询
    bool find(const T &val)
    {
        return nullptr != find(root_, val);
    }
    // 递归前序遍历接口 VLR
    void preOrder()
    {
        cout << "preOreder: ";
        preOrder(root_);
        cout << endl;
    }
    // 非递归前序遍历(使用stack)
    void n_preOrder()
    {
        cout << "n_preOrder: ";
        stack<Node *> s;
        // 下面是老师写的版本,更清晰
        if (root_ == nullptr)
        {
            return;
        }
        s.push(root_);
        while (!s.empty())
        {
            Node *cur = s.top();
            s.pop();
            cout << cur->data_ << " "; // v
            if (cur->right_ != nullptr)
            {
                s.push(cur->right_); // R
            }
            if (cur->left_ != nullptr)
            {
                s.push(cur->left_); // L
            }
        }
        // 下面是自己写的版本,也是对的但不够清晰
        //  Node *curnode = root_;
        //  while(curnode!=nullptr||!s.empty()){
        //      if (curnode == nullptr && !s.empty())
        //      {
        //          curnode = s.top();
        //          s.pop();
        //          continue;
        //      }
        //      if (curnode->right_ != nullptr)
        //      {
        //          s.push(curnode->right_);
        //      }
        //      cout << curnode->data_ << " ";
        //      curnode = curnode->left_;
        //  }
        cout << endl;
    }
    // 递归中序遍历接口 LVR(使用less比较器时是递增的)
    void inOrder()
    {
        cout << "inOreder: ";
        inOrder(root_);
        cout << endl;
    }
    // 变向递归中序遍历接口 RVL(和正常的中序遍历正好是倒序,可以用来求倒数第k个节点)
    void _inOrder()
    {
        cout << "_inOreder: ";
        _inOrder(root_);
        cout << endl;
    }
    // 非递归中序遍历(使用stack)
    void n_inOrder()
    {
        cout << "n_inOrder: ";
        stack<Node *> s;
        if (root_ == nullptr)
        {
            return;
        }
        s.push(root_);
        // //原始版本,更好理解
        // Node *cur = root_->left_;
        // while(cur!=nullptr){
        //     s.push(cur);
        //     cur = cur->left_;
        // }
        // while(!s.empty()){
        //     cur = s.top();
        //     s.pop();
        //     cout << cur->data_ << " ";
        //     cur = cur->right_;
        //     while (cur != nullptr){
        //         s.push(cur);
        //         cur = cur->left_;
        //     }
        // }
        // 优化后的版本,尽量不重复代码
        Node *cur = root_->left_;
        if (cur != nullptr)
        {
            s.push(cur);
            cur = cur->left_;
        }
        while (!s.empty() || cur != nullptr)
        {
            if (cur != nullptr)
            {
                s.push(cur);
                cur = cur->left_;
            }
            else
            {
                cur = s.top();
                s.pop();
                cout << cur->data_ << " ";
                cur = cur->right_;
            }
        }
        cout << endl;
    }
    // 递归后序遍历接口 LRV
    void postOrder()
    {
        cout << "postOreder: ";
        postOrder(root_);
        cout << endl;
    }
    // 非递归后序遍历
    void n_postOrder()
    {
        // 其实就是前序遍历反过来,可以先写前序遍历然后放到栈里再出栈
        cout << "n_postOrder: ";
        stack<Node *> s;
        stack<Node *> r;
        if (root_ == nullptr)
        {
            return;
        }
        s.push(root_);
        while (!s.empty())
        {
            Node *cur = s.top();
            s.pop();
            r.push(cur); // v
            if (cur->left_ != nullptr)
            {
                s.push(cur->left_); // L
            }
            if (cur->right_ != nullptr)
            {
                s.push(cur->right_); // R
            }
        }
        while (!r.empty())
        {
            Node *cur = r.top();
            cout << cur->data_ << " ";
            r.pop();
        }
        cout << endl;
    }
    // 递归层序遍历接口
    void levelOrder()
    {
        int h = high();
        cout << "levelOrder: ";
        for (int i = 0; i < h; i++)
        {
            levelOrder(root_, i);
        }
        cout << endl;
    }
    // 非递归层序遍历
    void n_levelOrder()
    {
        cout << "n_levelOrder: ";
        if (root_ == nullptr)
        {
            return;
        }
        deque<Node *> dqu;
        Node *cur = root_;
        dqu.push_back(cur);
        while (!dqu.empty())
        {
            cur = dqu.front();
            dqu.pop_front();
            cout << cur->data_ << " ";
            if (cur->left_ != nullptr)
            {
                dqu.push_back(cur->left_);
            }
            if (cur->right_ != nullptr)
            {
                dqu.push_back(cur->right_);
            }
        }
        cout << endl;
    }

    // 递归求二叉树高度接口
    int high()
    {
        return high(root_);
    }
    // 递归求二叉树节点个数
    int number()
    {
        return number(root_);
    }
    // 非递归找出数中大于等于i小于等于j的数据返回到vector中
    //  注意,如果更换比较器这个函数需要重写,主要是调整左和右的选择
    void n_findValues(vector<T> &vec, const T &i, const T &j)
    {
        stack<Node *> s;
        if (root_ == nullptr)
        {
            return;
        }
        s.push(root_);
        Node *cur = root_->left_;
        if (cur != nullptr)
        {
            s.push(cur);
            cur = cur->left_;
        }
        while (!s.empty() || cur != nullptr)
        {
            if (cur != nullptr)
            {
                s.push(cur);
                cur = cur->left_;
            }
            else
            {
                cur = s.top();
                s.pop();
                if (cur->data_ > j)
                {
                    return; // 再往下找下去肯定越来越大,这里已经不符合了,所以直接终止
                }
                if (cur->data_ >= i)
                {
                    vec.push_back(cur->data_);
                }
                cur = cur->right_;
            }
        }
        cout << endl;
    }
    // 递归找出数中大于等于i小于等于j的数据返回到vector中
    // 注意,如果更换比较器这个函数需要重写,主要是调整左和右的选择
    void findValues(vector<T> &vec, const T &i, const T &j)
    {
        findValues(root_, vec, i, j);
    }
    // 递归判断一颗二叉树是否为二叉树
    bool isBSTree()
    {
        Node *pre = nullptr;
        return isBSTree(root_, pre);
    }
    // 判断另一棵树是否是这一棵的的子树(当前树在那一支上的数据可以比子树多)
    bool isChildTree(BSTree<T, Compare> &child)
    {
        if (child.root_ == nullptr)
        {
            return true;
        }
        Node *curnode = root_;
        while (curnode != nullptr && (comp_(curnode->data_, child.root_->data_) || comp_(child.root_->data_, curnode->data_)))
        {
            if (comp_(curnode->data_, child.root_->data_))
            {
                curnode = curnode->right_;
                continue;
            }
            else
            {
                curnode = curnode->left_;
            }
        }
        if (curnode == nullptr)
        {
            return false;
        }
        return isChildTree(curnode, child.root_); // 见下方递归部分
    }
    // 找出两个节点的最近公共祖先节点(默认两个节点已经在树上,如果没找到就返回nullptr)
    Node *getLCA(const T &i, const T &j)
    {
        return getLCA(root_, i, j);
    }
    // 镜像翻转(将一课二叉树以树外垂直树干一条直线为轴镜像翻转)
    // 注意,镜像翻转后的树不再是符合最开始定义时标准的二叉树!
    void mirror01()
    {
        mirror01(root_);
    }
    // 镜像对称(判断一颗二叉树是否以根为轴左右对称)(没测试过)
    bool mirror02()
    {
        if (root_ == nullptr)
        {
            return true;
        }
        if (root_->left_ == nullptr && root_->right_ == nullptr)
        {
            return true;
        }
        if (root_->left_ == nullptr || root_->right_ == nullptr)
        {
            return false;
        }
        return mirror02(root_->left_, root_->right_);
    }
    // 重建二叉树(只对空二叉树使用)(需要提供前序遍历数组和中序遍历数组)
    void rebuild(T pre[], T in[], int len)
    {
        // 如果root_不是空树,则清空,防止内存泄漏
        if (root_ != nullptr)
        {
            clear();
        }
        // 设置下标,之后递归是用下标来递归
        int i = 0, m = 0;
        int j = len - 1, n = len - 1;
        root_ = rebuild(pre, i, j, in, m, n);
    }
    // 判断此树是否为平衡二叉树
    /*可以直接使用high()写递归,但是效率太低,会出现子树被重复计算高度的问题
    解决的方式就是归的时候更新高度
    另外带一个引用的标签,如果一个地方判断出了不是平衡二叉树则立即终止判断*/
    bool isBalance()
    {
        bool flag = true; // 用于随时中断判断
        isBalance(root_, flag);
        return flag;
    }
    // 找出中值遍历的倒数第k个值
    T get_revkth(int k)
    {
        int i = 0;
        T result;
        get_revkth(root_, k, i, result);
        return result;
    }

public:
    BSTree(Compare comp = Compare()) : root_(nullptr), comp_(comp) {}
    ~BSTree()
    {
        clear();
    }

private:
    // 清空树
    void clear()
    {
        deque<Node *> dqu;
        dqu.push_back(root_);
        while (!dqu.empty())
        {
            Node *del = dqu.front();
            dqu.pop_front();
            if (del->left_ != nullptr)
            {
                dqu.push_back(del->left_);
            }
            if (del->right_ != nullptr)
            {
                dqu.push_back(del->right_);
            }
            delete del;
        }
        root_ = nullptr;
    }
    void preOrder(Node *node)
    {
        if (node != nullptr)
        {
            cout << node->data_ << " ";
            preOrder(node->left_);
            preOrder(node->right_);
        }
        return;
    }
    void inOrder(Node *node)
    {
        if (node != nullptr)
        {
            inOrder(node->left_);
            cout << node->data_ << " ";
            inOrder(node->right_);
        }
        return;
    }
    void _inOrder(Node *node)
    {
        if (node != nullptr)
        {
            _inOrder(node->right_);
            cout << node->data_ << " ";
            _inOrder(node->left_);
        }
        return;
    }
    void postOrder(Node *node)
    {
        if (node != nullptr)
        {
            postOrder(node->left_);
            postOrder(node->right_);
            cout << node->data_ << " ";
        }
        return;
    }
    // 递归插入实现
    Node *insert(Node *node, const T &val)
    {
        if (node == nullptr)
        {
            return new Node(val);
        }
        if (comp_(node->data_, val))
        {
            node->right_ = insert(node->right_, val);
            return node;
        }
        else if (comp_(val, node->data_))
        {
            node->left_ = insert(node->left_, val);
            return node;
        }
        else
        {
            return node;
        }
    }
    // 递归查询实现
    Node *find(Node *node, const T &val)
    {
        if (node == nullptr)
        {
            return node;
        }
        if (comp_(node->data_, val))
        {
            return find(node->right_, val);
        }
        else if (comp_(val, node->data_))
        {
            return find(node->left_, val);
        }
        else
        {
            return node;
        }
    }
    // 递归删除实现
    Node *erase(Node *node, const T &val)
    {
        if (node == nullptr)
        {
            return node;
        }
        if (!(comp_(node->data_, val) || comp_(val, node->data_)))
        {
            if (node->left_ != nullptr && node->right_ != nullptr)
            {
                Node *prenode = node->left_;
                while (prenode->right_ != nullptr)
                {
                    prenode = prenode->right_;
                }
                node->data_ = prenode->data_;
                node->left_ = erase(node->left_, prenode->data_);
            }
            else
            {
                if (node->right_ != nullptr)
                {
                    Node *right = node->right_;
                    delete node;
                    return right;
                }
                else if (node->left_ != nullptr)
                {
                    Node *left = node->left_;
                    delete node;
                    return left;
                }
                else
                {
                    delete node;
                    return nullptr;
                }
            }
        }
        else if (comp_(node->data_, val))
        {
            node->right_ = erase(node->right_, val);
        }
        else
        {
            node->left_ = erase(node->left_, val);
        }
        return node;
    }
    // 以node为根的二叉树高度
    int high(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int left = high(node->left_);
        int right = high(node->right_);
        return left > right ? left + 1 : right + 1;
    }
    // 以node为根的二叉树节点个数
    int number(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int left = number(node->left_);
        int right = number(node->right_);
        return left + right + 1;
    }
    // 层序遍历实现
    void levelOrder(Node *node, int i)
    {
        if (node == nullptr)
        {
            return;
        }
        if (i == 0)
        {
            cout << node->data_ << " ";
            return;
        }
        levelOrder(node->left_, i - 1);
        levelOrder(node->right_, i - 1);
    }
    // findValues实现
    void findValues(Node *node, vector<T> &vec, const T &i, const T &j)
    {
        if (node != nullptr)
        {
            if (node->data_ >= i)
            {
                findValues(node->left_, vec, i, j);
            }
            if (node->data_ >= i && node->data_ <= j)
            {
                vec.push_back(node->data_);
            }
            if (node->data_ <= j)
            {
                findValues(node->right_, vec, i, j);
            }
        }
    }
    // isBSTree实现(使用中序遍历递增的性质)(这个性质是因为我们这里用了less的比较器)
    bool isBSTree(Node *node, Node *pre)
    {
        if (node == nullptr)
        {
            return true;
        }
        if (!isBSTree(node->left_, pre))
        {
            return false;
        }
        if (pre != nullptr)
        {
            if (comp_(node->data_, pre->data_))
            {
                return false;
            }
            pre = node;
        }
        return isBSTree(node->right_, pre);
    }
    // isChildTree递归部分
    bool isChildTree(Node *node_1, Node *node_2)
    {
        if (node_2 == nullptr)
        {
            return true;
        }
        if (node_1 == nullptr && node_2 != nullptr)
        {
            return false;
        }
        if (!isChildTree(node_1->left_, node_2->left_))
        {
            return false;
        }
        if (comp_(node_1->data_, node_2->data_) || comp_(node_2->data_, node_1->data_))
        {
            return false;
        }
        return isChildTree(node_1->right_, node_2->right_);
    }
    // getLCA递归部分
    Node *getLCA(Node *node, const T &i, const T &j)
    {
        if (node == nullptr)
        {
            return node; // 如果到最后都没找到,那就是i和j有问题
        }
        if (comp_(i, node->data_) && comp_(j, node->data_))
        {
            return getLCA(node->left_, i, j);
        }
        else if (comp_(node->data_, i) && comp_(node->data_, j))
        {
            return getLCA(node->right_, i, j);
        }
        else
        {
            return node; // 剩下的不是相等了就是在i和j中间,那就是我们要找的
        }
    }
    // 镜像翻转递归部分
    void mirror01(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        mirror01(node->left_);
        mirror01(node->right_);
        Node *t = node->left_;
        node->left_ = node->right_;
        node->right_ = t;
        t = nullptr;
    }
    // 镜像对称递归部分(没测试过)
    bool mirror02(Node *node1, Node *node2)
    {
        // 如果都为空，认为是对称的
        if (node1 == nullptr && node2 == nullptr)
        {
            return true;
        }
        // 如果一个为空一个不为空，肯定不对称
        if (node1 == nullptr || node2 == nullptr)
        {
            return false;
        }
        if (comp_(node1->data_, node2->data_) || comp_(node2->data_, node1->data_))
        {
            return false;
        }
        return (mirror02(node1->left_, node2->right_) && mirror02(node1->right_, node2->left_));
    }
    // 重建二叉树递归部分
    Node *rebuild(T pre[], int i, int j, T in[], int m, int n)
    {
        if (i > j || m > n)
        {
            return nullptr;
        }
        Node *newnode = new Node(pre[i]);
        for (int k = m; k <= n; k++)
        {
            if (!(comp_(in[k], pre[i]) || comp_(pre[i], in[k])))
            {
                newnode->left_ = rebuild(pre, i + 1, i + k - m, in, m, k - 1);
                newnode->right_ = rebuild(pre, i + k - m + 1, j, in, k + 1, n);
                return newnode;
            }
        }
        return newnode;
    }
    // 判断平衡树递归实现
    int isBalance(Node *node, bool &flag)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int left = isBalance(node->left_, flag);
        if (!flag)
        {
            return left; // 事情不对,直接终止,返回
        }
        int right = isBalance(node->right_, flag);
        if (!flag)
        {
            return right; // 事情不对,直接终止,返回
        }
        if (left - right < -1 || left - right > 1)
        {
            flag = false;
        }
        return left > right ? left + 1 : right + 1;
    }
    // get_revkth的递归实现
    void get_revkth(Node *node, int k, int &i, T &result)
    {
        if (node == nullptr || i >= k)
        {
            return;
        }
        get_revkth(node->right_, k, i, result);
        if (i < k)
        {
            i++;
            if (i == k)
            {
                result = node->data_;
                return;
            }
        }
        get_revkth(node->left_, k, i, result);
    }
};

int main()
{
    SetConsoleOutputCP(CP_UTF8); // 设置中文编码
    BSTree<int> bs;
    int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    for (int v : arr)
    {
        bs.insert(v);
    }
    // cout << bs.find(12) << endl;
    // bs.insert(12);
    // cout << bs.find(12) << endl;
    // bs.erase(12);
    // cout <<"12: "<< bs.find(12) << endl;
    // bs.erase(0);
    // cout << "0: " << bs.find(0) << endl;
    // bs.erase(67);
    // cout << "67: " << bs.find(67) << endl;
    // bs.erase(58);
    // cout << "58: " << bs.find(58) << endl;

    // bs.n_insert(12);
    // bs.n_erase(62);
    // bs.n_erase(69);
    // bs.n_erase(67);
    // bs.n_erase(64);
    // bs.n_erase(78);
    // bs.n_erase(58);
    // // bs.n_erase(13);
    // cout << bs.n_find(24) << endl;
    bs.preOrder();
    bs.n_preOrder();
    bs.inOrder();
    bs.n_inOrder();
    bs._inOrder();
    bs.postOrder();
    bs.n_postOrder();
    cout << bs.high() << endl;
    cout << bs.number() << endl;
    bs.levelOrder();
    bs.n_levelOrder();
    // bs.mirror01();
    // bs.levelOrder();
    cout << "bs中序遍历下倒数第k个节点data_值: " << bs.get_revkth(4) << endl;

    //测试区间寻找数据
    vector<int> vec;
    bs.findValues(vec, 41, 64);
    for (int i : vec)
    {
        cout << i << " ";
    }
    cout << endl;

    //测试是否为BST树的判断
    cout << bs.isBSTree() << endl;

    //测试是否为子树的判断
    BSTree<int> bs2;
    int arr2[] = {67, 62, 69, 64, 78};
    for (int v : arr2)
    {
        bs2.insert(v);
    }
    cout << "bs2是bs的子树: " << bs.isChildTree(bs2) << endl;

    BSTree<int> bs3;
    int arr3[] = {67, 62, 69, 64, 78, 50};
    for (int v : arr3)
    {
        bs3.insert(v);
    }
    cout << "bs3是bs的子树: " << bs.isChildTree(bs3) << endl;
    
    //测试最近祖先节点的寻找
    cout << bs.getLCA(62, 78)->data_ << endl;

    //测试对平衡树判断的接口
    cout << "bs是平衡树: " << bs.isBalance() << endl;

    //测试用中序遍历和前序遍历构建唯一二叉树
    BSTree<int> bs4;
    int pre[] = {58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78};
    int in[] = {0, 5, 24, 34, 41, 58, 62, 64, 67, 69, 78};
    bs4.rebuild(pre, in, 11);
    bs4.preOrder();
    bs4.inOrder();

    //测试比较函数的使用
    BSTree<int, std::function<bool(int, int)>> tree(
        [](int a, int b)->bool
        { return a > b; });
    int brr[] = {4, 8, 25, 95, 42, 16, 75, 36, 82};
    for(int v : brr){
        tree.insert(v);
    }
    tree.inOrder();

    using Elm = pair<int, string>;
    using Functor = function<bool(pair<int, string>, pair<int, string>)>;
    BSTree<Elm, Functor> bst([](Elm p1, Elm p2) -> bool
                             { return p1.first > p2.first; });
    //这个只是演示使用,但这个pair其实不适配我们的这个BSTree,因为里面所有的data_的输出之类的代码都要改动
}