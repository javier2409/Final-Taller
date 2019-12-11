/*
Escribir un programa ISO C que procese el archivo de texto cuyo nombre es recibido como parámetro.
El procesamiento consiste en leer oraciones y suprimir aquellas que tengan más de 3 palabras. Asuma
que el archivo no puede cargarse en memoria, pero una oración sí puede.
*/

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>

#define BUFSIZE 100

int readline(char* buffer, FILE* file, int bytesread){
    memset(buffer, 0, BUFSIZE);
    fseek(file, bytesread, SEEK_SET);
    int i = 0;
    while (i < BUFSIZE){
        fread(&buffer[i], 1, 1, file);
        i++;
        if (buffer[i-1] == '\n') break;
    }
    printf("reading line: %s", buffer);
    return i;
}

void parseline(char* buffer, FILE* file){
    printf("parsing: %s", buffer);
    int words = 0;
    for (int i = 0; i < BUFSIZE; i++){
        if (buffer[i] == ' ') words++;
        if (buffer[i] == '\n') {words++; break;}
    }
    if (words <= 3){
        fseek(file, 0, SEEK_END);
        for (int i = 0; i < BUFSIZE; i++){
            fwrite(&buffer[i], 1, 1, file);
            if (buffer[i] == '\n') break;
        }
    }
}

void finish(FILE* file, int length){
    fseek(file, 0, SEEK_END);
    int total = ftell(file);

    int newlength = total - length;

    for (int i = 0; i < newlength; i++){
        fseek(file, length+i, SEEK_SET);
        char buf;
        fread(&buf, 1, 1, file);
        fseek(file, i, SEEK_SET);
        fwrite(&buf, 1, 1, file);
    }

    ftruncate(fileno(file), newlength);
}

int main(int argc, char** argv){

    if (argc != 2) return 1;

    FILE* file = fopen(argv[1], "r+");

    char buffer[BUFSIZE];
    int bytesread = 0;
    fseek(file, 0, SEEK_END);
    int file_length = ftell(file);

    while (bytesread < file_length){
        bytesread += readline(buffer, file, bytesread);
        parseline(buffer, file);    
    }

    finish(file, file_length);

    fclose(file);
}
