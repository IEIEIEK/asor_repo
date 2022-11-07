#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){


printf ("Numero max de enlaces: %li\n", pathconf("/", _PC_LINK_MAX));
printf ("Tamaño max de una ruta /: %li\n", pathconf("/", _PC_PATH_MAX));
printf ("Tamaño max de un nombre de fichero: %li\n", pathconf("/", _PC_NAME_MAX));

return 1;
}