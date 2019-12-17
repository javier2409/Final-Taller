/*
Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje la siguiente
imagen en su área de dibujo.
*/

//NOTA: En el enunciado original se veía la imagen, aca la puse en el archivo image.png

#include <QApplication>

int main(int argc, char** argv){
    QApplication app(argc, argv);
    QWidget view;
    //cambiar la url de la imagen en caso de que este en otro lado
    //puse ".." porque voy a crear el ejecutable en una subcarpeta
    view.setStyleSheet("border-image: url(../image.png) 0 0 0 0 stretch stretch;");
    view.show();
    return app.exec();
}
