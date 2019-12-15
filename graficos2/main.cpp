/*
Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje la siguiente
imagen en su área de dibujo.
*/

//NOTA: En el enunciado original se veía la imagen, aca la puse en el archivo image.png

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

int main(int argc, char** argv){
    QApplication app(argc, argv);
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsPixmapItem item(QPixmap("/home/javier/Facultad/Taller/Ejercicios_Final/graficos2/image.png"));
    scene.addItem(&item);
    view.show();
    return app.exec();
}
