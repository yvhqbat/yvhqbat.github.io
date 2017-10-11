## unique_lock和lock_guard的区别

2017年9月6日
10:34

### `C++11`中 `std::unique_lock`与`std::lock_guard` 的区别及多线程应用实例
`C++`多线程编程中通常会对共享的数据进行写保护，以防止多线程在对共享数据成员进行读写时造成资源争抢导致程序出现未定义的行为。  
通常的做法是在修改共享数据成员的时候进行加锁**`mutex`**。在使用锁的时候通常是在对共享数据进行修改之前进行lock操作，在写完之后再进行unlock操作，经常会出现由于疏忽导致由于lock之后在离开共享成员操作区域时忘记unlock，导致死锁。  

针对以上的问题，`C++11`中引入了`std::unique_lock` 与 `std::lock_guard` 两种数据结构。通过对`lock`和`unlock`进行一次薄的封装，实现自动`unlock`的功能。
```
std::mutex mut;
 
void insert_data()
{
    std::lock_guard<std::mutex> lk(mut);
    queue.push_back(data);
}
 
void process_data()
{
    std::unqiue_lock<std::mutex> lk(mut);
    queue.pop();
}
```

`std::unique_lock` 与 `std::lock_guard` 都能实现自动加锁与解锁功能，但是`std::unique_lock`要比`std::lock_guard`更灵活，更灵活的代价是占用空间相对更大一点且相对更慢一点。
 
### 通过实现一个线程安全的队列来说明两者之间的差别
```
template <typename T>
class ThreadSafeQueue{
public:
         void Insert(T value);
         void Popup(T &value);
         bool Empety();
 
private:
       mutable std::mutex mut_;
       std::queue<t> que_;
       std::condition_variable cond_;
};


template <typename T>
void ThreadSafeQueue::Insert(T value){
    std::lock_guard<std::mutex> lk(mut_);
    que_.push_back(value);
    cond_.notify_one();
}
 
 
template <typename T>
void ThreadSafeQueue::Popup(T &value){
    std::unique_lock<std::mutex> lk(mut_);
    cond_.wait(lk, [this]{return !que_.empety();});
    value = que_.front();
    que_.pop();
}
 
 
template <typename T>
bool ThreadSafeQueue::Empty() const{
    std::lock_guard<std::mutex> lk(mut_);
    return que_.empty();
}
```
上面代码只实现了关键的几个函数，并使用了`C++11`新引入的`condition_variable`条件变量。从`Popup`与`Inert`两个函数看`std::unique_lock`相对`std::lock_guard`更灵活的地方在于在等待中的线程如果在等待期间需要解锁mutex，并在之后重新将其锁定。而`std::lock_guard`却不具备这样的功能。
 
上面代码中
```
cond_.wait(lk, [this]{return !Empety();});
```
可能会比较难以理解，
```
[this]{return !Empety();}
```
是`C++11`新引入的功能，`lambda`表达式，是一种匿名函数。方括号内表示捕获变量。当`lambda`表达式返回`true`时（即queue不为空），`wait`函数会锁定`mutex`。当`lambda`表达式返回`false`时，`wait`函数会解锁`mutex`同时会将当前线程置于阻塞或等待状态。

还存在另一种读写锁，但是并没有引入`C++11`，但是`boost`库提供了对应的实现。读写锁主要适合在于共享数据更新频率较低，但是读取共享数据频率较高的场合。

源文档 <https://www.2cto.com/kf/201706/649733.html> 
