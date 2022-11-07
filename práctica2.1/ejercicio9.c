#include <unistd.h>
#include <sys/types.h>

int main()
{
    printf("UID real del usuario: %d\n", getuid());
    printf("UID efectivo del usuario: %d\n", geteuid());

return 0;
}