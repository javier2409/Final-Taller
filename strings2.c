/*
Escriba un programa C que tome 2 cadenas por línea de comandos: A y B; e imprima la cadena A
después de haber suprimido todas las ocurrencias de B.
Ej: reemp.exe "El final no está aprobado" "no" ---> El final está aprobado
*/
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#define BUFSIZE 100

int main(int argc, char** argv){
    char* A = argv[1];
    char* B = argv[2];
    int len_a = strlen(A);
    int len_b = strlen(B);

    char printable[BUFSIZE];
    memset(printable, 0, BUFSIZE);

    int i = 0;
    int j = 0;
    while (i <= len_a - len_b){
        bool found = strncmp(&A[i], B, len_b) == 0;
        if (found){
            i += len_b;
        } else {
            printable[j] = A[i];
            j++;
            i++;
        }
    }

    for (int k = 0; k < len_b - 1 && (i+k) < len_a; k++){
        printable[j+k] = A[i+k];
    }
    printf("%s \n", printable);
}