/*
Crear una aplicacion gráfica que dibuje un triangulo rojo sobre un fondo verde
*/

#include <QApplication>
#include "window.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}