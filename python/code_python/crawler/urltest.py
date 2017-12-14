#!/usr/bin/python3.4

from urllib.request import urlopen
import re

def download(url):
    print('downloading',url)
    return urlopen(url)
#    with urlopen(url) as response:
#        return response
#        for line in response:
#            line=line.decode('utf-8')
#            #print(line)

context=download('http://www.baidu.com')
#html=context.read()

print(context.geturl())
print(context.info())
print(context.getcode())


html=context.read()
#print(html)
links=re.findall('<loc>(.*?</loc>)',html)
for link in links:
    print(link)

