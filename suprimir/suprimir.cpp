/*
Implemente una función C++ denominada Suprimir que reciba dos listas de elementos y devuelva una
nueva lista con los elementos de la primera que no están en la segunda:
*/
#include <list>
#include <iostream>
#include "template.h"

void printlist(std::list<int>& list, const char* listname){
    std::cout << listname << ": ";
    for (auto& element : list){
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::list<int> list1({1,2,3,4,5,6,7,8});
    std::list<int> list2({2,5,7});
    std::list<int> list3 = suprimir<int>(list1, list2);

    printlist(list1, "lista origen");
    printlist(list2, "suprimir");
    printlist(list3, "lista final");
}
