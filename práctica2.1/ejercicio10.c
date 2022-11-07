#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
/*  getpwuid() functions return a pointer to a  passwd  structure,
    or  NULL  if  the  matching  entry  is not found or an error occurs.  If an error
    occurs, errno is set appropriately.  If one wants to check errno after the  call,
    it should be set to zero before the call.
*/

int main()
{
    struct passwd *userinfo;
    errno = 0;
    userinfo = getpwuid(getuid());
    
    if (userinfo == NULL){
        if(errno != 0){
            printf("ERROR getpwuid()(%d): %s\n", errno, strerror(errno));
        }
        else printf("The  matching  entry  is not found");
        return -1;
    }
    else{
        printf("Nombre de usuario: %s\n", userinfo->pw_name);
        printf("Directorio home: %s\n", userinfo->pw_dir);
        printf("Descripcion del usuario: %s\n", userinfo->pw_gecos);
    
    }
    return 1;
}