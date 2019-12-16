/*
Dado un vector de enteros en C++, escriba un procedimiento que retorne el promedio de todos sus
números en punto flotante. Debido a la longitud del vector, se pide que el procesamiento sea en paralelo
con 2 hilos de ejecución. ¿Es necesario realizar un control de concurrencia entre 2 hilos? ¿Por qué?
*/

/*
Con este diseño no hace falta control de concurrencia porque el vector es accesible por posicion y no hace falta recorrerlo secuencialmente ya que cada thread puede acceder a posiciones distintas del vector concurrentemente sin data races.
*/

#include <vector>
#include <thread>
#include <iostream>

void calc_mean(std::vector<int>& vec, float& result, int threadno){
    int vec_size = vec.size();
    int count = 0;
    for (int i = threadno; i < vec_size; i += 2){
        count += vec[i];
    }
    result = (float)count/vec_size;
}

int main(){
    std::vector<int> vec({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20});

    float res1;
    float res2;

    auto h1 = std::thread(calc_mean, std::ref(vec), std::ref(res1), 0);
    auto h2 = std::thread(calc_mean, std::ref(vec), std::ref(res2), 1);

    h1.join();
    h2.join();

    float result = res1 + res2;

    std::cout << "Promedio: " << result << std::endl;

    return 0;
}