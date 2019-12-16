/*
Escribir una función que retorne char* y reciba 3 argumentos: char* string, char car, int qty. La función
debe crear una nueva cadena utilizando los caracteres de string pero reemplazando toda ocurrencia del
carácter car por qty veces dicho carácter.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* funcion(char* string, char car, int qty){
    int new_len = strlen(string)+1;
    for (int i = 0; i < strlen(string); i++){
        if (string[i] == car){
            new_len += (qty - 1);
        }
    }

    char* new_string = malloc(new_len * sizeof(char));
    memset(new_string, 0, new_len*sizeof(char));

    int new_index = 0;
    for (int i = 0; i < strlen(string); i++){
        if (string[i] == car){
            memset(&new_string[new_index], car, qty);
            new_index += qty;
        } else {
            new_string[new_index] = string[i];
            new_index++;
        }
    }
    return new_string;
}

//Esto es para probar
int main(){
    char* x = funcion("hola", 'l', 100);
    printf("%s\n", x);
    free(x);
    return 0;
}