#include <vector>
#include <iostream>
#include "template.h"

int main(){
    std::vector<int> vec({1,2,3,4,5,6,7});
    Sumador<int> sumador(vec);
    int resultado = sumador.sumar();
    std::cout << "Resultado: " << resultado << std::endl;
    return 0;
}