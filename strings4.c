/*
Escriba una función C que reciba 1 cadena (T), un arreglo de cadenas (L) y la longitud del arreglo
(Q). La función debe buscar ocurrencias en todas las cadenas provistas en L dentro de T y retornar un
valor total de coincidencias encontradas. Las coincidencias pueden aparecer en cualquier posición de
T y pueden ser múltiples, es decir, pueden ser 0, 1 o más coincidencias.
*/

/*
NOTA: No entendi la parte de "todas las cadenas provistas en L DENTRO de T" y que "las coincidencias
pueden aparecer en cualquier posicion de T". No le encuentro el sentido asi que asumo que quisieron decir
encontrar la cantidad de veces que aparece T en las cadenas de L, ejemplo:

T = "hola"

L = "hola"
    "hola123"
    "asdsdf"
    "qwertyhola"

Devolvería 3.
*/

#include <string.h>
#include <stdio.h>
//Asumo todo como null-terminated
int funcion(const char* T, const char** L, const int Q){
    int long_t = strlen(T);
    int ocurrencias = 0;
    for (int cadena = 0; cadena < Q; cadena++){
        for (int caracter = 0; L[cadena][caracter+long_t-2] != 0; caracter++){
            if (strncmp(T, &L[cadena][caracter], long_t) == 0)
                ocurrencias++;
        }
    }
    return ocurrencias;    
}

//Esto no se pide, es para probar
int main(int argc, char** argv){
    //Voy a tomar el primer argumento como T y los siguientes como L
    if (argc < 2) return 1;
    const char* T = argv[1];
    const char** L = &(argv[2]);
    const int Q = argc - 2;
    printf("Ocurrencias: %d \n", funcion(T, L, Q));
    return 0;
}