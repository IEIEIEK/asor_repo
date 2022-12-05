#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void atributos();
int main() {
   
	
	
    int p_h[2];
    int h_p[2];
    if(pipe(p_h)==-1 || pipe(h_p)==-1){
        printf("Error en la creacion de la tuberia\n");
    }
    int max=0;
    pid_t pid=fork();

    switch(pid){
        case 0:{
            close(p_h[1]);
            close(h_p[0]);
            while(1){
                char buf[500];
                if(read(p_h[0],&buf,sizeof(buf))<=0){
                    perror("Error de escritura\n");
                    break;
                }
                //printf("\n");
                printf("HIJO>%s\n",buf);
                sleep(1);
                max++;
                if(max==10){
                    char q='q';
                    write(h_p[1],&q,sizeof(q));//No hace falta comprobar errores, pues es logica interna, sabemos lo que se lee y lo que se escribe
                    printf("EL HIJO HA FINALIZADO\n");
                    break;
                }else{
                    char uno='1';
                    write(h_p[1],&uno,sizeof(uno));
                }
            }
            close(p_h[0]);
            close(h_p[1]);
        break;
        }
        case -1:
            perror("fork");
            exit(1);
        break;
        default:{
            char g='-';
            close(p_h[0]);
            close(h_p[1]);
            while(g!='q'){
                char c[500];
                printf("PADRE>");
                scanf("%s",c);
                if(write(p_h[1],&c,sizeof(c))>0){
                    read(h_p[0],&g,sizeof(g));
                     
                    
                }else{
                    perror("Error de escritura\n");
                    break;
                }
            }
            close(p_h[1]);
            close(h_p[0]);
            wait(NULL);
            printf("EL PADRE HA FINALIZADO\n");
        break;
        }
    }

   return 0;
}