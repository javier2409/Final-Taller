#include <list>
#include <thread>
#include <fstream>
#include <mutex>
#include <condition_variable>

typedef struct{
    int num;
    bool present;
    bool closed;
} queue;

static queue x = queue{0, false, false};
static std::mutex mtx;
static std::mutex file_mtx;
static std::condition_variable pop_cv, push_cv;

static void push(int num){
    std::unique_lock<std::mutex> lock(mtx);
    while (x.present)
        push_cv.wait(lock);
    x.num = num;
    x.present = true;
    pop_cv.notify_all();
}

static int pop(){
    std::unique_lock<std::mutex> lock(mtx);
    while (!x.present and !x.closed)
        pop_cv.wait(lock);
    if (x.closed and !x.present)
        throw std::runtime_error("queue closed");
    x.present = false;
    int retval = x.num;
    push_cv.notify_all();
    return retval;
}

static void push_nums(std::list<int>& nums){
    for (auto num : nums){
        push(num);
    }
    std::lock_guard<std::mutex> lock(mtx);
    x.closed = true;
    pop_cv.notify_all();
}

static void pop_nums(std::ofstream& file){
    int num;
    while (true){
        try{
            num = pop();
            std::lock_guard<std::mutex> lock(file_mtx);
            file << num << "\n";
        } catch (std::runtime_error& e){
            printf("%s \n", e.what());
            break;
        }
    }      
}

static void func(std::list<int>& numbers, std::ofstream& file){
    auto h1 = std::thread(push_nums, std::ref(numbers));
    std::list<std::thread> threads;

    for (auto _ : std::list<int>({1,2,3,4,5,6,7,8,9,10})){
        threads.emplace_back(pop_nums, std::ref(file));
    }

    h1.join();
    
    for (auto& thread : threads){
        thread.join();
    }
}

extern int (*f)();

int main(){
    int* (*C)[5];

    std::list<int> numbers;
    int i = 0;
    while (i < 1000){
        numbers.emplace_back(i);
        i++;
    }

    std::ofstream file("file.txt", std::ios_base::out);

    func(numbers, file);
}
