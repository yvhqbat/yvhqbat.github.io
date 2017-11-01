/** @file ThreadPool.h
 *  @brief  线程池类
 *  @note   模仿了muduo库的实现.
 *  @author liudong
 *  @date 2017/09/09
 */

#include <functional>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

/* 命名空间 ld */
namespace ld
{

/** @class CThreadPool
 *  @brief 线程池类
 */
class CThreadPool
{
public:
    /* 定义任务类型, 使用时可以使用std::bind来绑定参数 */
    typedef std::function<void()> Task;

    /* 构造函数 */
    CThreadPool(int nThreadNum);

    /* 析构函数 */
    ~CThreadPool();

    /* 启动线程池 */
    void Start();

    /* 关闭线程池 */
    void Stop();

    /* 添加任务到任务队列 */
    void RunTask(const Task &task);

    /* 从任务队列中取出一个任务 */
    Task TakeTask();

private:
    /* 每个线程, 从任务队列中取任务,并开始执行 */
    void RunInThread();

private:
    int                       m_nThreadNum;         ///< 线程数目
    std::vector<std::thread*> m_pThreads;           ///< 保存线程指针
    std::queue<Task>          m_taskQueue;          ///< 任务队列
    std::mutex                m_mutex;              ///< 保护任务队列的互斥锁
    std::condition_variable   m_conditionVariable;  ///< 不为空的条件变量
    bool                      m_bRunning;           ///< 运行状态
};

}
