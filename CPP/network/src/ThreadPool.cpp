/** @file ThreadPool.cpp
 *  @brief  线程池类
 *  @author liudong
 *  @date 2017/09/09
 */
#include <iostream>
using namespace std;
#include "ThreadPool.h"
using namespace ld;

/* 线程池构造函数 */
CThreadPool::CThreadPool(int nThreadNum)
    :m_nThreadNum(nThreadNum),
     m_mutex(),
     m_conditionVariable(),
     m_bRunning(false)
{
}

/* 线程池析构函数 */
CThreadPool::~CThreadPool()
{
    if(m_bRunning)
    {
        Stop();
    }
}

/* 启动线程池 */
void CThreadPool::Start()
{
    m_bRunning = true;
    for(int i=0;i<m_nThreadNum;++i)
    {
        m_pThreads.push_back(new std::thread(&CThreadPool::RunInThread, this));
    }
}

/* 停止线程持 */
void CThreadPool::Stop()
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_bRunning = false;
        m_conditionVariable.notify_all();
    }
    for(auto ite=m_pThreads.begin();
             ite!=m_pThreads.end();
             ++ite)
    {
        std::cout<<"thread "<<(*ite)->get_id()<<"quit"<<std::endl;
        (*ite)->join();
    }
}

/* 添加任务 */
void CThreadPool::RunTask(const Task& task)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_taskQueue.push(task);
    m_conditionVariable.notify_one();
}

/* 取出一个任务 */
CThreadPool::Task CThreadPool::TakeTask()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while(m_taskQueue.empty() && m_bRunning)
    {
        m_conditionVariable.wait(lock);
    }
    Task task;
    if(!m_taskQueue.empty())
    {
        task=m_taskQueue.front();
        m_taskQueue.pop();
    }
    return task;
}

/* 每个线程执行的函数, 不断从任务队列中取任务, 然后执行 */
void CThreadPool::RunInThread()
{
    while(m_bRunning)
    {
        Task task=TakeTask();
        if(task)
        {
            task();
        }
    }
}
