/*
Escribir un programa en C que reciba por argumento el nombre de un archivo de texto y lo procese sobre
sí mismo (sin crear archivos intermedios). El procesamiento consiste en reemplazar todas las ocurrencias
de ‘1’, ‘2’ y ‘3’ (con un separador antes y uno después) por ‘uno’, ‘dos’ y ‘tres’, respectivamente.
*/

/*
NOTA: Yo interpreto que hay que reemplazar todos los " 1 ", " 2 " y " 3 " (osea con un espacio antes
y uno despues) por " uno ", " dos ", " tres ", osea que si encuentro "abc1abc" no hago nada, en cambio
"abc 1 abc" lo reemplazo por "abc uno abc". Eso complica bastante las cosas con respecto a si no considerara
si tiene o no espacios antes, asi que no estoy seguro de que sea eso lo que piden.
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

int file_current_length(FILE* file){
    struct stat stats;
    fstat(fileno(file), &stats);
    return stats.st_size;
}

void file_read_byte(FILE* file, int pos, char* buffer){
    fseek(file, pos, SEEK_SET);
    fread(buffer, 1, 1, file);
}

void file_write_bytes(FILE* file, int pos, int len, const char* buffer){
    fseek(file, pos, SEEK_SET);
    fwrite(buffer, len, 1, file);
}

int file_future_length(FILE* file){
    int current_length = file_current_length(file);
    int new_length = current_length;
    char window[3];
    for (int i = 0; i < current_length; i++){
        char buf;
        file_read_byte(file, i, &buf);
        window[0] = window[1];
        window[1] = window[2];
        window[2] = buf;

        if (strncmp(window, " 3 ", 3) == 0)
            new_length += 3;
        if (strncmp(window, " 2 ", 3) == 0)
            new_length += 2;
        if (strncmp(window, " 1 ", 3) == 0)
            new_length += 2;
    }
    return new_length;
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[1], "r+");

    int new_len = file_future_length(file);
    int f_len = file_current_length(file);
    ftruncate(fileno(file), new_len);

    char window[3];
    memset(window, 0, 3);
    int j = new_len, i = f_len - 1;
    while (i >= 0){
        char buf;
        file_read_byte(file, i, &buf);

        char discarded = window[2];
        window[2] = window[1];
        window[1] = window[0];
        window[0] = buf;

        if (discarded != 0){
            j--;
            file_write_bytes(file, j, 1, &discarded);
        }

        if(strncmp(window, " 1 ", 3) == 0){
            j -= 5;
            memset(window, 0, 3);
            file_write_bytes(file, j, 5, " uno ");
        } else
        if(strncmp(window, " 2 ", 3) == 0){
            j -= 5;
            memset(window, 0, 3);
            file_write_bytes(file, j, 5, " dos ");
        } else
        if(strncmp(window, " 3 ", 3) == 0){
            j -= 6;
            memset(window, 0, 3);
            file_write_bytes(file, j, 6, " tres ");
        }
        i--;
    }

    for (int i = 2; i >= 0; i--){
        if (window[i] != 0){
            j--;
            file_write_bytes(file, j, 1, &window[i]);
        }
    }

    fflush(file);
    fclose(file);
}