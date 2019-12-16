/*
Escribir un programa C que reciba por argumento el nombre de un archivo de texto y lo procese sobre sí
mismo (sin crear archivos intermedios). El procesamiento consiste en reemplazar todas las ocurrencias
de ‘UNO’, ‘DOS’ y ‘TRES’ por ‘1’, ‘2’ y ‘3’, respectivamente.
*/

/*
NOTA: Se supone que la convención es llamar "ocurrencia" a la palabra con un espacio antes y uno despues, yo por las dudas lo preguntaria en el final.
*/

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <memory.h>
#include <string.h>

#define BUFSIZE 256

int file_get_length(FILE* file){
    struct stat stats;
    fstat(fileno(file), &stats);
    return stats.st_size;
}

int file_read_next_word(FILE* file, char* buffer, int read_cursor){
    fseek(file, read_cursor, SEEK_SET);
    for(int i = 0; i < BUFSIZE - 1; i++){ //le resto 1 para preservar el caracter nulo al final
        char buf = 0;
        fread(&buf, 1, 1, file);
        read_cursor++;
        if (buf == ' ')
            break;
        else
            buffer[i] = buf;

        if (read_cursor == file_get_length(file))
            break;
    }
    return ftell(file);
}

int file_write_word(FILE* file, char* buffer, int write_cursor){
    fseek(file, write_cursor, SEEK_SET);
    for (int i = 0; i < BUFSIZE; i++){
        if (buffer[i] == 0) break;
        fwrite(&buffer[i], 1, 1, file);
    }
    char space = ' ';
    fwrite(&space, 1, 1, file);
    return ftell(file);
}


int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r+");

    int write_cursor = 0;
    int read_cursor = 0;

    bool exit = false;
    while (read_cursor < file_get_length(file)){
        char buffer[BUFSIZE];
        memset(buffer, 0, BUFSIZE);
        read_cursor = file_read_next_word(file, buffer, read_cursor);

        if (strncmp(buffer, "UNO", 3) == 0){
            write_cursor = file_write_word(file, "1", write_cursor);
        } else if (strncmp(buffer, "DOS", 3) == 0){
            write_cursor = file_write_word(file, "2", write_cursor);
        } else if (strncmp(buffer, "TRES", 3) == 0){
            write_cursor = file_write_word(file, "3", write_cursor);
        } else {
            write_cursor = file_write_word(file, buffer, write_cursor);
        }
    }

    ftruncate(fileno(file), write_cursor);
    fflush(file);
    fclose(file);
}