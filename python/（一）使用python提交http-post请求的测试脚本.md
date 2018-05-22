## 用到的模块

```python
import urllib.request
import json
from io import StringIO
from string import Template
import random
import logging

```
## 示例
```python
import urllib.request
import json
from io import StringIO
from string import Template
import random

import logging

logger = logging.getLogger('mylogger')
logger.setLevel(logging.DEBUG)
# 创建一个handler，用于写入日志文件
fh = logging.FileHandler('test.log')
fh.setLevel(logging.DEBUG)
# 定义handler的输出格式
formatter = logging.Formatter(
    '[%(asctime)s][%(thread)d][%(filename)s][line: %(lineno)d][%(levelname)s] ## %(message)s')
fh.setFormatter(formatter)
logger.addHandler(fh)



# 定义一个模板
template = Template(
    '{"algorithmType":$algorithmType,"abilities":"$abilities","dataSourceType":$dataSourceType,"url":"$url","targetType":$targetType,"token":"$token","executeParams":{"detectionType" : [ "$detectionType" ]}}')

# d=dict(algorithmType='1000',abilities=1,dataSourceType=2,url='http://10.66.91.11:7777/iectest/iec_4096_2160.jpg',targetType=5,token=getToken(),detectionType="human")
# task=template.safe_substitute(d)
# print(task)

def post(task_url, task_data):
    req = urllib.request.Request(url=task_url, data=task_data)
    f = urllib.request.urlopen(req)
    # print(f.status)
    # print(f.reason)
    result = f.read().decode('utf-8')
    return result

def getToken():
    token_url='http://10.66.91.11:2343/c100/services/rest/login'
    token_data=b'login={"userName":"admin","password":"12345"}'
    token_post=post(token_url,token_data)
    io = StringIO(token_post)
    token_json = json.load(io)
    token=token_json['token']
    return token

def task(picture):
    task_url = 'http://10.66.91.11:2343/c100/services/v2/target/analyze'
    #task_data = b'{"algorithmType":1000,"abilities":"1","dataSourceType":2,"url":"http://10.66.91.11:7777/iectest/iec_4096_2160.jpg","targetType":5,"token":"b0bfaf75f80f419096c464a9831bf15f","executeParams":{"detectionType" : [ "human" ]}}'
    d = dict(algorithmType='1000',
             abilities=1,
             dataSourceType=2,
             url='http://10.66.91.11:7777/iectest/'+picture,
             targetType=5,
             token=getToken(),
             detectionType="human")
    task = template.safe_substitute(d)
    result = post(task_url,bytes(task,encoding='utf-8'))
    io=StringIO(result)
    result_json=json.load(io)
    print(result_json)
    #print(result_json['results'][0])


pictures=['iec_4096_2160.jpg',
          'iec_1920_1080.jpg',
          'iec_1280_720.jpg',
          'iec_500_500.jpg',
          'test.jpg']
# while True:
#     picture=random.choice(pictures)
#     task(picture)


from multiprocessing import Process
import datetime

def f():
    while True:
        # picture = random.choice(pictures)
        picture = pictures[0]
        start = datetime.datetime.now()
        task(picture)
        end = datetime.datetime.now()
        print("time used ", (end - start).microseconds, "microseconds")
        logger.info("time used %d microseconds", (end - start).microseconds)


if __name__ == '__main__':
    start=datetime.datetime.now()
    lt=list()
    for i in range(10):
        p = Process(target=f)
        p.start()
        lt.append(p)

    for q in lt:
        q.join()
        end=datetime.datetime.now()

    print("time used ",(end-start).seconds, "s")

```
