#include <stdio.h>
#include <signal.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int operativa(int *sd){
        char buffer[100];
        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];
        struct sockaddr_storage cliente;
        socklen_t clientelen=sizeof(struct sockaddr_storage);
        ssize_t bytes=recvfrom(*sd,buffer,99,0,(struct sockaddr*)&cliente,
        &clientelen);
        if(bytes!=0){
            
        
        buffer[bytes]='\0';
        getnameinfo((struct sockaddr*)&cliente,clientelen,host,NI_MAXHOST,serv,NI_MAXSERV,0);
        printf("[PID:%i] %i bytes de %s:%s\n",getpid(),clientelen,host,serv);
        char t[]="t";
        char q[]="q";
        char d[]="d";
        if(q[0]==buffer[0]){
            printf("Saliendo...\n");
            close(*sd);
            return -1;
        }else{
            time_t now;
            struct tm *tm;
       
            now = time(NULL);
            tm = localtime(&now);
            char f[64];
         
        if(d[0]==buffer[0]){
            strftime(f, sizeof(f), "%x", tm);
            sendto(*sd,f,sizeof(f),0,(struct sockaddr*)&cliente,clientelen);
        }else{
        if(t[0]==buffer[0]){
             strftime(f, sizeof(f), "%c", tm);
             sendto(*sd,f,sizeof(f),0,(struct sockaddr*)&cliente,clientelen);
            
        }else{
            printf("Comando %s no soportado\n",buffer);
        }
        }
            
        }
        }

        return 0;
}
void child(int s){
    while(waitpid(0,NULL,WNOHANG)!=-1){};

}

int main(int argc, char **argv)
{   
    struct sigaction sa;
    sa.sa_handler=child;
    sa.sa_flags=SA_RESTART;
    sigaction(SIGCHLD,&sa,0);
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
    int i=0;
    for(i=0;i<5;i++){
    pid_t pid=fork();
    
        if(pid==0){
            
            while(1){
                
                int y=operativa(&sd);
                if(y==-1){ break;}
                
            }
                close(sd);
                return 0;
        }else{
                close(sd);
                
        }
    }
return 0;
}

