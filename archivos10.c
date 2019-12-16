/*
Escribir un programa C que reciba por argumento el nombre de un archivo de texto y lo procese sobre
sí mismo (sin crear archivos intermedios). El procesamiento consiste en eliminar todo carácter que no
sea letra (a-Z o A-Z) ni número (0-9).
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>

int file_get_length(FILE* file){
    struct stat stats;
    fstat(fileno(file), &stats);
    return stats.st_size;
}

char file_read_byte(FILE* file, int pos){
    char buf = 0;
    fseek(file, pos, SEEK_SET);
    fread(&buf, 1, 1, file);
    return buf;
}

void file_write_byte(FILE* file, int pos, char byte){
    fseek(file, pos, SEEK_SET);
    fwrite(&byte, 1, 1, file);
}

bool byte_is_letter_or_number(char byte){
    return ((byte >= 'a' && byte <= 'z') || (byte >= 'A' && byte <= 'Z') || (byte >= '0' && byte <= '9'));
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r+");

    int length = file_get_length(file);

    int write_cursor = 0;
    for (int read_cursor = 0; read_cursor < length; read_cursor++){
        char byte = file_read_byte(file, read_cursor);
        if (byte_is_letter_or_number(byte)){
            file_write_byte(file, write_cursor, byte);
            write_cursor++;
        }
    }

    ftruncate(fileno(file), write_cursor);
    fflush(file);
    fclose(file);
}