/*
Dado un vector de enteros en C++, escriba un procedimiento que reciba el vector, lo recorra, imprima
su contenido en 2 archivos distintos (a.txt y b.txt) en paralelo y libere los recursos. ¿Es necesario
realizar un control de concurrencia entre los 2 hilos? ¿Por qué?
*/

/*
No es necesario control de concurrencia porque los hilos van a acceder al vector para solo lectura, y van a trabajar sobre archivos distintos
*/

#include <vector>
#include <thread>
#include <fstream>

void escribir(std::vector<int>& vec, const char* filename){
    std::ofstream file(filename, std::ios_base::out);
    for (auto& number : vec){
        file << number;
    }
}

void procedimiento(std::vector<int>& vec){
    auto h1 = std::thread(escribir, std::ref(vec), "a.txt");
    auto h2 = std::thread(escribir, std::ref(vec), "b.txt");
    h1.join();
    h2.join();
}

int main(){
    std::vector<int> vec({1,2,3,4,5,6,7,8,9});
    procedimiento(vec);
}