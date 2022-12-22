#include <stdio.h>

#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
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
    hints.ai_socktype=SOCK_DGRAM;
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
    freeaddrinfo(resul);
    while(1){
        char buffer[100];
        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];
        struct sockaddr_storage cliente;
        socklen_t clientelen=sizeof(struct sockaddr_storage);
        ssize_t bytes=recvfrom(sd,buffer,99,0,(struct sockaddr*)&cliente,
        &clientelen);
        buffer[bytes]='\0';
        getnameinfo((struct sockaddr*)&cliente,clientelen,host,NI_MAXHOST,serv,NI_MAXSERV,0);
        printf("%i bytes de %s:%s\n",clientelen,host,serv);
        char t[]="t";
        char q[]="q";
        char d[]="d";
        if(q[0]==buffer[0]){
            printf("Saliendo...\n");
            close(sd);
            break;
        }else{
            time_t now;
            struct tm *tm;
       
            now = time(NULL);
            tm = localtime(&now);
            char f[64];
         
        if(d[0]==buffer[0]){
            strftime(f, sizeof(f), "%x", tm);
            sendto(sd,f,sizeof(f),0,(struct sockaddr*)&cliente,clientelen);
        }else{
        if(t[0]==buffer[0]){
             strftime(f, sizeof(f), "%c", tm);
             sendto(sd,f,sizeof(f),0,(struct sockaddr*)&cliente,clientelen);
            
        }else{
            printf("Comando %s no soportado\n",buffer);
        }
        }
            
        }
    }
     
   
return 0;
}