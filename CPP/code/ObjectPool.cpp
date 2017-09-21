/*************************************************************************
	> File Name: ObjectPool.cpp
	> Author: ld
	> Mail: yvhqbat@126.com 
	> Created Time: 2017年09月22日 星期五 00时06分01秒
 ************************************************************************/
#include <vector>
#include <memory>
#include <mutex>
#include <iostream>
#include <functional>


template<class T>
class CObjectPool
{
public:
	using Deletor=std::function<void(T*)>;

	void Add(std::unique_ptr<T> t)
	{
		m_pool.push_back(std::move(t));
	}

	std::unique_ptr<T,Deletor> Get()
	{
		if(m_pool.empty())
		{
			return std::unique_ptr<T, Deletor>(new T(),
					         [this](T *t)
							 {
							     /* 插入以t初始化的unique_ptr */
	 							 m_pool.push_back(std::unique_ptr<T>(t));
	 						 }); 
		}
		std::unique_ptr<T, Deletor> ptr(m_pool.back().release(),
	 				         [this](T *t) 
							 {
	 						     /* 插入以 t初始化的unique_ptr */
								 m_pool.push_back(std::unique_ptr<T>(t));
							 });
		m_pool.pop_back();
		return std::move(ptr);
	}

	size_t size() const
	{
		return m_pool.size();
	}
private:
	std::vector<std::unique_ptr<T>> m_pool;
	std::mutex                      m_mutex;
};


class A
{
public:
	A()
	{
		m_i = 0;
	}

private:
	int m_i;
};

/* 测试 */
int main()
{
	CObjectPool<A> pool;
	for(int i=0;i<10;i++)
	{
	//	pool.Add(std::unique_ptr<A>(new A()));
	}
	std::cout<<"pool size is "<<pool.size()<<std::endl;

	{
		auto t = pool.Get();
		auto t1 = pool.Get();
		std::cout<<"pool size is "<<pool.size()<<std::endl;
	}	
	std::cout<<"pool size is "<<pool.size()<<std::endl;
	return 0;
}
