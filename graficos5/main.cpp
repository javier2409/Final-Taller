/*
Escriba una función que cargue un listbox (combo o dropdown) con 10 strings de la forma “opción xx”,
siendo xx una cadena de 2 dígitos con la forma 01, 02, ..., 10.
*/

#include <QApplication>
#include "window.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}