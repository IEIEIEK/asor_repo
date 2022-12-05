#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>

int descript(int *f1,int *f2,int ntuberia){
        char buf[256]="-";
        int rtub=read(*f1,&buf,sizeof(buf));
        buf[rtub]='\0';
        if(rtub==0){
                    close(*f1);
                    *f1=open("./tuberiaa2",O_RDONLY | O_NONBLOCK);
                    if(*f1<0){
                        close(*f2);
                        perror("Errro al abrir de nuevo la tuberia\n");
                        return -1;
                    }

        }else{
        printf("Tuberia %i: %s\n",ntuberia,buf);
        }
        return 0;
}
int main(){
    mkfifo("tuberiaa",0777); //si ya esta creada ignoramos el error
    mkfifo("tuberiaa2",0777); //si ya esta creada ignoramos el error
    int fd=open("./tuberiaa",O_RDONLY | O_NONBLOCK);
    int fd2=open("./tuberiaa2",O_RDONLY | O_NONBLOCK);
    int change=0;
    if(fd>=0 || fd2>=0){
        while(change!=-1){
                fd_set set;
                FD_ZERO(&set);
                FD_SET(fd,&set);
                FD_SET(fd2,&set);
                int nfds=0;
                if(fd>fd2){ nfds=fd; } else{ nfds=fd2;}
                change= select(nfds+1,&set,0,0,0);
                if(change==-1){ perror("Error en select\n");
                }else{
                    if(FD_ISSET(fd,&set)){
                             int a=descript(&fd,&fd2,1);
                             if(a<0){break;}
                    }else{ 
                        if(FD_ISSET(fd2,&set)){
                             int a=descript(&fd2,&fd,2);
                              if(a<0){ break;}
                        }
                    }
                }
            }//finwhile
    close(fd);
    close(fd2);
    }else{
        perror("Error de open\n");
    }
return 0;
}
