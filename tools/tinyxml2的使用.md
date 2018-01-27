
## tinyxml2

TinyXML-2 is a simple, small, efficient, C++ XML parser that can be easily integrated into other programs.

[doc](http://leethomason.github.io/tinyxml2/index.html)

主要就两个文件：
- tinyxml2.h
- tinyxml2.cpp

包含到项目中即可。

### 实例

1. xml文件
```
<PLAY>
	<TITLE>i love you</TITLE>
	<CONTENT>this is the content</CONTENT>
</PLAY>
```

2. 使用

```
#include "tinyxml2.h"

#include <iostream>
using namespace std;
using namespace tinyxml2;

int
main()
{
	int nRet=0;
	XMLDocument doc;
	nRet = doc.LoadFile("test.xml");
    if(0!=nRet)
	{
		cout<<"load dream.xml file failed"<<endl;
		return nRet;
	}


	XMLElement* pElement=doc.FirstChildElement("PLAY");
	if(NULL == pElement)
	{
		cout<<"get first child element failed"<<endl;
		return -1;
	}
    //const char* pPlay=pElement->GetText();
	//cout<<"PLAY: "<<pPlay<<endl;

	XMLElement* p1=pElement->FirstChildElement("TITLE");
	const char* pTitle=p1->GetText();
	if(NULL == pTitle)
	{
		cout<<"get title failed"<<endl;
		return -1;
	}
	cout<<"title: "<<pTitle<<endl;

	XMLElement* p2=p1->NextSiblingElement("CONTENT");
	const char* pContent=p2->GetText();
	cout<<"content: "<<pContent<<endl;

	return 0;
}

```
