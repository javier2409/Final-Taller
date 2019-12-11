/*
Escriba un programa que imprima por salida estándar los números entre 1 y 100, en orden ascendente.
Se pide que los números sean contabilizados por una variable global única y que los pares sean escritos
por un hilo mientras que los impares por otro. Contemple la correcta sincronización entre hilos y la
liberación de los recursos utilizados.
*/

#include <thread>
#include <condition_variable>
#include <mutex>

static int x;
static std::condition_variable cv;
static std::mutex mtx;

void add_uneven(){
    std::unique_lock<std::mutex> lock(mtx);
    while (x < 100){
        while ((x % 2) == 0){
            cv.wait(lock);
        }
        if (x < 100) x++;
        cv.notify_all();
    }
}

void add_even(){
    std::unique_lock<std::mutex> lock(mtx);
    while (x < 100){
        while ((x % 2) != 0){
            cv.wait(lock);
        }
        if (x < 100) x++;
        cv.notify_all();
    }
}

int main(int argc, char** argv){
    x = 1;
    auto h1 = std::thread(add_even);
    auto h2 = std::thread(add_uneven);

    h2.join();
    h1.join();

    printf("%d \n", x);
}