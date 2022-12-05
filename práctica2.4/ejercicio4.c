#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[]){
    if(argc<2){
        perror("Error de argumentos\n");
    }
    mkfifo("tuberiaa",0777); //si ya esta creada ignoramos el error

    int fd=open("./tuberiaa",O_WRONLY);
    if(fd>0){
        char c[sizeof(argv[1])];
        strcpy(c,argv[1]);
        write(fd,&c,sizeof(c));
        close(fd);
    }else{
        perror("Error de open\n");
    }
return 0;
}