## shared_ptr function bind 的使用
> function_demo.cpp

```
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

#include <memory>

using namespace std;

#define TEST_HELP
#ifdef TEST_HELP
int _total_test=0;
int _failed_test=0;

#define test_condition(_c,scrib) \
do{\
	_total_test++;\
	if(_c){printf("%s\n", scrib);}\
	else{_failed_test++;}\
}while(0)

#define test_report()\
do{\
	printf("_total_test is %d, _failed_test is %d\n", _total_test,_failed_test);\
}while(0)

#endif

void test(string str){
	cout<<str<<endl;
}

void bind_func(string str1,string str2){
	cout<<str1<<endl;
	cout<<str2<<endl;
}

void bind_test(){
	function<void(string)> func;
	//func=bind(test,"bind test");
	// 占位符 std::placeholders::_1, _2, ...
	func=bind(bind_func,"this is string 2",std::placeholders::_1);
	func("this is string 1");
}

void test1(string str){
	cout<<"this is test1"<<endl;
}

typedef function<void(string)> callback;

class Base{
public:
	int n;
	string str;

	void member(void){
		cout<<str<<endl;
	}
};

void mem_fun_test()
{
	shared_ptr<Base> pBase=make_shared<Base>();
	pBase->str="this is base instance";

	function<void(void)> func;
	func=bind(&Base::member,pBase);
	func();
}

int main()
{
	function<void(string)> func;
	func=test;
	func("hello world");

	// 函数表
	map<string,callback> functionTabel;

	functionTabel["test"]=test;
	functionTabel["test"]("this is test");

	functionTabel["test1"]=test1;
	functionTabel["test1"]("hehe");

	greater<int> gt;
	cout<<gt(9,7)<<endl;

	vector<int> datas;
	for(int i=0;i<10;++i){
		datas.push_back(i+1);
	}

	int result=accumulate(datas.begin(),datas.end(),1,multiplies<int>());
	cout<<"result is "<<result<<endl;

	// 智能指针的使用
	//shared_ptr<Base> spBase(new Base());
	shared_ptr<Base> spBase=make_shared<Base>();
	spBase->n=13;
	spBase->str="dog";
	cout<<spBase->str<<endl;

	test_condition(1==0,"1==0");
	test_condition(1>0,"1>0");
	test_report();

	bind_test();

	mem_fun_test();

	return 0;
}
```
