#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
int main(int argc, char *argv[]) {
    //usando comillas
    if(argc<=1){
        printf("Error\n");
        return -1;
    }else{
        
       if( system(argv[1])==-1){
           perror("SYSTEM error\n");
       }else{
           printf("El comando terminó de ejecutarse\n");
       }
    }
   
   return 1;
}
