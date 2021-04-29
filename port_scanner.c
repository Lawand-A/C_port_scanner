#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <signal.h> 
#include <unistd.h> 
#include <arpa/inet.h>
#include <stdarg.h>   // for function with variable argument lists
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>


void handle_error(const char *fmt, ...);


int main(int argc, char **argv){
    int sockfd;
    struct sockaddr_in servaddr;

//check the arguments
    if(argc != 2)
	handle_error("usage: %s <server adress>", argv[0]);
	

    int port = 1;
    int count = 0;
    printf("Start scanning ...\n\n==============================\n");
    while (port <= 10000){
    //create an Internet stream socket
        if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) <0)
            handle_error("There was an error while creating the socket!");

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
    //convert string representation of the adress to binary reapresentation
        if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)  
            handle_error("inet_pton error for %s ", argv[1]);

        if (connect( sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) <0){
            //printf("port %d is closed\n",port);
        } else{
            printf("port %d is open\n",port);
            count++;
            
        }
        port++;
	close(sockfd);
    }
    printf("==============================\n\nThere were %d ports open\n\n",count);
}

void handle_error(const char *m, ...){
    int errno_save;
    va_list a;

    errno_save = errno;

    va_start(a,m);
    vfprintf(stdout, m, a);
    fprintf(stdout, "\n");
    fflush(stdout);

    if (errno_save != 0) {
        fprintf(stdout, "(errno =%d) : %s\n", errno_save, strerror(errno_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }
    va_end(a);
    exit(1);
} 
	
	
	
	
	
