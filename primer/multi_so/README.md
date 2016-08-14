多个版本动态库
====

*   [Linux共享库的版本控制和使用](http://www.voidcn.com/blog/lovewubo/article/p-55305.html)

0.0.0版本
----

g++ -shared -Wl,-soname,libhello.so.0 -o libhello.so.0.0.0 hello.o
readelf -d libhello.so.0.0.0
ln -s libhello.so.0.0.0 libhello.so.0 # 软连接
ln -s libhello.so libhello.so.0

0.1.0版本
----

g++ -shared -Wl,-soname,libhello.so.0 -o libhello.so.0.1.0 hello.o

1.0.0版本
----

g++ -shared -Wl,-soname,libhello.so.1 -o libhello.so.1.0.0 hello.o
ln -s libhello.so.1.0.0 libhello.so.1 # 软连接
ln -s libhello.so libhello.so.1
