#include <unistd.h>
#include <stdio.h>

int main() {
    int rc = setuid(0);

    if (rc == -1) 
    {
        perror("Error setuid()");
        return -1;
    }
    return 1;
}