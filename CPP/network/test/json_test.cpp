
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
#include "jsoncpp/json.h"

int main()
{
    Json::Value root;
    Json::FastWriter writer;

	/*
    Json::Value person;
    person["name"] = "hello world";
    person["age"] = 100;
    root.append(person);
    */

    Json::Value arr;
    arr[0]="param 0";
    arr[1]="param 1";
    arr[2]="param 2";
    root["params"]=arr;

    //Json::Value params;
    /*Json::Value item;
    for(int i=0;i<10;++i)
    {
        string value = "param";
        item["params"] = value;
        root.append(item);
    }*/




    std::string json_file = writer.write(root);


    ofstream ofs;
    ofs.open("test1.json");
    assert(ofs.is_open());
    ofs<<json_file;
    ofs.close();



   std::ifstream ifs;
   ifs.open("test.json");
   Json::Value val;
   Json::Reader reader;

   if (!reader.parse(ifs, val)) {
       return -1;
   }

   int sz = val["Skills"].size();
   for (int i = 0; i < sz; ++i) {
       std::cout << "Element " << i + 1 << ": ";
       std::cout << val["Skills"][i].asString();
       std::cout << std::endl;
   }

    return 0;
}
