/*
Escribir un programa que procese un archivo binario de enteros sin signo sobre sí mismo. El proce-
samiento consiste en leer pares de enteros de 1 byte cada uno y reemplazarlos por 3 enteros (el archivo
se agranda): su suma, su resta y el OR lógico entre ambos.
*/

#include <stdio.h>
#include <sys/stat.h>

int get_current_length(FILE* file){
    struct stat buf;
    fstat(fileno(file), &buf);
    return buf.st_size;
    //fseek(file, 0, SEEK_END);
    //return ftell(file);
}

char read_nth_byte(FILE* file, int n){
    fseek(file, n, SEEK_SET);
    char buf;
    fread(&buf, 1, 1, file);
    return buf;
}

void write_nth_triple_byte(FILE* file, int n, char byte1, char byte2){
    fseek(file, 3*n, SEEK_SET);
    char add = byte1 + byte2;
    char subst = byte1 - byte2;
    char log_or = byte1 | byte2;

    fwrite(&add, 1, 1, file);
    fwrite(&subst, 1, 1, file);
    fwrite(&log_or, 1, 1, file);
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r+b");
    
    int initial_length = get_current_length(file);
    int new_length = initial_length/2 * 3;
    ftruncate(fileno(file), new_length);

    for (int i = initial_length - 2; i >= 0; i -= 2){
        char byte1 = read_nth_byte(file, i);
        char byte2 = read_nth_byte(file, i+1);
        write_nth_triple_byte(file, i, byte1, byte2);
    }

    fflush(file);
    fclose(file);
}
