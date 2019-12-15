/*
Defina la clase Documento que encapsule una cadena de caracteres con el número de documento propi-
amente dicho y otra cadena con el tipo (‘Pasaporte’,‘DNI’, etc). La clase debe incluir: constructor
default, constructor por copia, operadores ==, <<, =.
*/

#include <string>
#include <iostream>

class Documento{
    private:
        std::string numero;
        std::string tipo;
    public:
        Documento(const char* numero, const char* tipo) : numero(numero), tipo(tipo){}
        Documento(Documento& other){
            this->numero = other.numero;
            this->tipo = other.tipo;
        }
        bool operator==(const Documento& other) const{
            if (this->tipo == other.tipo && this->numero == other.numero)
                return true;
            return false;
        }
        friend std::ostream& operator<<(std::ostream& out, const Documento& doc){
            out << "numero: " << doc.numero << " tipo: " << doc.tipo;
        }
        Documento& operator=(const Documento& other){
            this->numero = other.numero;
            this->tipo = other.tipo;
            return *this;
        }
};