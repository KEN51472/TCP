# TCP_LOCALHOST
TCP客户/服务器本机测试

头文件unp.h  git clone https://github.com/unpbook/unpv13e.git
    
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
