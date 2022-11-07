#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {

    int i;
    for (i = 0; i < 256; i++) 
    {
        printf("ERROR(%d): %s\n", i, strerror(i));
    }
    return 1;
}