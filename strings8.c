/*
Implemente la función char* substract(const char* s, unsigned short inicio, unsigned short fin) que
procese la secuencia s y retorne una nueva cadena de caracteres con la copia de s salvo aquellos
caracteres comprendidos entre los índices inicio y fin. Considere las condiciones de borde.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* substract(const char* s, unsigned short inicio, unsigned short fin){
    if (fin < inicio || fin >= strlen(s)) return NULL;
    int new_len = strlen(s) - (fin - inicio + 1) + 1;
    char* new_string = malloc(new_len* sizeof(char));
    memset(new_string, 0, new_len*sizeof(char));
    int new_index = 0;
    for (int i = 0; i < strlen(s); i++){
        if (!(i >= inicio && i <= fin)){
            new_string[new_index] = s[i];
            new_index++;
        }
    }
    return new_string;
}

//Para probar
int main(){
    char* x = substract("No vas a aprobar el final", 0, 2);
    printf("%s\n", x);
    free(x);
}
