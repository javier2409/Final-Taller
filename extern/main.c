#include <stdio.h>

extern void (*externfunc)();

int main(){
    externfunc();
    return 0;
}
