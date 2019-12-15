/*
Escribir un programa C que procese el archivo “numeros.txt” sobre sí mismo (sin crear archivos in-
termedios y sin subir el archivo a memoria). El procesamiento consiste en leer grupos de 5 digitos y
reemplazarlos por 4 caracteres hexadecimales que representen el mismo número leído pero en hexadec-
imal.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

void num_to_hex(const char* num, char* buffer){
    char num_zero[6];
    num_zero[5] = 0;
    strncpy(num_zero, num, 5);
    int number = atoi(num_zero);
    char digit_0;

    for (int i = 0; i < 4; i++){
        int n = ((int)floor(number/pow(16,i)) % 16);
        if (n < 10)
            buffer[3-i] = '0' + n;
        else
            buffer[3-i] = 'A' + n - 10;
    }
}

void file_read_bytes(FILE* file, int pos, int n, char* buffer){
    fseek(file, pos, SEEK_SET);
    fread(buffer, n, 1, file);
}

void file_write_bytes(FILE* file, int pos, int n, const char* buffer){
    fseek(file, pos, SEEK_SET);
    fwrite(buffer, n, 1, file);
}

int file_get_length(FILE* file){
    struct stat stats;
    fstat(fileno(file), &stats);
    return stats.st_size;
}

int main(){
    FILE* file = fopen("numeros.txt", "r+");
    int f_length = file_get_length(file);

    int j = 0;
    for(int i = 0; i <= f_length - 5; i += 5){
        char buffer[5];
        file_read_bytes(file, i, 5, buffer);

        char hex[4];
        num_to_hex(buffer, hex);

        file_write_bytes(file, j, 4, hex);
        j += 4;
    }

    ftruncate(fileno(file), j);
    fflush(file);
    fclose(file);
}
