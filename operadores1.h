/*
Declare la clase IPv4 para almacenar una dirección IP. Incluya constructor default, constructor move,
constructor de copia y los siguientes operadores: operator<<, operator==, operator= y operator+.
*/

#include <iostream>

class IPv4{
    private:
        std::string ip;
    public:
        IPv4(); //default
        IPv4(IPv4&& other); //move
        IPv4(IPv4& other);  //copy
        friend std::ostream& operator<<(std::ostream& out, const IPv4& other);
        bool operator==(const IPv4& other) const;
        IPv4& operator=(const IPv4& other); //copy (para que sea move tiene que recibir un && y que no sea const)
        IPv4 operator+(const IPv4& other) const ;
};