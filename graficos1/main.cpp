/*
Escriba un pequeño programa de interfaz gráfica que lance una aplicación de ventana simple, con un
único botón. El botón debe tener el texto ‘Cerrar’ que al ser presionado oculta la ventana y cierra el
sistema.
*/

/*
Nota: Para ejecutar este programa correr:
    qmake -project
Despues editar el archivo .pro y agregar la linea:
    QT += gui widgets
Despues correr:
    make
    ./main
*/

#include <QApplication>
#include "MainWindow.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    MainWidget win;
    win.show();
    return app.exec();
}
