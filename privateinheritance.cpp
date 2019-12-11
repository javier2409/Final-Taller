class A{
    protected:
        int a;
    public:
        A(){
            a = 0;
        }
        void add(int n){
            a+=n;
        }
};

class B: private A{
    public:
        B(): A(){}
        int addA(){
            //B puede usar los metodos de A, dentro de B se sabe que hereda de A
            A::add(1);
            return a;
        }
};

int main(){
    A a;
    B b;

    //no puedo usar el metodo de A a traves de B porque la herencia
    //es privada, desde afuera no sé que B hereda de A.
    //b.add();

    b.addA();
}


