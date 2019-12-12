/*
Defina un operador global == que toma un vector STL de tipo genérico T y un arreglo de elementos
T. El operador debe retornar un bool indicando si las colecciones son iguales, es decir, si todos los
elementos de T coinciden en ambas colecciones.
*/

#include <vector>
#include <iostream>

template <class T>
bool std::operator==(std::vector<T> vector, T array[]){
    for (int i = 0; i < vector.size(); i++){
        if (vector[i] != array[i])
            return false;
    }
    return true;
}

int main(){
    std::vector<int> vec({1,2,3,4});
    int array[] = {1,2,3,4};

    if (vec == array)
        std::cout << "Son iguales \n";  
}
