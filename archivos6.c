/*
Escriba una rutina que procese un archivo indicado por parámetro sobre sí mismo eliminando todas
las ocurrencias de caracteres repetidos. El procesamiento consiste en detectar toda sucesión de dos o
más carácteres idénticos y reemplazarlos por una única ocurrencia.
*/

#include <stdio.h>
#include <sys/stat.h>

char file_read_nth_byte(FILE* file, int n){
    fseek(file, n, SEEK_SET);
    char buf;
    fread(&buf, 1, 1, file);
    return buf;
}

void file_write_nth_byte(FILE* file, int n, char byte){
    fseek(file, n, SEEK_SET);
    fwrite(&byte, 1, 1, file);
}

int file_get_length(FILE* file){
    struct stat st;
    fstat(fileno(file), &st);
    return st.st_size;
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r+");

    int f_length = file_get_length(file); 
    char byte = file_read_nth_byte(file, 0);
    int j = 0;
    for (int i = 1; i < f_length; i++){
        char newbyte = file_read_nth_byte(file, i);
        if (newbyte != byte){
            file_write_nth_byte(file, j, byte);
            j++;
        }
        byte = newbyte;
    }
    file_write_nth_byte(file, j, byte);

    ftruncate(fileno(file), j);

    fflush(file);
    fclose(file);
}
