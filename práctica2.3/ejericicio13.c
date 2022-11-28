#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>
volatile int borrar=1;
void handler(int signal){
      if(signal==SIGUSR1){
            borrar=0;
            printf("Se ha recibido la señal SIGUSR1\n");
      }else{
        printf("La alarma ha sonado\n");
      }
}
//primero hay que exportar la variable de entorno export SLEEP_SECS=50
int main(int argc, char * argv[]) {
    if(argc<2){
      printf("Error pocos argumentos\n");
      return -1;
    }
    struct sigaction sigact;
    
  alarm(atoi(argv[1]));
  signal(SIGALRM,handler);
  sigaction(SIGUSR1, NULL,&sigact);
  sigact.sa_handler=handler;
  sigaction(SIGUSR1, &sigact,NULL);
  sigset_t set;
  sigfillset(&set);
  sigdelset(&set,SIGALRM);//lo que hacemos es llenarlo de todas las señales, y quitamos con la que queremos que despierte
  printf("Se suspendera durante %i segundos\n",atoi(argv[1]));
  sigsuspend(&set);
  if(borrar==1){
    printf("Se va a borrar ejercicio13\n");
    
    unlink(argv[0]);
  return 0;
  }else{
       printf("No se va a borrar ejercicio13\n");
  }

  
   return 0;
}
