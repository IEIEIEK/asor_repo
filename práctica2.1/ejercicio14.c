#include <time.h>
#include <stdio.h>

int main()
{
    struct tm *lt;
    time_t t = time(NULL);
    lt = localtime(&t);
    printf("Año: %i\n", 1900+lt->tm_year);
    return 1;
}