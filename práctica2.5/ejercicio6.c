#include <stdio.h>

#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
int main(int argc, char **argv)
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
    int a=bind(sd,resul->ai_addr,resul->ai_addrlen);
    if(a==-1){
        perror("Error: \n");
        return -1;
    }
    listen(sd,5);
    freeaddrinfo(resul);
    while(1){
        char buffer[100];
        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];
        struct sockaddr_storage cliente;
        socklen_t clientelen=sizeof(struct sockaddr_storage);
        int clientsd=accept(sd,(struct sockaddr*)&cliente,&clientelen);
        getnameinfo((struct sockaddr*)&cliente,clientelen,host,NI_MAXHOST,serv,NI_MAXSERV,0);
        printf("%i bytes de %s:%s\n",clientelen,host,serv);
        int c=0;
        while((c=recv(clientsd,buffer,80,0))!=0){
            send(clientsd,buffer,c,0);
        }
        if(c==0){
            break;
        }
        close(clientsd);
     }
   printf("Conexion finalizada\n");
return 0;
}