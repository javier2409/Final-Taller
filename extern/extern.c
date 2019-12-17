#include <stdio.h>

static void externfunc(){
    printf("funcion externa");
}

void (*func)() = externfunc;
