/*
Escribir un programa ISO C que procese el archivo “valuesword.dat” sobre sí mismo, eliminando los
words (2 bytes) múltiplos de 16
*/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define BUFSIZE 100

int main(){
    FILE* file = fopen("valuesword.dat", "r+");

    int read_cursor = 0;
    int write_cursor = 0;
    while(!feof(file)){
        char buffer[BUFSIZE];
        memset(buffer, 0, BUFSIZE);

        fseek(file, read_cursor, SEEK_SET);
        fread(buffer, 2, 1, file);
        read_cursor = ftell(file);

        fseek(file, write_cursor, SEEK_SET);
        if (atoi(buffer)%16 != 0){
            fwrite(buffer, 2, 1, file);
            write_cursor = ftell(file);
        }
    }

    fflush(file);
    fclose(file);
}
