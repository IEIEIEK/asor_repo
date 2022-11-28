#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

void atributos();
int main() {
    pid_t pid=fork();

    switch(pid){
        case 0:{
        setsid();
        chdir("/tmp");
        //sleep(3);
        printf("-------PROCESO CREADO----------------------\n");
        atributos();
        printf("-------------------------------------------\n");
      
        break;
        }
        case -1:
        perror("fork");
        exit(1);
        break;
        default:
        printf("-------PROCESO PADRE----------------------\n");
        atributos();
        printf("-------------------------------------------\n");
        sleep(10);
      
        break;
    }
    //no hay que poner wait ya que si no no conseguimos que el hijo se quede zombi o huerfano
   
   return 0;
}


void atributos(){
char  *buf=malloc(500);
   struct rlimit lm;
   if(getrlimit(RLIMIT_NOFILE,&lm)==-1){
       perror(" erorr\n");
    
   }else{
   getcwd(buf,200);
   int i=lm.rlim_max;
   printf("PID: %i PPID: %i PGID: %i SID:  %i NºMax ficheros abiertos:  %i Directorio actual: %s \n",
   getpid(),getppid(),getpgid(getpid()),getsid(getpid()),i,buf);
   free(buf);
   }
}