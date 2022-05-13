#include "unp.h"
#include <cstdio>

int main(int argc, char **argv)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    //创建套接口，捆绑服务器的端口
    listenfd = socket(AF_INET, SOCK_STREAM, 0); //创建一个套接口
    printf("创建套接口...\n");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    bind((listenfd), (SA *)&servaddr, sizeof(servaddr)); //套接口绑定提供服务的端口
    printf("套接口绑定提供服务的端口...\n");
    listen(listenfd, LISTENQ); //指示套接口进入监听连接请求状态
    printf("套接口进入监听连接请求状态...\n");
    for (;;)
    { //等待完成客户连接
        printf("等待完成客户连接...\n");
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (SA *)&cliaddr, &clilen); //接受连接请求，进入连接状态
        printf("接受连接请求，进入连接状态...\n");
        //并发服务器
        if ((childpid = fork()) == 0)
        {
            close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        close(connfd);
    }
}