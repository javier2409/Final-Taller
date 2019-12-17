/*
Escribir un programa C que reciba por argumento el nombre de un archivo, y lo procese sobre sí mismo
(sin crear archivos intermedios). El procesamiento consiste en eliminar todos los espacios duplicados
dejando solamente 1 espacio en su lugar.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>

int file_get_length(FILE* file){
    struct stat st;
    fstat(fileno(file), &st);
    return st.st_size;
}

int file_read_byte(FILE* file, char* buffer, int read_cursor){
    fseek(file, read_cursor, SEEK_SET);
    fread(buffer, 1, 1, file);
    return ftell(file);
}

int file_write_byte(FILE* file, const char buffer, int write_cursor){
    fseek(file, write_cursor, SEEK_SET);
    fwrite(&buffer, 1, 1, file);
    return ftell(file);
}

int main(int argc, char** argv){
    if (argc < 2) return 1;
    FILE* file = fopen(argv[1], "r+");

    int read_cursor = 0;
    int write_cursor = 0;

    char buffer;
    read_cursor = file_read_byte(file, &buffer, read_cursor);
    write_cursor = file_write_byte(file, buffer, write_cursor);

    while(read_cursor < file_get_length(file)){
        char previous = buffer;
        read_cursor = file_read_byte(file, &buffer, read_cursor);
        if (buffer != ' ' || buffer != previous)
            write_cursor = file_write_byte(file, buffer, write_cursor);
    }

    ftruncate(fileno(file), write_cursor);
    fflush(file);
    fclose(file);
}