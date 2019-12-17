/*
Escribir un programa ISO C que procese el archivo palabras.txt sobre sí mismo. El proceso consiste
en duplicar las palabras que tengan más de 3 vocales distintas.
*/

//Este es el ejercicio mas largo de archivos que vi.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <memory.h>
#define BUFSIZE 256

int file_get_length(FILE* file){
    struct stat st;
    fstat(fileno(file), &st);
    return st.st_size;
}

int file_read_word_backwards(FILE* file, char* buffer, int* word_size, int read_cursor){
    int i = 0;
    while(read_cursor > 0){
        read_cursor--;
        char buf = 0;
        fseek(file, read_cursor, SEEK_SET);
        fread(&buf, 1, 1, file);
        if (buf != ' '){
            buffer[i] = buf;
            i++;
        } else {
            break;
        }
    }
    *word_size = i;
    return read_cursor;
}

int file_write_word_backwards(FILE* file, char* buffer, int word_size, int write_cursor){
    char space = ' ';
    int new_cursor = write_cursor - (word_size + 1);
    
    int i = 0;
    while (i < word_size && write_cursor > 0){
        write_cursor--;
        fseek(file, write_cursor, SEEK_SET);
        fwrite(&buffer[i], 1, 1, file);
        i++;
    }

    if (write_cursor != 0){
        fseek(file, write_cursor - 1, SEEK_SET);
        fwrite(&space, 1, 1, file);
    }

    return new_cursor;
}

bool word_should_duplicate(char* buffer, int word_size){
    int distinct_vocals = 0;
    char* vocals_u = "AEIOU";
    char* vocals_l = "aeiou";

    for (int j = 0; j < 5; j++){
        if (strchr(buffer, vocals_u[j] || strchr(buffer, vocals_l[j])))
            distinct_vocals++;
        /*
        for (int i = 0; i < word_size; i++){
            if(buffer[i] == vocals_l[j] || buffer[i] == vocals_u[j]){
                distinct_vocals++;
                break;
            }
        }
        */
    }
    return (distinct_vocals > 3);
}

int file_calc_new_length(FILE* file){
    int read_cursor = file_get_length(file);
    int new_length = read_cursor;
    while (read_cursor > 0){
        char buffer[BUFSIZE];
        memset(buffer, 0, BUFSIZE);
        int word_size = 0;
        read_cursor = file_read_word_backwards(file, buffer, &word_size, read_cursor);
        if (word_should_duplicate(buffer, word_size))
            new_length += word_size + 1;
    }
    return new_length;
}

int main(){
    FILE* file = fopen("palabras.txt", "r+");
    int new_length = file_calc_new_length(file);

    int read_cursor = file_get_length(file);
    ftruncate(fileno(file), new_length);
    int write_cursor = new_length;

    while (read_cursor > 0){
        char buffer[BUFSIZE];
        memset(buffer, 0, BUFSIZE);
        int word_size = 0;

        read_cursor = file_read_word_backwards(file, buffer, &word_size, read_cursor);
        write_cursor = file_write_word_backwards(file, buffer, word_size, write_cursor);
        if (word_should_duplicate(buffer, word_size)){
            write_cursor = file_write_word_backwards(file, buffer, word_size, write_cursor);
        }
    }
    fflush(file);
    fclose(file);
}