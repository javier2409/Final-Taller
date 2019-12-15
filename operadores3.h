/*
Declare la clase Pagina capaz de almacenar una acumulación de líneas de texto (strings) en cierto orden.
Incluya las operaciones de agregación y eliminación de líneas. La clase debe poseer los operadores
usuales de copia, asignación, salida a flujo (<<), comparación (==), agregación (+), eliminación (-).
Implemente este último operador.
*/

#include <string>
#include <list>

class Pagina{
    private:
        std::list<std::string> lines;
    public:
        Pagina();
        Pagina(const Pagina& other);
        void addLine(std::string line);
        void removeLine(int line_number);
        Pagina& operator=(const Pagina& other);
        friend std::ostream& operator<<(std::ostream& out, const Pagina& pagina);
        Pagina operator+(const Pagina& other) const;
        Pagina operator-(const Pagina& other) const{
            Pagina retpg;
            for (auto& line : lines){
                bool contained = false;
                for (auto& otherline : other.lines){
                    if (line == otherline){
                        contained = true;
                        break;
                    }
                }
                if (!contained)
                    retpg.addLine(line);
            }
            return retpg;
        }
};