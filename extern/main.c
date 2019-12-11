#include <stdio.h>

extern int a;

void externfunc();

int main(){
    a = 0;
    externfunc();
    printf("%d \n", a);
    return 0;
}
