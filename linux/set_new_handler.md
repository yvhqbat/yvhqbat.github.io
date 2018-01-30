```
/*
define:
new_handler set_new_handler (new_handler new_p) noexcept;

refer to:
http://www.cplusplus.com/reference/new/set_new_handler/

compiler and run:
root@ubuntu:/mnt/ld/demos# g++ -std=c++11 new_handler.cpp -o new_handler_demo
root@ubuntu:/mnt/ld/demos# ./new_handler_demo                                
ok: 0
ok: 1
ok: 2
set_new_handler callback: out of memory
Aborted
*/

#include <iostream>
#include <new>

void OutOfMemory()
{
	std::cout<<"set_new_handler callback: out of memory"<<std::endl;
	std::abort();
}

int main(int argc, char** argv)
{
	std::set_new_handler(OutOfMemory);
	for(int i=0;i<100;++i)
	{
		char* p=new char[1024*1024*1024];  // 1G
		std::cout<<"ok: "<<i<<std::endl;
	}
	return 0;
}
```
