//
//  main.c
//  mainprj
//
//  Created by Yosif Aboulaban on 10.10.2024.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "liblinet.h"

int main(int argc, const char * argv[])
{
    int RES;
    char OPT[100];
    
    while(1)
    {
        printf("MAIN&>> ");
        scanf("%s", OPT);
        
        RES = strcmp(OPT, "quit");
        if(RES == 0)
        {
            printf("Bye Bye!\n");
            exit(0);
        }
        
        RES = strcmp(OPT, "exit");
        if(RES == 0)
        {
            printf("Bye Bye!\n");
            exit(0);
        }
        
        RES = strcmp(OPT, "httpreq");
        if(RES == 0)
        {
            int PoRT;
            char IP[100];
            
            printf("enter Ip: ");
            scanf("%s", IP);
            
            printf("enter port: ");
            scanf("%d", &PoRT);
            
            hedreq(IP, PoRT);
        }
        
        RES = strcmp(OPT, "rserv");
        if(RES == 0)
        {
            bcks();
        }
        
        RES = strcmp(OPT, "rcli");
        if(RES == 0)
        {
            char ip[100];
            
            printf("Enter Ip: ");
            scanf("%s", ip);
            
            admin(ip);
        }
    }
}
