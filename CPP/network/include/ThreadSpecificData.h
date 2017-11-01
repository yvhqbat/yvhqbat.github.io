/** @file ThreadSpecificData.h
 *  @brief 线程特定数据
 *  @note  在单线程程序中，我们经常要用到"全局变量"以实现多个函数间共享数据。
           在多线程环境下，由于数据空间是共享的，因此全局变量也为所有线程所共有。

           但有时应用程序设计中有必要提供线程私有的全局变量，仅在某个线程中有效，但却可以跨多个函数访问.
           比如程序可能需要每个线程维护一个链表，而使用相同的函数操作，
           最简单的办法就是使用同名而不同变量地址的线程相关数据结构。
           这样的数据结构可以由Posix线程库维护，称为 线程私有数据（Thread-specific Data，或TSD）。
 *  @author liudong
 *  @author 2017/09/10
 */

/*
#include <pthread.h>

int pthread_key_create(pthread_key_t *key, void (*destructor)(void*));
int pthread_key_delete(pthread_key_t key);
void *pthread_getspecific(pthread_key_t key);
int pthread_setspecific(pthread_key_t key, const void *value);
*/


#ifndef THREAD_SPECIFIC_DATA_H
#define THREAD_SPECIFIC_DATA_H
#include <pthread.h>

namespace ld
{

/** @class CThreadSpecificData
 *  @brief 将Posix维护的TSD封装为类.
 */
template<typename T>
class CThreadSpecificData
{
public:
    /* 构造函数 */
    CThreadSpecificData()
    {
        pthread_key_create(&m_key, &CThreadSpecificData::Destructor);
    }

    /* 析构函数 */
    ~CThreadSpecificData()
    {
        pthread_key_delete(m_key);
    }

    /* 创建m_key对应的value */
    void CreateValue()
    {
        T* newObj = new T();
        pthread_setspecific(m_key, newObj);
    }

    /* 获取m_key对应的value的值 */
    T& GetValue()
    {
        T* pT = static_cast<T*>(pthread_getspecific(m_key));
        return *pT;
    }

private:
    /* T对象的销毁 */
    static void Destructor(void *x)
    {
        T *t = static_cast<T*>(x);
        delete t;
    }
private:
    pthread_key_t m_key;    ///< 线程特定数据的key.
};

}
#endif  //THREAD_SPECIFIC_DATA_H
