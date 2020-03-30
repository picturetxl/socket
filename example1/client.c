
/*
* @Author: TaiLiang
* @LastEditTime: 2020/03/29/21/55/38
* @FilePath: /mnt/c/Users/tailiang/Desktop/socket/example1/client.c
* @Description: 本地客户
*/


#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char ch = 'A';

    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0); //TCP:SOCK_STREAM

    //
    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
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