## XML和JSON的区别
[参考1](https://www.cnblogs.com/gslblog/p/6664641.html)
[参考2](http://blog.csdn.net/ljyanlj/article/details/55254279)


### 1.XML
扩展标记语言 (Extensible Markup Language, XML) ，用于标记电子文件使其具有结构性的标记语言，可以用来标记数据、定义数据类型，是一种允许用户对自己的标记语言进行定义的源语言。 XML使用DTD(document type definition)文档类型定义来组织数据;格式统一，跨平台和语言，早已成为业界公认的标准。
XML是标准通用标记语言 (SGML) 的子集，非常适合 Web 传输。XML 提供统一的方法来描述和交换独立于应用程序或供应商的结构化数据。

### 2.JSON
JSON(JavaScript Object Notation)一种轻量级的数据交换格式，具有良好的可读和便于快速编写的特性。可在不同平台之间进行数据交换。JSON采用兼容性很高的、完全独立于语言文本格式，同时也具备类似于C语言的习惯(包括C, C++, C#, Java, JavaScript, Perl, Python等)体系的行为。这些特性使JSON成为理想的数据交换语言。
JSON基于JavaScript Programming Language , Standard ECMA-262 3rd Edition - December 1999 的一个子集。

### 3.XML和JSON优缺点
(1).XML的优缺点
<1>.XML的优点
　　A.格式统一，符合标准；
　　B.容易与其他系统进行远程交互，数据共享比较方便。
<2>.XML的缺点
　　A.XML文件庞大，文件格式复杂，传输占带宽；
　　B.服务器端和客户端都需要花费大量代码来解析XML，导致服务器端和客户端代码变得异常复杂且不易维护；
　　C.客户端不同浏览器之间解析XML的方式不一致，需要重复编写很多代码；
　　D.服务器端和客户端解析XML花费较多的资源和时间。

 

(2).JSON的优缺点
<1>.JSON的优点：
　　A.数据格式比较简单，易于读写，格式都是压缩的，占用带宽小；
　　B.易于解析，客户端JavaScript可以简单的通过eval()进行JSON数据的读取；
　　C.支持多种语言，包括ActionScript, C, C#, ColdFusion, Java, JavaScript, Perl, PHP, Python, Ruby等服务器端语言，便于服务器端的解析；
　　D.在PHP世界，已经有PHP-JSON和JSON-PHP出现了，偏于PHP序列化后的程序直接调用，PHP服务器端的对象、数组等能直接生成JSON格式，便于客户端的访问提取；
　　E.因为JSON格式能直接为服务器端代码使用，大大简化了服务器端和客户端的代码开发量，且完成任务不变，并且易于维护。
<2>.JSON的缺点
　　A.没有XML格式这么推广的深入人心和喜用广泛，没有XML那么通用性；
　　B.JSON格式目前在Web Service中推广还属于初级阶段。
