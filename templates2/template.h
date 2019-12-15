/*
Escriba una clase template llamada Sumador que reciba por constructor un vector de elementos genéri-
cos. La clase Sumador debe incluir un método llamado ‘sumar’ que acumule los valores del vector
recibido y retorne un nuevo objeto del tipo genérico. ¿Qué restricciones se le piden al tipo genérico en
la definición de Sumador?
*/

//El tipo generico debe tener definido el operador + y el operador =

#include <vector>

template<class T>
class Sumador{
    private:
        std::vector<T> elementos;
    public:
        Sumador(std::vector<T>& elementos) : elementos(elementos){}
        T sumar(){
            T ret_val = elementos[0];
            for (auto iter = ++elementos.begin(); iter != elementos.end(); iter++){
                ret_val += *iter;
            }
            return ret_val;
        }
};