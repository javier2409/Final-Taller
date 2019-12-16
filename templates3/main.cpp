#include <iostream>
#include "template.h"

class Ejecutable{
    public:
        void ejecutar(){
            std::cout << "El ejecutable fue ejecutado" << std::endl;
        }
};

int main(){
    Ejecutable ejec;
    Delegador<Ejecutable> delegador(&ejec);

    delegador.ejecutar();

    return 0;
}