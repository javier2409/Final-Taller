/*
Defina una función C llamada trim_all que reciba una lista de strings L y el tamaño de dicha lista
C. La función debe retornar una nueva lista de strings, que posea copias de los valores recibidos pero
sin carácteres de espacio (" ") en el inicio de cada string. Indique claramente el tipo elegido para las
variables L y C.
*/

#include <string.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

char** trim_all(char** L, int C){
    char** new_list = malloc(C*sizeof(char*));
    for(int i = 0; i < C; i++){
        int len = strlen(L[i]);
        int first_space = 0;
        for(int j = 0; L[i][j] != 0; j++){
            if (L[i][j] != ' '){
                first_space = j;
                break;
            }
        }
        new_list[i] = malloc(len - first_space);
        for (int j = first_space; L[i][j] != 0; j++){
            new_list[i][j-first_space] = L[i][j];
        }
    }
    return new_list;
}

//Esto es para probar, no se pide
int main(int argc, char** argv){
    char** new_list = trim_all(argv, argc);
    for(int i = 0; i < argc-1; i++){
        printf("%s \n", new_list[i]);
        free(new_list[i]);
    }
    free(new_list);
}