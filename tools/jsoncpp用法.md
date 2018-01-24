# jsoncpp用法
jsoncpp的Github网址:  
https://github.com/open-source-parsers/jsoncpp

可获得源码,并编译成库, 文档.

jsoncpp主要的三个类的用法如下:

## 1. Json::Value

```
Json::Value root;
/* key-value */
root["type"]="request"; //"response"
root["cmd"] ="start";   // "stop","query", "close"

/* 数组 */
Json::Value array;
//array.resize(0);
array[0] = "param 1";
array[1] = 2;
array[2] = "hello world";
root["params"]=array;
```

Json::Value转化为字符串的方法Json::Value::toStyledString()
```
std::string str = root.toStyledString();
```
## 2. Json::FastWriter
```
/* Json::Value 转化为字符串 */
Json::FastWriter writer;
std::string strJson = writer.write(root);
cout << "json string is: "<< strJson << endl;
```
## 3. Json::Reader
主要用于解析
```
// parse
// strJson 为json 字符串
Json::Reader reader;
Json::Value  root;
if (!reader.parse(strJson, root, false))
{
    cout<<"解析失败"<<endl;
}

/* 打印 */
cout<<"type: "<<root["type"]<<endl;
cout<<"cmd : "<<root["cmd"]<<endl;
for(int i=0;i<root["params"].size();++i)
{
    cout<<"param "<<i<<": "<<root["params"][i]<<root["params"][i].type()<<endl;
    if(root["params"][i].isString())
    {
        cout<<"is string"<<endl;
    }
}

cout<<endl;
string param0=root["params"][0].asString();
int param1=root["params"][1].asInt();
//int param2=root["params"][2].asInt();
string param2=root["params"][2].asString();
cout<<param0<<endl<<param1<<endl<<param2<<endl;
```

## 4. std 的文件操作 fstream
1. 从文件流中解析json

```
/* 解析 json 文件 */
ifstream ifs;
ifs.open("stream_url.json");
assert(ifs.is_open());

Json::Reader reader;
Json::Value root;
if (!reader.parse(ifs, root, false))
{
    cout<<"解析文件失败"<<endl;
}
```

2. 将string写入到文件流

```
ofstream ofs;
ofs.open("stream_url.json");
assert(ofs.is_open());
ofs<<strJson;
ofs.close();
```
