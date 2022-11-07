#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    int rc = setuid(0);

    if (rc == -1) 
    {
        //perror("Error setuid()");
        printf("ERROR(%d): %s\n", errno,strerror(errno));
        return -1;
    }
    return 1;
}