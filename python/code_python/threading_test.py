#!/usr/bin/python3.4

import threading
from time import sleep, ctime

loops=[4,2]

def loop(nloop, nsec):
    print('start loop',nloop,'at:',ctime())
    sleep(nsec)
    print('loop',nloop,'done at:',ctime())

def main():
    print('starting at:',ctime())
    threads=[]
    for i in range(0,10):
        t=threading.Thread(target=loop,args=(i,2))
        threads.append(t)

    for i in range(0,10):
        threads[i].start()

    for i in range(0,10):
        threads[i].join()

    print('all done at:',ctime())


if __name__=='__main__':
    main()
