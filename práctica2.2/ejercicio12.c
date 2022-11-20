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
    if(dup2(fd,1)==-1){
         close(fd);
        perror("Error al redirigir la salida estandar");
               exit(EXIT_FAILURE);
    }else{
        printf("Prueba 1\n");
        printf("Prueba 2\n");
        printf("Prueba 3\n");
        close(fd);
    }

    }
return 0;
}