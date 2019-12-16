/*
Escriba una función ISO C llamada ‘split’ que reciba una cadena de caracteres constante ‘S’ y retorne
un puntero a una secuencia con todas las palabras que posee ‘S’. Considere como separador entre
palabras al carácter espacio.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split(const char* S){
    char delim = ' ';
    int cant_palabras = 0;
    int i = 0;
    while(true){
        if (S[i] == delim)
            cant_palabras++;
        else if (S[i] == 0){
            cant_palabras++;
            break;
        }
        i++;
    }
    printf("Cant palabras: %d \n", cant_palabras);
    char** retvalue = malloc(cant_palabras*sizeof(char*));
    
    int inicial = 0;
    for (int i = 0, p = 0; true; i++){
        if (S[i] == delim || S[i] == 0){
            retvalue[p] = malloc(sizeof(char)*(i-inicial+1));
            memset(retvalue[p], 0, (i-inicial+1));
            strncpy(retvalue[p], &S[inicial], (i-inicial));
            inicial = i+1;
            p++;
            if (S[i] == 0) break;
        }
    }
    return retvalue;
}

//Esto es para probar
int main(int argc, char** argv){
    char** x = split("taller de programacion 1 veiga");
    for (int i = 0; i < 5; i++){
        printf("%s \n", x[i]);
        free(x[i]);
    }
    free(x);
}