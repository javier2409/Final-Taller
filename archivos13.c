/*
Escriba una rutina que procese un archivo binario indicado por parámetro sobre sí mismo, sumarizando
los listados de números que posee almacenado. La sumarización consiste en recorrer los valores enteros
de 32 bits con signo grabados en formato big-endian y acumular sus valores hasta encontrar el valor
‘OXFFFFFFFF’ que se considera un separador entre listados. Todos los valores enteros detectados
son reemplazados por su sumatoria (en el mismo formato) manteniendo luego el elemento separador.
Considere archivos bien formados.
*/

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <memory.h>
#include <stdint.h>

int file_get_length(FILE* file){
    struct stat st;
    fstat(fileno(file), &st);
    return st.st_size;
}

int file_read_integer(FILE* file, uint32_t* number, int read_cursor){
    fseek(file, read_cursor, SEEK_SET);
    fread(number, 4, 1, file);
    return ftell(file);
}

int file_write_integer(FILE* file, uint32_t number, int write_cursor){
    fseek(file, write_cursor, SEEK_SET);
    fwrite(&number, 4, 1, file);
    return ftell(file);
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r+b");
    int read_cursor = 0;
    int write_cursor = 0;

    uint32_t separator = 0xFFFFFFFF;

    while (read_cursor < file_get_length(file)){
        bool exit = false;
        uint32_t sum = 0;
        while(read_cursor < file_get_length(file)){
            uint32_t number;
            read_cursor = file_read_integer(file, &number, read_cursor);
            if (number == separator)
                break;
            sum += ntohl(number);
        }

        sum = htonl(sum);
        write_cursor = file_write_integer(file, sum, write_cursor);
        if (read_cursor != file_get_length(file))
            write_cursor = file_write_integer(file, separator, write_cursor);
    }

    ftruncate(fileno(file), write_cursor);
    fflush(file);
    fclose(file);
}