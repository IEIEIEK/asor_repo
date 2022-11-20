#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){
int fd=open("archivoabierto.txt",O_CREAT,0645);
if(fd==-1){
    perror("Error al abrir/crear archivo");
}else{
    close(fd);
}
return 0;
}