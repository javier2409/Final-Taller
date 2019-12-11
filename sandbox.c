#include <stdlib.h>

int main(){
    int (*x)[10];
    x = (int(*)[10])malloc(10*sizeof(int));
    free(x);
}
