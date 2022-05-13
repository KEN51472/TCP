#include "unp.h"

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
    {
        exit(0);
    }

    //创建套接口，初始化套接口地址结构
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr); //转换由argv指针所指的字符串，并通过servaddr.sin_addr指针存放二进制结果，成功返回1失败返回0

    //与服务器连接
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0; //与服务器建立连接


    str_cli(stdin, sockfd); /* do it all */

    exit(0);
}