#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(){

struct utsname buf;

int rc = uname(&buf);

if(rc == -1){
    printf("ERROR uname()(%d): %s\n", errno, strerror(errno));
    return -1;
}
else {
printf ("System name: %s\n", buf.sysname);
printf ("Node name: %s\n", buf.nodename);
printf ("Release: %s\n", buf.release);
printf ("Version: %s\n", buf.version);
printf ("Machine: %s\n", buf.machine);
//printf ("Domain name: %s\n", buf.domainname);
}

return 1;
}