#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
int main(int argc, char **argv)
{
    if(argc<2){
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
    for(struct addrinfo * i=resul;i!=0;i=i->ai_next){
        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];
        getnameinfo(i->ai_addr,i->ai_addrlen,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST | NI_NUMERICSERV);
        printf("%s %s %i %i\n",host,serv,i->ai_family,i->ai_socktype);
    }
    freeaddrinfo(resul);
return 0;
}