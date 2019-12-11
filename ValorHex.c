/*
Implemente la función void ValorHex(char* hex, int* ent) que interprete la cadena hex (de símbolos
hexadecimales) y guarde el valor correspondiente en el entero indicado por ent.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

void ValorHex(char* hex, int* ent){
    *ent = 0;
    int num = 0;
    int len = strlen(hex);
    for (int i = len - 1; i >= 0; i--){
        switch (hex[i]){
            case '0': num=0; break;
            case '1': num=1; break;
            case '2': num=2; break;
            case '3': num=3; break;
            case '4': num=4; break;
            case '5': num=5; break;
            case '6': num=6; break;
            case '7': num=7; break;
            case '8': num=8; break;
            case '9': num=9; break;
            case 'A':
            case 'a': num=10; break;
            case 'B':
            case 'b': num=11; break;
            case 'C':
            case 'c': num=12; break;
            case 'D':
            case 'd': num=13; break;
            case 'E':
            case 'e': num=14; break;
            case 'F':
            case 'f': num=15; break;
        }
        *ent += pow(16, len - i - 1) * num;
    }
}

int main(int argc, char** argv){
    int number;
    ValorHex(argv[1], &number);
    printf("El numero es: %d \n", number);
}
