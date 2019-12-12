/*
Dado un vector de enteros en C++, escriba un procedimiento que reciba el vector, lo recorra y genere
un nuevo vector con las potencias de 2 de cada uno de los items del vector original. Para optimizar los
recursos de computación, se pide que se utilicen al menos 2 hilos para realizar el procedimiento. ¿Es
necesario realizar un control de concurrencia entre dichos hilos?
*/

/*
Respuesta: Al menos con esta solucion no hace falta control de concurrencia porque cada hilo accede a 
posiciones distintas del vector y hacer eso es thread-safe.
*/

#include <vector>
#include <list>
#include <thread>
#include <cmath>
#include <iostream>

#define NTHREADS 2

void calc_powers(std::vector<int>& vec, std::vector<int>& res, int n_thread){
    for (int i = n_thread; i < vec.size(); i+=NTHREADS){
        int power = pow(2, vec[i]);
        res[i] = power;
    }
}

int main(){
    /*
    Este vector me deberia llegar como parametro, y esto deberia ser una 
    función, pero lo creo acá y hago todo en el main para poder probar el programa
    */
    std::vector<int> vec({4,7,3,5,1,8,5,6,7,4,4,7,9,10,5,6,8,6,8,5,3,4,5,2,1,9,7});

    // Ya se de antemano que el vector resultante va a tener el mismo tamaño
    std::vector<int> res;
    res.resize(vec.size());

    std::list<std::thread> threads;

    for (int i = 0; i < NTHREADS; i++){
        threads.emplace_back(calc_powers, std::ref(vec), std::ref(res), i);
    }

    for (auto& thread: threads){
        thread.join();
    }

    // Imprimo el vector para chequear el resultado
    for (auto& nbr : res){
        std::cout << nbr << std::endl;
    }
}
