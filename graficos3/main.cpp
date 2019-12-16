/*
Escriba una rutina de interfaz gráfica que lance una aplicación de ventana simple, con un cuadro de
texto y un botón. Al presionar el botón, se debe borrar el valor ingresado por el usuario en el cuadro
de texto.
*/

#include <QApplication>
#include "window.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}