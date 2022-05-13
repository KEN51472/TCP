#include "unp.h"

void str_cli(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    //读一行，写到服务器
    while (fgets(sendline, 4096, fp) != NULL)
    {
        writen(sockfd, sendline, strlen(sendline));

        //从服务器读取回射行，写到标准输出
        if (readline(sockfd, recvline, 4096) == 0)
        {
            exit(0);
        }
        fputs(recvline, stdout);
    }
}