#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>





int main(){
struct stat sb;  

int fd=open("archivoabierto.txt",O_CREAT,0645);
if(fd==-1){
    perror("Error al abrir/crear archivo");
}else{
    close(fd);
   
if (stat("archivoabierto.txt", &sb) == -1) {
               perror("stat");
               exit(EXIT_FAILURE);
} 
printf("ID del dispositivo (major y minor):  [%lx,%lx]\n", (long) major(sb.st_dev), (long) minor(sb.st_dev));
printf("Numero I-node  %ld\n", (long) sb.st_ino);
printf("Tipo de archivo: ");
switch (sb.st_mode & S_IFMT) {  
           case S_IFDIR:  printf("Directorio\n");
           break;
           case S_IFLNK:  printf("Enlace simbolico\n");
           break;
           case S_IFREG:  printf("Fichero regular\n"); 
           break;
           
           default:       printf("desconocida\n"); 
           break;
}
printf("Ultimo acceso al archivo:  %s", ctime(&sb.st_atime));
}
return 0;
}