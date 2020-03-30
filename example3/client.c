
/*
* @Author: TaiLiang
* @LastEditTime: 2020/03/29/21/55/38
* @FilePath: /mnt/c/Users/tailiang/Desktop/socket/example1/client.c
* @Description: 网络回路客户
*/


#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    char ch = 'A';

    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //TCP:SOCK_STREAM

    //
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);
    int len = sizeof(address);

    int result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("oops:client1");
        exit(1);
    }

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server %c\n", ch);
    close(sockfd);
    exit(0);
}