#include <iostream>
#include <math.h>

using namespace std;

template<typename T>

class AVLtree {
private:
    struct Node
    {
        Node(T data = T()) : data_(data), left_(nullptr), right_(nullptr), height_(1)
        {
        }
        T data_;
        Node *left_;
        Node *right_;
        int height_;
    };
    Node *root_;
public:
    AVLtree():root_(nullptr){}
    int getHeight(Node *node)
    {
        return node == nullptr ? 0 : node->height_;
    }
    void insert(T val){
        root_ = insert(root_, val);
    }
    void erase(T val){
        root_ = erase(root_, val);
    }
private:
    /*左孩子的左子树太高了
            40              30
           /                / \
          30          =>   20  40
          / \                  /
        20   x                x
    */
        Node *rightRotate(Node *node){
            //旋转
            Node *child = node->left_;
            node->left_ = child->right_;
            child->right_ = node;
            //高度更新
            node->height_ = max(getHeight(node->left_), getHeight(node->right_))+1;
            child->height_ = max(getHeight(child->left_), getHeight(child->right_))+1;
            //返回旋转后的新的根节点
            return child;
        }
    /*右孩子的右子树太高了
        20                30
         \                / \
         30          =>  20  40
        /  \               \
        x   40               x
    */
        Node *leftRotate(Node *node)
        {
            // 旋转
            Node *child = node->right_;
            node->right_ = child->left_;
            child->left_ = node;
            // 高度更新
            node->height_ = max(getHeight(node->left_), getHeight(node->right_))+1;
            child->height_ = max(getHeight(child->left_), getHeight(child->right_))+1;
            // 返回旋转后的新的根节点
            return child;
        }
    /*左孩子的右子树太高了
         40               30
         /                / \
        20          =>  20  40
         \               
          30               
    */
        Node *leftBalance(Node *node){
            node->left_ = leftRotate(node->left_);
            return rightRotate(node);
        }
    /*右孩子的左子树太高了
         20                30
          \                / \
          40          =>  20  40
          /
         30
    */
        Node *rightBalance(Node *node)
        {
            node->right_ = rightRotate(node->right_);
            return leftRotate(node);
        }
    //插入
    Node *insert(Node *node, T val){
        if(node == nullptr){
            return new Node(val);
        }
        if(val<node->data_){
            node->left_ = insert(node->left_, val);
            if((getHeight(node->left_)-getHeight(node->right_))>1){
                // node的左子树太高了
                if(getHeight(node->left_->left_)>=getHeight(node->left_->right_)){
                     // node的左孩子的左子树太高了
                    node = rightRotate(node);
                }else{
                    // node的左孩子的左子树太高了
                    node = leftBalance(node);
                }
            }
        }
        if(val>node->data_){
            node->right_ = insert(node->right_, val);
            if ((getHeight(node->right_) - getHeight(node->left_)) > 1)
            {
                // node的右子树太高了
                if (getHeight(node->right_->right_) >= getHeight(node->right_->left_))
                {
                    // node的右孩子的右子树太高了
                    node = leftRotate(node);
                }
                else
                {
                    // node的右孩子的左子树太高了
                    node = rightBalance(node);
                }
            }
        }
        
        node->height_ = max(getHeight(node->left_), getHeight(node->right_)) + 1;

        return node;
    }
    //删除
    Node *erase(Node *node, T val){
        if(node==nullptr){
            return nullptr;
        }
        if(node->data_<val){
            node->right_ = erase(node->right_, val);
            //右支删掉节点后左支可能会太高
            if(getHeight(node->left_) - getHeight(node->right_)>1){
                //左子树太高了
                if(getHeight(node->left_->left_)>=getHeight(node->left_->right_)){
                    //左孩子的左子树太高了
                    node = rightRotate(node);
                }else{
                    //左孩子的右子树太高了
                    node = leftBalance(node);
                }
            }
        }else if(node->data_>val){
            node->left_ = erase(node->left_, val);
            // 左支删掉节点后右支可能会太高
            if (getHeight(node->right_) - getHeight(node->left_) > 1){
                // 右子树太高了
                if (getHeight(node->right_->right_) >= getHeight(node->right_->left_)){
                    // 右孩子的右子树太高了
                    node = leftRotate(node);
                }else{
                    //右孩子的左子树太高了
                    node = rightBalance(node);
                }
            }
        }else{
            if(node->left_!=nullptr&&node->right_!=nullptr){
                //先梳理两边都有子节点的
                if(getHeight(node->left_)>getHeight(node->right_)){
                    //如果左子树高那么就删右子树上的节点
                    Node *pre = node->left_;
                    while(pre->right_!=nullptr){
                        pre = pre->right_;
                    }
                    node->data_ = pre->data_;
                    node->left_ = erase(node->left_, pre->data_);
                }else{
                    //如果右子树高那么就删左子树上的节点
                    Node *pre = node->right_;
                    while (pre->left_ != nullptr){
                        pre = pre->left_;
                    }
                    node->data_ = pre->data_;
                    node->right_ = erase(node->right_, pre->data_);
                }
            }else{
                //再处理只有一边有子节点的或没有子节点的
                if(node->left_!=nullptr){
                    Node *left = node->left_;
                    delete node;
                    return left;
                }else if(node->right_!=nullptr){
                    Node *right = node->right_;
                    delete node;
                    return right;
                }else{
                    delete node;
                    return nullptr;
                }
            }
        }
        //更新节点高度
        node->height_ = max(getHeight(node->left_), getHeight(node->right_)) + 1;
        return node;
    }
};

int main(){
    AVLtree<int> avl;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for(int v : arr){
        avl.insert(v);
    }
    avl.erase(9);
    avl.erase(10);
    avl.erase(6);
    avl.erase(8);
    avl.erase(2);
    avl.erase(1);
    avl.erase(3);

    AVLtree<int> avl2;
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,12 ,13 ,14 ,15 ,16};
    for (int v : arr2)
    {
        avl2.insert(v);
    }
    avl2.erase(13);
}
