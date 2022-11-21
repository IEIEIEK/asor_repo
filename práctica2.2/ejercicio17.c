

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, char *argv[]){
     DIR * fd;
     if (argc<2 || (fd=opendir(argv[1]))==NULL) {
             perror("Error al abrir directorio");
               exit(EXIT_FAILURE);
    } else{
        struct dirent *dirent;
        int sum=0;
        struct stat sb;
        while((dirent=readdir(fd))!=NULL){
            
            char c[500];
            strcpy(c,argv[1]);
            strcat(c,"/");    //anadirle la ruta donde se encuentran el contenido de los ficheros por stat                    
            strcat(c,dirent->d_name); 
            
            if (lstat(c, &sb) == -1) {
                perror("stat");
                exit(EXIT_FAILURE);
            }

            switch (sb.st_mode & S_IFMT) {  //comprueba que tipo de fichero es
                case S_IFDIR: 
                 printf("%s/\n",dirent->d_name);
                    break;
                case S_IFLNK:  ;
                    char buf[500];
                    int y=readlink(c,buf,500);//pasarle la ruta completa
                    buf[y]='\0';//readlink no devuelve el caracter nulo
                    printf("%s->%s\n",dirent->d_name,buf);
                    
                    break;
                case S_IFREG: 
                     if((sb.st_mode &  S_IXUSR) && (sb.st_mode &   S_IXGRP  ) && (sb.st_mode &   S_IXOTH )){ //permisos de x para g , u y o
                             printf("%s*\n",dirent->d_name); 
                     }else{
                        printf("%s\n",dirent->d_name); 
                     }
                     sum=sum+sb.st_size;
                    break;
                default:       printf("desconocida\n"); 
                    break;
            }
        }
        double kb=(double)sum/1000;
        printf("Total KB de ficheros: %f \n",kb); //mostrar 6 decimales
        
     
     closedir(fd);
    }
return 0;
}
