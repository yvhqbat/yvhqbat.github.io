#!/usr/bin

import os
import sys
import urllib
import urlparse

class Crawl(object):
    count=0

    def __init__(self, url):
        self.q=[url]
        self.seen=set()
        parsed=
