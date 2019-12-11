#include <iostream>

class A{
    protected:
        int a,b;
    public:
        A(int a, int b): a(a), b(b){}
        virtual int operation(){
            return a + b;
        }
};

class B: public A{
        int c;
    public:
        B(int a, int b, int c): A(a,b), c(c){}
        int operation() override{
            return a * b * c;
        }
};

int main(){
    A a = B(1, 2, 3);

    // espero que se llame a B::operation() <--- esto no va a pasar
    std::cout << a.operation() << std::endl;
}
