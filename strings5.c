/*
Escriba una función de C llamada strncat_new que reciba 3 parámetros: dos punteros a carácter
constante (S1 y S2) y un entero sin signo (L). La función debe concatenar S1 con S2 y retornar una
nueva cadena de caracteres considerando L como tamaño máximo para cualquiera de los elementos
(S1, S2 y la nueva cadena). La función debe detectar condiciones de error respecto de la longitud y
retornar NULL en cualquier caso.
*/

/*
NOTA: Asumo que S1 y S2 pueden no estar terminados en '\0' y copio hasta encontrar '\0' (en caso de que lo tenga) o hasta copiar L elementos, lo que ocurra primero. El problema es que de esta forma no puedo detectar errores (¿como se el largo de las cadenas si no son null-terminated?) entonces para cumplir lo que dice el enunciado habria que asumirlas null-terminated y usar strlen (con lo cual para mi no tiene sentido usar una funcion que reciba un tope pero bueno).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strncat_new(const char* S1, const char* S2, const unsigned int L){
    char* buffer = malloc(sizeof(char) * L);
    int s_index = 0;
    while (s_index < L){
        if (S1[s_index] == 0) break;
        buffer[s_index] = S1[s_index];
        s_index++;
    }
    int s2_start = s_index;
    while (s_index < L){
        if (S2[s_index-s2_start] == 0) break;
        buffer[s_index] = S2[s_index-s2_start];
        s_index++;
    }
    char* retvalue = malloc(sizeof(char) * (s_index+1)); //sumo 1 mas para el '\0'
    memset(retvalue, 0, s_index+1);
    strncpy(retvalue, buffer, (s_index));
    free(buffer);
    return retvalue; 
}

//Esto es para probar
int main(int argc, char** argv){
    char* x = strncat_new(argv[1], argv[2], atoi(argv[3]));
    printf("%s \n", x);
    free(x);
}