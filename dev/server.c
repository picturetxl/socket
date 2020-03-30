
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    char port[1];
    int flags, opt;
    while ((opt = getopt(argc, argv, "p:")) != -1)
    {
        switch (opt)
        {
        case 'p':
        {
            // printf("-p option");
            strcpy(port, optarg);
            if (atoi(port) < 1024)
            {
                fprintf(stderr, "port is too small\n");
                exit(EXIT_FAILURE);
            }
            break;
        }
        case '?': /* '?' */
        {
            fprintf(stderr, "Usage: %s [-p port]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        }
    }
    if (argc <= 1)
    {
        fprintf(stderr, "Usage: %s [-p port]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // printf("waiting\n");
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(atoi(port));
    server_len = sizeof(server_address);

    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    listen(server_sockfd, 5);

    client_len = sizeof(client_address);

    char msg[255];
    while (1)
    {
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, (socklen_t *)&client_len);
        if (fork() == 0)
        {
            close(server_sockfd);
            while (1)
            {
                bzero(msg, 256);
                read(client_sockfd, msg, 255);
                fputs(msg, stdout);
            }

            exit(EXIT_SUCCESS);
        }
        else
        {
            close(client_sockfd);
        }
    }

    exit(EXIT_SUCCESS);
}