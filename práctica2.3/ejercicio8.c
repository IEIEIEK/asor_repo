#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void atributos();
int main(int argc,char * argv[]) {

    int fd=open("/tmp/daemon.out",O_CREAT | O_RDWR,0666);
    int fd2=open("/tmp/daemon.err",O_CREAT | O_RDWR,0666);
    int fdin=open("/dev/null",O_RDONLY);
    
     if ((argc<2) || (fd==-1) || (fd2==-1) || (fdin==-1)) {
             perror("Error al abrir/crear archivo, asegurate de tener permisos");
            exit(EXIT_FAILURE);
    }else{
    
    pid_t pid=fork();

    switch(pid){
        case 0:{
        setsid();
        //chdir("/tmp");
        if(dup2(fd,1)==-1 || dup2(fd2,2)==-1 || dup2(fdin,0)==-1){
            perror("Error on dups");
        }
        close(fd);
        close(fd2);
        close(fdin);
        if( execvp(argv[1],argv+1 )==-1){
           perror("Exec erorr\n");
        }
        break;
        }
        case -1:
        perror("fork");
        close(fd);
        close(fd2);
        close(fdin);
        exit(1);
        break;
        default:
        close(fd);
        close(fd2);
        close(fdin);
        //el padre no hace nada
        break;
    }
    
    }
   return 0;
}

