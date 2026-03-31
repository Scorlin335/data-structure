#include <iostream>

using namespace std;

enum State{
    STATE_USING,  // 此处有值,正在使用
    STATE_UNUSED, // 此处从未放过值
    STATE_DEL,    // 此处曾经放过值,但现在被删掉了
};

struct Bucket{
    Bucket(int key=0,State state=STATE_UNUSED)
        :key_(key),
        state_(state)
        {}
    int key_;
    State state_;
};

class HashTable{
    public:
        //放入一个元素
        bool insert(int key){
            //如果需要则扩容
            if(useBucketNum_*1.0/tableSize_>loadFactor_){
                expend();
            }
            cout << "factor: " << useBucketNum_ * 1.0 / tableSize_ << endl;
            int index = key % tableSize_;
            int i = index;
            do{
                if(table_[i].state_!=STATE_USING){
                    table_[i].key_ = key;
                    table_[i].state_ = STATE_USING;
                    useBucketNum_++;
                    return true;
                }else{
                    i = (i + 1) % tableSize_;//哈希表是循环的
                }
            } while (i != index);
            return false;
        }
        //清除所有值为key的元素,这里只是改变他们的状态,并不是真的删除
        bool erase(int key){
            int index = key % tableSize_;
            int i = index;
            bool flag = false;
            //找的时候如果有一个位置是从来没有放过元素的,那么就可以停了
            if (table_[i].state_==STATE_UNUSED){
                return false;
            }else{
                do{
                    if(table_[i].state_==STATE_USING&&table_[i].key_==key){
                        table_[i].state_ = STATE_DEL;
                        useBucketNum_--;
                        flag = true;
                    }
                    i = (i + 1) % tableSize_;
                } while (table_[i].state_ != STATE_UNUSED && i != index);
            }
            return flag;
        }
        //查询是否有这个元素(也可以通过简单修改改成里面有几个这个元素)
        bool find(int key){
            int index = key % tableSize_;
            int i = index;
            //找的时候如果有一个位置是从来没有放过元素的,那么就可以停了
            if (table_[i].state_==STATE_UNUSED){
                return false;
            }else{
                do{
                    if(table_[i].state_==STATE_USING&&table_[i].key_==key){
                        return true;
                    }else{
                    i = (i + 1) % tableSize_;
                }
                } while (table_[i].state_ != STATE_UNUSED && i != index);
            }
            return false;
        }
    private:
        void expend(){
            primeIdx_++;
            if(primeIdx_==PRIME_SIZE){
                throw "the hashtable is too large, can not be expanded any more!";
            }
            Bucket *newtable = new Bucket[primes_[primeIdx_]];
            for (int i = 0; i < tableSize_;i++){
                if(table_[i].state_==STATE_USING){
                    int index = table_[i].key_ % primes_[primeIdx_];
                    int k = index;
                    do{
                        if(newtable[k].state_!=STATE_USING){
                            newtable[k].key_ = table_[i].key_;
                            newtable[k].state_ = STATE_USING;
                            break;
                        }else{
                            k = (k + 1) % primes_[primeIdx_];
                        }
                    } while (k != index);
                }
            }
            delete []table_;
            table_ = newtable;
            tableSize_ = primes_[primeIdx_];
        }
    public:
        HashTable(int size=primes_[0],double loadFactor=0.75)
            :useBucketNum_(0),
            loadFactor_(loadFactor),
            primeIdx_(0){
                //如果用户传进来了一个不在素数表中的size
                if(size!=primes_[0]){
                    for (; primeIdx_ < PRIME_SIZE;primeIdx_++){
                        if(primes_[primeIdx_]>=size){
                            break;
                        }
                    }
                    // 如果用户传进来的size超过了素数表中的最大值
                    if(primeIdx_==PRIME_SIZE){
                        primeIdx_--;
                    }
                }
                tableSize_ = primes_[primeIdx_];
                table_ = new Bucket[tableSize_];
            }
        ~HashTable(){
            delete[] table_;
            table_ = nullptr;
        }
    private:
        Bucket *table_;     //表头
        int tableSize_;     //表的容量
        int useBucketNum_;  //已经使用的位置个数
        double loadFactor_; //装载因子

        inline static const int PRIME_SIZE = 10;   //素数表大小
        inline static int primes_[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};
        int primeIdx_;
};

#include <iostream>
#include <cassert>
#include <string>
using namespace std;

// 将您的 HashTable 类定义放在这里（或者包含头文件）

int main()
{
    // 测试1：基本插入和查找
    cout << "=== Test 1: Basic insert and find ===" << endl;
    HashTable ht1;
    assert(ht1.insert(10));
    assert(ht1.insert(20));
    assert(ht1.insert(30));
    assert(ht1.find(10));
    assert(ht1.find(20));
    assert(ht1.find(30));
    assert(!ht1.find(40));
    cout << "Test 1 passed.\n"
         << endl;

    // 测试2：删除和再次查找
    cout << "=== Test 2: Erase and find again ===" << endl;
    assert(ht1.erase(20));
    assert(!ht1.find(20));
    assert(ht1.find(10));
    assert(ht1.find(30));
    assert(!ht1.erase(20)); // 删除不存在的元素返回 false
    cout << "Test 2 passed.\n"
         << endl;

    // 测试3：重复键（如果允许重复）
    cout << "=== Test 3: Duplicate keys ===" << endl;
    HashTable ht2;
    assert(ht2.insert(5));
    assert(ht2.insert(5)); // 再次插入相同键（允许重复）
    assert(ht2.insert(5));
    // 查找应能找到（多个重复值，find 只返回是否存在）
    assert(ht2.find(5));
    // 删除所有重复值
    assert(ht2.erase(5));
    // 删除所有重复后，应该找不到 5
    assert(!ht2.find(5));
    // 再插入一个 5，应能成功
    assert(ht2.insert(5));
    assert(ht2.find(5));
    cout << "Test 3 passed.\n"
         << endl;

    // 测试4：扩容
    cout << "=== Test 4: Expansion ===" << endl;
    HashTable ht3(3); // 初始容量3，装载因子0.75，当使用超过2个时扩容
    assert(ht3.insert(1));
    assert(ht3.insert(2));
    // 此时装载因子 = 2/3 ≈ 0.666，未达到0.75，不会扩容
    assert(ht3.insert(3)); // 现在3个，装载因子=1，触发扩容
    // 扩容后容量应为下一个素数7
    // 检查元素是否都在
    assert(ht3.find(1));
    assert(ht3.find(2));
    assert(ht3.find(3));
    // 继续插入更多，验证扩容后的正确性
    assert(ht3.insert(4));
    assert(ht3.insert(5));
    assert(ht3.insert(6));
    assert(ht3.insert(7)); // 此时可能再次扩容到23
    // 验证所有元素
    for (int i = 1; i <= 7; i++)
    {
        assert(ht3.find(i));
    }
    cout << "Test 4 passed.\n"
         << endl;

    // 测试5：线性探测删除后重新插入
    cout << "=== Test 5: Deleted slot reuse ===" << endl;
    HashTable ht4(7); // 容量7
    // 插入一些元素，造成冲突
    for (int i = 0; i < 5; i++)
    {
        ht4.insert(i * 7); // 所有key %7 ==0，会线性探测
    }
    // 删除其中一个
    assert(ht4.erase(0));
    // 重新插入，应该能复用被删除的槽位
    assert(ht4.insert(0));
    assert(ht4.find(0));
    cout << "Test 5 passed.\n"
         << endl;

    // 测试6：大量数据插入，验证无崩溃
    cout << "=== Test 6: Large insertion ===" << endl;
    HashTable ht5;
    const int N = 1000;
    for (int i = 0; i < N; i++)
    {
        assert(ht5.insert(i));
    }
    for (int i = 0; i < N; i++)
    {
        assert(ht5.find(i));
    }
    for (int i = 0; i < N; i++)
    {
        assert(ht5.erase(i));
        assert(!ht5.find(i));
    }
    cout << "Test 6 passed.\n"
         << endl;

    cout << "\nAll tests passed!" << endl;
    return 0;
}

// int main(){
//     HashTable htable(7);
//     htable.insert(14);
//     htable.insert(8);
//     htable.insert(35);
//     htable.insert(35);
//     htable.insert(3);
//     htable.insert(16);
//     htable.insert(77);
//     cout << htable.find(77) << endl;
//     htable.erase(77);
//     cout << htable.find(77) << endl;
// }