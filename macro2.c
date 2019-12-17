//Ejemplo de macro mal hecha

#include <stdio.h>

//No se respeta la buena practica de poner el parametro entre paréntesis
#define CUBE(A) (A*A*A) 

//No se respeta poner la definicion entre parentesis
#define SUM(A,B) A+B

int main(){
    //Se va a hacer 2+3*2+3*2+3 lo que da 17 ya que se agrupan las multiplicaciones
    if (CUBE(2+3) == 125){
        printf("cube funciona\n");
    }
    printf("CUBE(5) = %d\n", CUBE(2+3));


    //Aca se va a hacer 3+4*2 = 11
    if ((SUM(3,4)*2) == 14){
        printf("sum funciona\n");
    }
    printf("SUM(3,4)*2 = %d\n", SUM(3,4)*2);
}
