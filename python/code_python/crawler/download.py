#!/usr/bin/python3.4

import urllib

def download(url):
    print('downloading',url)
    try:
        html=urllib.request.urlopen(url).read()
    except urllib.error.URLError as e:
        print('download error:',e.reason)
        html=None
    return html

download('www.baidu.com')


