
## xml/json/protobuf/thrift的区别
参考[xml json protobuf](https://www.cnblogs.com/gistao/p/4369216.html)

跨语言通信方案：
- Google protobuf
- Apache Thrift

### 1. XML
- 应用广泛，可扩展性强，被广泛应用各种场合
- 可读性强，可描述复杂结构
- 格式描述非常详细、冗余，读取、解析没有JSON快

### 2. JSON
- 应用广泛
- 结构简单，都是键值对
- 读取、解析速度快，多语言支持
- 传输数据量小，传输速率大大提高
- 描述复杂结构能力较弱

### 3. Protobuf
- 二进制格式，没有可读性
- 解析需要*.proto文件
- 速度快
- 使用简单，可自动生成访问数据的类
- 仅支持C++/Java/python

### 4. Thrift
Thrift提供了序列化/反序列化功能，支持语言众多，但性能相比protobuf还是弱一些。
Thrift在rpc场景被大量采用。
