#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <iostream>

class MainWindow : public QWidget{
    Q_OBJECT
    private:
        QPushButton btn;
        QTextEdit edit;
    public slots:
        void showText(){
            std::cout << this->edit.toPlainText().toStdString() << std::endl;
        }
    public:
        MainWindow(QWidget* parent = 0) : QWidget(parent){
            QObject::connect(&btn, SIGNAL(clicked()), this, SLOT(showText()));
            QGridLayout* layout = new QGridLayout;
            layout->addWidget(&btn, 0, 0);
            layout->addWidget(&edit, 0, 1);
            setLayout(layout);
        }
};