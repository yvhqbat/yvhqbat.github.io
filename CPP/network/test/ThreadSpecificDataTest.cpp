
#include <iostream>
#include <string>
#include <thread>
using namespace std;
#include "ThreadSpecificData.h"
using namespace ld;

class CTest
{
public:
    CTest()
    {
    }

    void SetName(const string &strName)
    {
        m_strName = strName;
    }

    void PrintName()
    {
        cout<<"thread id "<<this_thread::get_id()<<" name is "<<m_strName<<endl;
    }

private:
    string m_strName;  ///< 数据
};


CThreadSpecificData<CTest> tsd;

void ThreadFunc()
{
    tsd.CreateValue();
    tsd.GetValue().SetName("liudong");
    tsd.GetValue().PrintName();
}


int main()
{
    thread *t = new thread(ThreadFunc);

    /* 主线程中 */
    tsd.CreateValue();
    tsd.GetValue().SetName("caipei");
    tsd.GetValue().PrintName();

    t->join();
    return 0;
}
