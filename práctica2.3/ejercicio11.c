#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>

//primero hay que exportar la variable de entorno export SLEEP_SECS=50
int main() {
    
    sigset_t blk_set;
    sigemptyset(&blk_set);
    sigaddset(&blk_set,SIGINT );
    sigaddset(&blk_set,SIGTSTP );
    sigprocmask(SIG_BLOCK, &blk_set,NULL);
    
   char * cc=getenv("SLEEP_SECS");
    int i=atoi(cc);
    printf("El programa entrara en suspension %i segundos\n",i);
    sleep(i);
    sigset_t pendientes;
    sigemptyset(&pendientes);
    sigpending(&pendientes);
    if(sigismember(&pendientes,SIGINT)==1){
        printf("Llego la señal SIGINT\n");
    }
    if(sigismember(&pendientes,SIGTSTP)==1){
        printf("Llego la señal SIGTSTP\n");
        sigset_t blk_set2;
        sigemptyset(&blk_set2);
        sigaddset(&blk_set2,SIGTSTP );
        sigprocmask(SIG_UNBLOCK,&blk_set2,NULL);
        printf("SE REANUDO LA EJECUCIÓN\n");
       return 0;
    }
    sigprocmask(SIG_UNBLOCK,&blk_set,NULL);
   
   return 1;
}
