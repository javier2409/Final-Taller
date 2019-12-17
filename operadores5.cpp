/*
Prueba de funcionamiento del operador >>
*/
#include <string>
#include <iostream>
#include <vector>
#include <map>

class CellNumber {
    std::string number;
    std::string area;
    std::string country;
    public:
        friend std::istream& operator>>(std::istream& in, CellNumber& cell){
            in >> cell.number >> cell.area >> cell.country;
            return in;
        }
        void print(){
            std::cout << "Number: " << number << std::endl;
            std::cout << "Area: " << area << std::endl;
            std::cout << "Country: " << country << std::endl;
        }
};

int main(){
    CellNumber cell;
    std::cin >> cell;
    cell.print();
}