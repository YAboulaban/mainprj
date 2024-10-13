//
//  liblinet.h
//  mainprj
//
//  Created by Yosif Aboulaban on 10.10.2024.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

#define PORT 3030

void hedreq(char Ip[], int Port)
{
    int sockfd;
    struct sockaddr_in host_addr;
    char Buffer[4096];
    char message[100];
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("PROBLEM IN SOCKET\n");
    }
    
    else
    {
        printf("socket is fine\n");
    }
    
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(Port);
    host_addr.sin_addr.s_addr = inet_addr(Ip);
    
    if((connect(sockfd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr))) == -1)
    {
        printf("PROBLEM CONNECTING TO IP ADRESS\n");
    }
    
    else
    {
        printf("connection is fine\n");
    }
    
    if((send(sockfd, message, sizeof(message), 0)) == -1)
    {
        printf("PROBLEM IN SENDING MESSAGE\n");
    }
    
    else
    {
        printf("mesage is fine\n");
    }
    
    if((recv(sockfd, Buffer, 4096, 0)) == -1)
    {
        printf("PROBLEM WHILE RECIVING MESSAGE\n");
    }
    
    else
    {
        printf("no problems reciving message");
        printf("HTTP REQUEST: %s\n", Buffer+8);
    }
    
}

void bcks(void)
{
    char Buffer[4096];
    int sockfd, clisock;
    socklen_t len;
    struct sockaddr_in host_addr, cli;
    
    len = sizeof(cli);
    
    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("PROBLEM IN SOCKET\n");
    }
    
    else
    {
        printf("socket is okay\n");
    }
    
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if((bind(sockfd, (struct sockaddr *)&host_addr, sizeof(host_addr))) == -1)
    {
        printf("problem binding\n");
    }
    
    else
    {
        printf("succesfully binded\n");
    }
    
    if((listen(sockfd, 10000)) == -1)
    {
        printf("problem listening for clients\n");
        printf("exiting\n");
        exit(1);
    }
    
    else
    {
        printf("listening for clients\n");
        printf("SERVER IS UP AND RUNNING\n");
    }
    
    while(1)
    {
        if((clisock = accept(sockfd, (struct sockaddr *)&cli, &len)) == -1)
        {
            continue;
        }
        
        else
        {
            printf("got connection from: %s, %d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
        }
        
        int RES;
        RES = strcmp((inet_ntoa(cli.sin_addr)), "127.0.0.1");
        
        if(RES == 0)
        {
            printf("Admin entered the server\n");
            send(clisock, "Welcome admin\n", sizeof("Welcome admin\n"), 0);
            
            while(1)
            {
                send(clisock, "RAT$>>", sizeof("RAT$>>"), 0);
                recv(clisock, Buffer, sizeof(Buffer), 0);
            }
        }
    }
}

void admin(char ip[])
{
    int sockfd;
    struct sockaddr_in host_addr;
    char Buffer[4096];
    
    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("problem in socket");
    }
    
    else
    {
        printf("socket is fine\n");
    }
    
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = inet_addr(ip);
    
    if((connect(sockfd, (const struct sockaddr *)&host_addr, sizeof(struct sockaddr))) == -1)
    {
        printf("problem in connection\n");
        
        printf("exiting\n");
        exit(1);
    }
    
    else
    {
        printf("connection is successfull\n");
    }
    
    recv(sockfd, Buffer, 4096, 0);
    
    printf("%s", Buffer);
    
    while(1)
    {
        recv(sockfd, Buffer, 4096, 0);
        printf("%s ", Buffer);
        
        char inp[100];
        scanf("%s", inp);
        send(sockfd, inp, sizeof(inp), 0);
    }
}
