#include <iostream>

class Clase1{
    public:
        static int i;
        explicit Clase1(){
            std::cout << "Construyendo un Clase1" << std::endl;
        }
};
int Clase1::i = 10;

static Clase1 x;

int main(){
    std::cout << x.i << std::endl;
    Clase1::i = 5;
    std::cout << x.i << std::endl;
    return 0;
}
