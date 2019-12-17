#include <QComboBox>
#include <QWidget>
#include <QGridLayout>

class MainWindow : public QWidget{
    private:
        QComboBox cbx;
    public:
        MainWindow(QWidget* parent = 0) : QWidget(parent){
            for (int i = 1; i <= 10; i++){
                char buf[11];
                std::snprintf(buf, 11, "option %02d", i);
                cbx.addItem(buf);
            }
            QGridLayout* layout = new QGridLayout(this);
            layout->addWidget(&cbx, 0, 0);
            setLayout(layout);
        }
};
