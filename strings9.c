/*
Escriba una función C que reciba 1 cadena (T) y 1 entero (N); y retorne una nueva cadena cuyo
contenido sea N veces la cadena T utilizando un espacio como separador.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* replicar(char* T, int N){
    //longitud original +1 por el separador, N veces, incluyo un espacio extra al final para el '\0'
    int new_len = (strlen(T) + 1) * N;
    char* new_string = malloc(new_len * sizeof(char));
    memset(new_string, 0, new_len);
    int i = 0;
    while (i < new_len){
        strncpy(&new_string[i], T, strlen(T));
        i += strlen(T);
        new_string[i] = ' ';
        i++;
    }
    new_string[new_len - 1] = 0;
    return new_string;
}

//Para probar
int main(){
    char* x = replicar("hola", 7);
    printf("%s\n", x);
    free(x);
}