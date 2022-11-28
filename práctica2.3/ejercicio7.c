#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
int main(int argc, char *argv[]) {
    //sin usar comillas
    if(argc<=1){
        printf("Error\n");
        return -1;
    }else{
        
       if( execvp(argv[1],argv+1 )==-1){
           perror("Exec erorr\n");
       }else{
           printf("El comando terminó de ejecutarse\n");
       }
    }
   
   return 1;
}
