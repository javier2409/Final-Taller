/*
Escriba una función ISO C que permita procesar un archivo de texto sobre sí mismo, que contenga
un palabra por línea. El procesamiento consiste en ordenar las palabras (líneas) alfabéticamente
considerando que el archivo no entra en memoria.
*/

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <memory.h>

#define BUFSIZE 100

bool pasada(FILE* file){
    bool switched = false;
    int cursor_1 = 0;
    int cursor_2 = 0;
    char word_1[BUFSIZE];
    char word_2[BUFSIZE];
    memset(word_1, 0, BUFSIZE);
    memset(word_2, 0, BUFSIZE);

    fgets(word_1, BUFSIZE, file);
    cursor_1 = ftell(file);

    while (true){
        memset(word_1, 0, BUFSIZE);
        memset(word_2, 0, BUFSIZE);

        int beg = cursor_2;
    
        fseek(file, cursor_1, SEEK_SET);
        fgets(word_1, BUFSIZE, file);
        cursor_1 = ftell(file);

        if (strnlen(word_1, BUFSIZE) < 1) break;

        fseek(file, cursor_2, SEEK_SET);
        fgets(word_2, BUFSIZE, file);
        cursor_2 = ftell(file);

        printf("comparing: %s and %s \n", word_2, word_1);
        if (strncasecmp(word_1, word_2, BUFSIZE) < 0){
            fseek(file, beg, SEEK_SET);
            fputs(word_1, file);
            cursor_2 = ftell(file);
            fputs(word_2, file);
            cursor_1 = ftell(file);
            switched = true;
        }        
    }
    return !switched;
}

int main (int argc, char** argv){
    FILE* file = fopen(argv[1], "r+");

    bool exit = false;
    while (!exit){
        exit = pasada(file);
    }

    fflush(file);
    fclose(file);
}
