#include <QPainter>
#include <QWidget>
#include <QPoint>

class MainWindow : public QWidget{
    protected:
        void paintEvent(QPaintEvent* event){ 
            QPainter painter(this);      
            static const QPoint points[3] {
                QPoint(150, 0),
                QPoint(300, 300),
                QPoint(0, 300)
            };
            painter.setBrush(Qt::red);
            painter.drawConvexPolygon(points, 3);
            this->setStyleSheet("background-color: green;");
            this->resize(300,300);
        }
};