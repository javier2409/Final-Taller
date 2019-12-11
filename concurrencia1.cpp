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