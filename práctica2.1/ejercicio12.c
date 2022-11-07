#include <time.h>
#include <stdio.h>

int main()
{
    time_t t;
    printf("Segundos desde Epoch 1970-01-01 00:00:00 +0000, UTC: %li\n", time(&t));
    return 1;
}