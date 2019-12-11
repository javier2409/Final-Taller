/*
Escribir un programa ISO C que reciba por argumento el nombre de un archivo de texto y lo pro-
cese sobre sí mismo (sin crear archivos intermedios ni subiendo todo su contenido a memoria). El
procesamiento consiste en eliminar todas las líneas de 1 sola palabra.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <memory.h>
#define BUFSIZE 100

bool readline(FILE* file, char* buffer, int* cursor){
    fseek(file, *cursor, SEEK_SET);
    void* r = fgets(buffer, BUFSIZE, file);
    *cursor = ftell(file);
    if (!r) return false;
    return true;
}

bool should_write(char* buffer){
    int words = 0;
    for (int i = 0; i < BUFSIZE; i++){
        if (buffer[i] == ' ') return false;
        if (buffer[i] == '\0' || buffer[i] == '\n') break;
    }
    return true;
}

void writeline(FILE* file, char* buffer, int* cursor){
    fseek(file, *cursor, SEEK_SET);
    fputs(buffer, file);
    *cursor = ftell(file);
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r+");

    int read_c = 0;
    int write_c = 0;
    char buffer[BUFSIZE];
    memset(buffer, 0, BUFSIZE);

    while(readline(file, buffer, &read_c)){
        if (feof(file)) break;
        if (should_write(buffer))
            writeline(file, buffer, &write_c);
        memset(buffer, 0, BUFSIZE);
    }

    ftruncate(fileno(file), write_c);
    fclose(file);
}
