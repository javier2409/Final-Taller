/*
Escribir un programa C que reciba por argumento el nombre de un archivo y lo procese sobre sí mismo
(sin crear archivos intermedios). El procesamiento consiste en eliminar todas las ocurrencias de la
cadena “ABCD”. Por ejemplo: la cadena O1 23 AABCDD 45 debe ser reemplazada por 01 23 AD 45.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

static const char* DEL_STRING = "ABCD";
#define STR_LEN 4

void file_read_bytes(FILE* file, int pos, int len, char* buffer){
    fseek(file, pos, SEEK_SET);
    fread(buffer, len, 1, file);
}

void file_write_bytes(FILE* file, int pos, int len, const char* bytes){
    fseek(file, pos, SEEK_SET);
    fwrite(bytes, len, 1, file);
}

int file_get_length(FILE* file){
    struct stat stats;
    fstat(fileno(file), &stats);
    return stats.st_size;
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r+");

    int f_length = file_get_length(file);

    int i = 0, j = 0, k = 0;
    char buffer[STR_LEN];
    while (i <= (f_length - STR_LEN)){
        file_read_bytes(file, i, STR_LEN, buffer);
        if (strncmp(buffer, DEL_STRING, STR_LEN) == 0){
            i += STR_LEN;
        } else {
            file_write_bytes(file, j, 1, &buffer[0]);
            i++;
            j++;
            if (i == (f_length - STR_LEN + 1)){
                file_write_bytes(file, j, STR_LEN - 1, &buffer[1]);
            }
        }
    }
    ftruncate(fileno(file), j);
    fflush(file);
    fclose(file);
}