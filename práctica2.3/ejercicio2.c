#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
int main() {
    
    struct sched_param param;
    int policy=sched_getscheduler(getpid());

   if(sched_getparam(getpid(),&param)==-1 || policy==-1){
    
     perror("Error de sistema: ");
     
   }else{
       switch(policy){
           case SCHED_FIFO:
           printf("Politica: SCHED_FIFO\n");
           break;
           case SCHED_OTHER:
           printf("Politica: SCHED_OTHER\n");
           break;
           case SCHED_RR:
           printf("Politica: SCHED_RR\n");
           break;
           default:
           break;
       }
     int max=sched_get_priority_max( policy);
     int min=sched_get_priority_min( policy);
     if(max!=-1 && min!=-1){
     printf("Prioridad actual: %i Prioridad maxima:  %d Prioridad minima: %d  \n",param.sched_priority,max,min );
     }
   }
   return 1;
}
