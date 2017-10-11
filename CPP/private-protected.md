## private和protected

2017年9月6日
17:38

一个`C++`类中的变量如果如下关键字作为修饰符.  
1. `public`: 程序的任何地方都可以访问.  
2. `protected`: 只有类本身及其派生类和其友元函数,友元类可以访问.  
3. `private`: 只有类本身及其友元函数,友元类可以访问.  
4. `friend`: 用于定义友元函数友元类. 在类里声明的一个普通函数,在前面加上friend修饰符,这个函数就可以访问该类的一切成员,包括private成员.  

下面在看下`c++`中 `public private protected`关键字  
1. 当在类的内部使用这三个关键字，表示访问权限：  
   `public`: 可以被任意访问。  
   `protected`: 只允许子类和本类的成员函数访问。  
   `private`: 只允许本类的成员函数访问。  
2. 当在类的继承层次中访问时：  
    `public`: 基类成员的访问权限不会被改变。  
    `protected`: 基类的public成员为子类的protected成员，其它成员的访问权限不变。  
    `private`: 基类的所有成员在子类中的访问权限变为private。  

源文档 <https://yq.aliyun.com/ziliao/103965> 
