#include <iostream>

class Functor{
    private:
        int a,b;
    public:
        Functor(int a, int b) : a(a), b(b){}
        int operator()(){
            return a+b;
        }
};

int main(){
    Functor func(2, 3);

    std::cout << func() << std::endl;
}
