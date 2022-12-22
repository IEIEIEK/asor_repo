#include <stdio.h>
#include <unistd.h> // for close
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
int main(int argc, char *argv[])
{
    if(argc<4 || (*argv[3]!='t' && *argv[3]!='d')){
        printf("Errror en los argumentos\n");
        return -1;
    }
     struct addrinfo hints;
    struct addrinfo *resul;
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_flags=AI_PASSIVE;
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_DGRAM;
    int rc=getaddrinfo(argv[1],argv[2],&hints,&resul);
    if(rc!=0){
        perror("error \n");
        return -1;
    }
    int sd=socket(resul->ai_family,resul->ai_socktype,0);
    freeaddrinfo(resul);
    
    char buffer[100];
    socklen_t servlen=sizeof(struct sockaddr_storage);
        
    sendto(sd,argv[3],sizeof(argv[3]),0,resul->ai_addr,servlen);
    ssize_t bytes=recvfrom(sd,buffer,99,0,resul->ai_addr,&servlen);
    if(bytes==0){
        close(sd);
        return 0;
    }
    buffer[bytes]='\0';
    printf("%s\n",buffer);
        
    close(sd);
     
   
return 0;
}