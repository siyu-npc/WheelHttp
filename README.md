使用c++完成一个的简单的http web服务器，这是一个造轮子的过程。
因此将其命名为WheelHttp。

WheelHttp 是自己的一个学习网络编程的项目，该服务器默认端口号
为2520。

### 编译WheelHttp
在linux系统下直接输入make即可，编译完成生成WheelHttp可执行文件


### 编译客户端程序
项目中除了服务器程序，还有一个client客户端程序，用来连接服务器
``` 
g++ client.cpp -o client 
```
之后就可以使用client连接WheelHttp，连接正常时输出“welcome,hello"
