

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    int flags, opt;
    char *port = (char *)malloc(sizeof(1));
    if (port == NULL)
    {
        exit(EXIT_FAILURE);
    }
    char *host = (char *)malloc(sizeof(4));
    if (host == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while ((opt = getopt(argc, argv, "p:h:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            strcpy(host, optarg);
            if (atoi(port) < 1024)
            {
                fprintf(stderr, "port is too small\n");
                exit(EXIT_FAILURE);
                break;
            case 'p':
                strcpy(port, optarg);
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-p port] [-h host]\n",
                        argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }
    if (argc <= 4)
    {
        fprintf(stderr, "Usage: %s [-p port] [-h host]\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }
    // printf("port:%s,host:%s\n", port, host);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //TCP:SOCK_STREAM
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(EXIT_FAILURE);
    }
    // struct hostent *server;
    // server = gethostbyname(host);
    // if (server == NULL) {
    //     fprintf(stderr,"ERROR, no such host\n");
    //     exit(EXIT_FAILURE);
    // }

    //AF_INET
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(host);
    address.sin_port = htons(atoi(port));
    int len = sizeof(address);
    //connect
    int result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("connect:error");
        exit(EXIT_FAILURE);
    }

    char msg[256];
    // printf("fgets\n");
    int newline = 0;
    while (1)
    {
        bzero(msg, 256);
        fgets(msg, 255, stdin);
        if (msg[strlen(msg) - 1] == '\n' && strlen(msg) == 1)
        {
            newline++;
        }

        if (msg[strlen(msg) - 1] == '\n' && strlen(msg) > 1)
        {
            newline = 1;
            int n = write(sockfd, msg, strlen(msg));
            if (n < 0)
            {
                perror("ERROR writing to socket");
                exit(EXIT_FAILURE);
            }
        }

        if (newline == 2)
        {
            break;
        }
    }
    close(sockfd);
    exit(EXIT_SUCCESS);
}