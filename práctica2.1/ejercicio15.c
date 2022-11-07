#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char outstr[200];
    time_t t;
    struct tm *tmp;

    t = time(NULL);
    tmp = localtime(&t);
    if (tmp == NULL) {
        perror("localtime");
        return -1;
    }

    if (strftime(outstr, sizeof(outstr), "%A, %d de %B de %Y, %I:%M", tmp) == 0) {
        fprintf(stderr, "strftime returned 0");
        return -1;
    }

    printf("hoy es \"%s\"\n", outstr);
    return 0;
}
