/** @file    ObjectPool.h
 *  @brief   CObjectPool模板类
 *
 *  @author  
 *  @date    2017/09/22
 *
 *  @note
 *  @warning
 */
#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include <mutex>
#include <vector>
#include <memory>
#include <iostream>
#include <functional>

/** @template class CObjectPool
 *  @brief   保存的应该只是指向对象的指针, 对于指针所指的对象的构造、初始化和析构过程, 应该在外部完成.
 */
template<class T>
class CObjectPool
{
public:
    using Deletor=std::function<void(T*)>;

    void Add(std::unique_ptr<T> t)
    {
        std::cout<<"add a new object."<<std::endl;
        std::lock_guard<std::mutex> lgLock(m_mutex);
        m_pool.push_back(std::move(t));
    }

    std::unique_ptr<T,Deletor> Get()
    {
        // std::lock_guard<std::mutex> lgLock(m_mutex);  //Add里面有锁, 添加这行会导致死锁
        if(m_pool.empty())
        {
            Add(std::unique_ptr<T>(new T()));
        }
        std::lock_guard<std::mutex> lgLock(m_mutex);
        std::unique_ptr<T, Deletor> ptr(m_pool.back().release(),
                            [this](T *t)
                            {
                            /* 插入以 t初始化的unique_ptr */
                            std::lock_guard<std::mutex> lgLock(m_mutex);
                            m_pool.push_back(std::unique_ptr<T>(t));
                            std::cout<<"collect a old object."<<std::endl;
                            });
        m_pool.pop_back();
        return std::move(ptr);
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lgLock(m_mutex);
        return m_pool.size();
    }

    /* 构造函数 */
    CObjectPool()
    {
        for(int i=0;i<10;i++)
        {
            // TODO: 这个向对象池中添加新对象的过程是否可以考虑放在用户端
            Add(std::unique_ptr<T>(new T()));
        }
    }

    /* 析构函数, 用来释放对象池中的对象资源 */
    ~CObjectPool()
    {
        std::lock_guard<std::mutex> lgLock(m_mutex);
        for(auto ite = m_pool.begin();ite!=m_pool.end();ite++)
        {
            T* t = (*ite).release();
            if(nullptr != t)
            {
                delete t;
            }
        }
    }
private:
    std::vector<std::unique_ptr<T>> m_pool;
    std::mutex                      m_mutex;
};
#endif //OBJECT_POOL_H
