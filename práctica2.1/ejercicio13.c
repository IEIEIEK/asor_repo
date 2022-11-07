#include <sys/time.h>
#include <stdio.h>

int main() {
    struct timeval ini, fin;
    gettimeofday(&ini, NULL);

    int i;
    for(i=0; i<1000000; i++);

    gettimeofday(&fin, NULL);

    printf("Ha tardado %li ms en incrementar 1 millones de veces dede %li hasta %li\n", 
    fin.tv_usec - ini.tv_usec, ini.tv_usec, fin.tv_usec);

    return 1;

}