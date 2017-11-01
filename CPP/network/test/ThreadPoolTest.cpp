#include "ThreadPool.h"
#include <iostream>
using namespace std;
using namespace ld;

void callback(int i)
{
    cout<<"thread id "<<std::this_thread::get_id()
        <<" and i is "<<i<<endl;
}

int main()
{
    CThreadPool *pThreadPool=new CThreadPool(5);
    pThreadPool->Start();
    for(int i=0;i<10;++i)
    {
        pThreadPool->RunTask(std::bind(callback,i));
    }
    delete pThreadPool;
    return 0;

}
