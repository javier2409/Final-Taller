#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>

class MainWindow : public QWidget{
    Q_OBJECT
    private:
        QPushButton btn;
        QTextEdit text;
    public:
        MainWindow(QWidget* parent = 0) : QWidget(parent){
            QObject::connect(&btn, SIGNAL(clicked()), &text, SLOT(clear()));
            QGridLayout* layout = new QGridLayout;
            layout->addWidget(&btn, 0, 0);
            layout->addWidget(&text, 0, 1);
            setLayout(layout);
        }
};