# TCP_LOCALHOST
TCP客户/服务器本机测试

头文件unp.h 
---
git clone https://github.com/unpbook/unpv13e.git
    
    ./configure    # try to figure out all implementation differences

    cd lib         # build the basic library that all programs need
    make           # use "gmake" everywhere on BSD/OS systems

    cd ../libfree  # continue building the basic library
    make

    # note the following two lines are not needed on Linux systems
    cd ../libroute # only if your system supports 4.4BSD style routing sockets
    make           # only if your system supports 4.4BSD style routing sockets

    cd ../intro    # build and test a basic client program
    make daytimetcpcli
    ./daytimetcpcli 127.0.0.1


出错及处理
---

./daytimetcpcli 127.0.0.1  
connect error: Connection refused   
  
	sudo apt-get install xinetd  
	cd /etc/xinetd.d  
	sudo vim daytime  
	disable=yes 改成 no  
	service xinetd restart

error: redefinition of ‘struct in_pktinfo’  
	  
	将头文件与系统自带库中冲突部分注释掉
	
	
undefined reference to `Socket(int, int, int)'  
   
	首字母大写函数Socket是函数socket的包裹函数，修改为socket调用最低级别函数即可
	
<iostream>与头文件在编译时发生冲突  
  
	打印内容使用printf代替cout，#include<cstdio>
