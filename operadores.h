/*
Declare la clase IPv4 para almacenar una dirección IP. Incluya constructor default, constructor move,
constructor de copia y los siguientes operadores: operator<<, operator==, operator= y operator+.
*/

#include <iostream>

class IPv4{
    private:
        std::string ip;
    public:
        IPv4();
        IPv4(IPv4&& other);
        IPv4(IPv4& other);
        friend std::ostream& operator<<(std::ostream& out, const IPv4& other);
        bool operator==(const IPv4& other) const;
        IPv4& operator=(const IPv4& other);
        IPv4 operator+(const IPv4& other) const ;
};