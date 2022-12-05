#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

void atributos();
int main(int argc, char *argv[]) {
    if(argc<4){
      printf("Error pocos argumentos\n");
      return -1;
    }
	
	
    int fd[2];
    if(pipe(fd)==-1){
        printf("Error en la creacion de la tuberia\n");
    }
    pid_t pid=fork();

    switch(pid){
        case 0:{
            if(dup2(fd[0],0)!=-1){
            close(fd[0]);
            close(fd[1]);
            execlp(argv[3],argv[3],argv[4],NULL);
        }
      
        break;
        }
        case -1:
        perror("fork");
        exit(1);
        break;
        default:
        if(dup2(fd[1],1)!=-1){
            close(fd[0]);
            close(fd[1]);
            execlp(argv[1],argv[1],argv[2],NULL);
        }
      
        break;
    }

   return 0;
}