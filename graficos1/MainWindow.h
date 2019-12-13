#include <QtWidgets>
#include <QPushButton>
#include <QWidget>

class MainWidget: public QWidget{
    Q_OBJECT
    private:
        QPushButton btn;

    public slots:
        void exitSlot(){
            this->close();
        }
    public:
        MainWidget(QWidget* parent = 0) : QWidget(parent), btn("Cerrar"){
            QObject::connect(&btn, SIGNAL(clicked()), this, SLOT(exitSlot()));
            QGridLayout* layout = new QGridLayout;
            layout->addWidget(&btn, 0, 0);
            setLayout(layout);
        } 
};
