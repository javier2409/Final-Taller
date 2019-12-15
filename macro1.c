/*
Escriba una macro llamada ASSERT. La macro debe recibir como parámetro una condición de código
a validar y un mensaje de error a imprimir por la salida estándar en caso que la condición no se cumpla.
Al imprimir el mensaje, se debe incluir el nombre del archivo C. Ejemplo de uso: ASSERT(div > 0,
“Imposible dividir por 0”)
*/

#include <stdio.h>

#define ASSERT(condition, msg) {\
    if (!condition){\
        printf("Assertion error in file: %s \n", __FILE__);\
        printf("%s \n", msg);\
    }\
}

int main(){
    ASSERT((1 < 0), "1 no es menor a 0");
}
