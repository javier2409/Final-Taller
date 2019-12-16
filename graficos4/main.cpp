/*
Escriba una rutina para ambientes gráficos que exponga una ventana con un cuadro de texto y un
botón. Al realizar click sobre el botón, el sistema debe tomar la información ingresada en el cuadro de
texto e imprimirla por consola.
*/

#include <QApplication>
#include "window.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}