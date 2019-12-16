/*
Escribir un programa ISO C que procese el archivo de texto sobre sí mismo. El proceso consiste en
detectar las secuencias de caracteres ‘ABAB’ y reemplazarlas por ‘C’.
*/

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <memory.h>
#include <string.h>

int file_get_length(FILE* file){
    struct stat stats;
    fstat(fileno(file), &stats);
    return stats.st_size;
}

int file_read_byte(FILE* file, char* buf, int read_cursor){
    fseek(file, read_cursor, SEEK_SET);
    fread(buf, 1, 1, file);
    return ftell(file);
}

int file_write_byte(FILE* file, char byte, int write_cursor){
    fseek(file, write_cursor, SEEK_SET);
    fwrite(&byte, 1, 1, file);
    return ftell(file);
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r+");

    int read_cursor = 0;
    int write_cursor = 0;

    char window[4];
    memset(window, 0, 4);
    while(read_cursor < file_get_length(file)){
        char buf;
        read_cursor = file_read_byte(file, &buf, read_cursor);

        char out = window[0];
        window[0] = window[1];
        window[1] = window[2];
        window[2] = window[3];
        window[3] = buf;

        if (out != 0){
            write_cursor = file_write_byte(file, out, write_cursor);
        }

        if (strncmp(window, "ABAB", 4) == 0){
            write_cursor = file_write_byte(file, 'C', write_cursor);
            memset(window, 0, 4);
        }
    }

    for (int i = 0; i < 4; i++){
        if (window[i] != 0)
            write_cursor = file_write_byte(file, window[i], write_cursor);
    }

    ftruncate(fileno(file), write_cursor);
    fflush(file);
    fclose(file);
}