/*
Escribir un programa ISO C que lea el archivo ‘a.txt’ e invierta sus caracteres sin utilizar archivos
intermedios.
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

char file_read_byte(FILE* file, int pos){
    fseek(file, pos, SEEK_SET);
    char buf;
    fread(&buf, 1, 1, file);
    return buf;
}

void file_write_byte(FILE* file, int pos, char byte){
    fseek(file, pos, SEEK_SET);
    fwrite(&byte, 1, 1, file);
}

int main(){
    FILE* file = fopen("a.txt", "r+");
    int cursor_r = file_get_length(file) - 1;
    int cursor_l = 0;

    while (cursor_r > cursor_l){
        char byte_r = file_read_byte(file, cursor_r);
        char byte_l = file_read_byte(file, cursor_l);
        file_write_byte(file, cursor_r, byte_l);
        file_write_byte(file, cursor_l, byte_r);
        cursor_r--;
        cursor_l++;
    }

    fflush(file);
    fclose(file);
}