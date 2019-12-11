/*
Escriba una función ISO C llamada Replicar que reciba una cadena (S), dos índices (I1 e I2) y una
cantidad (Q). La función debe retornar una copia de S salvo los carácteres que se encuentren entre los
índices I1 e I2 que serán duplicados Q veces.
*/

#include <stdio.h>
#include <memory.h>

// src must be null terminated
void replicar (const char* src, char* dst, int i1, int i2, int q){
    for (int i = 0; i < i1; i++){
        dst[i] = src[i];
    }

    int last_index = i1;
    for (int i = 0; i < q; i++){
        for (int j = 0; j < i2-i1; j++){
            last_index = i1+((i2-i1)*i)+j;
            dst[last_index] = src[i1+j];
        }
    }
    for (int i = i2; src[i] != '\0'; i++){
        dst[last_index+i-i2+1] = src[i];
    }
}

int main (){
    const char* src = "Hola mina xd";
    char dst[50];
    memset(dst, 0, 50);
    replicar(src, dst, 5, 9, 3);
    printf("%s \n", dst);
}
