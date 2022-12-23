#include <stdio.h>
#include <unistd.h> // for close
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
int main(int argc, char *argv[])
{
    if(argc<3){
        printf("Errror en los argumentos\n");
        return -1;
    }
     struct addrinfo hints;
    struct addrinfo *resul;
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_flags=AI_PASSIVE;
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;
    int rc=getaddrinfo(argv[1],argv[2],&hints,&resul);
    if(rc!=0){
        perror("error \n");
        return -1;
    }
    int sd=socket(resul->ai_family,resul->ai_socktype,0);
    socklen_t servlen=sizeof(struct sockaddr_storage);
    connect(sd,resul->ai_addr,servlen);
    freeaddrinfo(resul);
    while(1){
    char buffer[100];
    int sizee=read(0,buffer,0777);
    buffer[sizee]='\0';
    if(buffer[0]=='Q'){
        close(sd);
        break;
    }else{
        send(sd,buffer,sizee,0);
        int bytes=recv(sd,buffer,100,0);
        buffer[bytes]='\0';
        if(bytes==0){
        close(sd);
        return 0;
        }
        printf("Servidor envia: %s\n",buffer);
    }
    }

     
   
return 0;
}