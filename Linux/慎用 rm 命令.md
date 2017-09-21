
## `rm -rf ./*` 导致的整个工程文件丢失错误
```
root@tegra-ubuntu:/home/liudong11/StageTwo/VideoProcess# ls
bin  build  build.sh  CMakeLists.txt  include  libs  Makefile  src
root@tegra-ubuntu:/home/liudong11/StageTwo/VideoProcess# ll ./build
total 40
drwxr-xr-x 4 root root  4096 Sep 21 10:21 ./
drwxr-xr-x 7 4119 4120  4096 Sep 21 10:19 ../
-rw-r--r-- 1 root root 12183 Sep 21 10:20 CMakeCache.txt
drwxr-xr-x 5 root root  4096 Sep 21 10:21 CMakeFiles/
-rw-r--r-- 1 root root  1844 Sep 21 10:20 cmake_install.cmake
-rw-r--r-- 1 root root  5970 Sep 21 10:21 Makefile
drwxr-xr-x 3 root root  4096 Sep 21 10:21 src/
root@tegra-ubuntu:/home/liudong11/StageTwo/VideoProcess# rm -rf ./*
root@tegra-ubuntu:/home/liudong11/StageTwo/VideoProcess# ls
root@tegra-ubuntu:/home/liudong11/StageTwo/VideoProcess# ls
root@tegra-ubuntu:/home/liudong11/StageTwo/VideoProcess# ls
```
