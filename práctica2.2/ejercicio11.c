#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <unistd.h>



int main(int argc, char *argv[]){
struct stat sb;         
if (argc<2 || stat(argv[1], &sb) == -1) {
               perror("stat");
               exit(EXIT_FAILURE);
} else{


switch (sb.st_mode & S_IFMT) {  
           case S_IFREG: ;
                    char  hh[200];
                    strcpy(hh,argv[1]);
                    char  ss[200];
                    strcpy(ss,argv[1]);
                    
                    if(link(argv[1],strcat(hh,".hard"))==0 && symlink(argv[1],strcat(ss,".sym"))==0){
                        printf("Enlaces creados\n");
                    }else{
                        printf("Enlaces no creados\n");
                        perror("Error: ");
                    }
                    
           break;
           default:       printf("Solo los ficheros ficheros son soportados\n"); 
           break;
}
}
return 0;
}