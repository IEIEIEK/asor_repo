

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>



int main(int argc, char *argv[]){
    int fd;
     if (argc<2 || (fd=open(argv[1],O_RDWR,0777))==-1) {
             perror("Error al abrir/crear archivo");
               exit(EXIT_FAILURE);
    } else{
     if(lockf(fd,F_LOCK,0)==-1){
          close(fd);
         perror("Error al hacer lock sobre el archivo");
          exit(EXIT_FAILURE);
     }else{
         time_t times;
         time(&times);
         struct tm *tm=localtime(&times);
         printf("Hora: %i , minutos: %i , segundos: %i \n",tm->tm_hour,tm->tm_min,tm->tm_sec);
         sleep(10);
         if(lockf(fd,F_ULOCK,0)==-1){
          close(fd);
          perror("Error al hacer lock sobre el archivo");
          exit(EXIT_FAILURE);
         }
        sleep(10);
        close(fd);
     }

    }
return 0;
}