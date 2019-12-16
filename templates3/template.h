/*
Escriba una clase templates llamada Delegador que reciba por constructor un puntero a un objeto de
tipo genérico y que a su vez contenga un método llamado ‘ejecutar’. Dicho método no recibe argumentos
y no realiza retorno alguno, pero invoca el método ‘ejecutar’ sobre el objeto recibido en el constructor.
*/

template <class T>
class Delegador{
    private:
        T* objeto;
    public:
        Delegador(T* objeto) : objeto(objeto){}
        void ejecutar(){
            objeto->ejecutar();
        } 
};