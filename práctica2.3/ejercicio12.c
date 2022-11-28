#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>
volatile int sigint=0;
volatile int sigtstp=0;
void handler(int signal){
        if(signal==SIGINT){
            sigint++;
        }else{
            sigtstp++;
        }
}
//primero hay que exportar la variable de entorno export SLEEP_SECS=50
int main() {
    struct sigaction sigact;
    struct sigaction sigact2;
  sigaction(SIGINT, NULL,&sigact);
  sigact.sa_handler=handler;
  sigaction(SIGINT, &sigact,NULL);
  sigaction(SIGTSTP, NULL,&sigact2);
  sigact2.sa_handler=handler;
  sigaction(SIGTSTP, &sigact2,NULL);
  while(sigint+sigtstp<10){

  }
  printf("El numero de señales de SIGINT es %i \n",sigint);
  printf("El numero de señales de SIGTSTP es %i \n",sigtstp);
  
   return 1;
}
