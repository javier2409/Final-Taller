/*
Declare la clase TELEFONO para encapsular una cadena numérica correspondiente a un teléfono.
Incluya al menos: Constructor(área, numero), constructor default y constructor de copia, operador
<<, operador ==, =, long y >>. Implemente el operador >>.
*/

#include <string>
#include <iostream>

class TELEFONO{
    private:
        std::string numero;
    public:
        TELEFONO();
        TELEFONO(std::string& area, std::string& numero);
        TELEFONO(TELEFONO& other);
        friend std::ostream& operator<<(std::ostream& out, const TELEFONO& tel);
        bool operator==(const TELEFONO& other) const;
        TELEFONO& operator=(const TELEFONO& other);
        operator long() const;
        friend std::istream& operator>>(std::istream& in, TELEFONO& tel){
            in >> tel.telefono;
            return in;
        }
};