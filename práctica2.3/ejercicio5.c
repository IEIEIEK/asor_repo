#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
int main() {
    
    
   char  *buf=malloc(500);
   struct rlimit lm;
   if(getrlimit(RLIMIT_NOFILE,&lm)==-1){
       perror(" erorr\n");
       return -1;
   }
   getcwd(buf,200);
   int i=lm.rlim_max;
   printf("PID: %i PPID: %i PGID: %i SID:  %i NºMax ficheros abiertos:  %i Directorio actual: %s \n",
   getpid(),getppid(),getpgid(getpid()),getsid(getpid()),i,buf);
   free(buf);
   return 0;
}
