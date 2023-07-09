#include "mygrid.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //Qwidget>> boxlayout >> gridlayout
    QApplication a(argc, argv);
    QWidget *main_window = new QWidget;
    QVBoxLayout *box = new QVBoxLayout(main_window);
    MyGrid *my_grid=new MyGrid();
    main_window->setWindowTitle("Card Match Game");
    main_window->resize(700, 200);
    my_grid->create_grid();
    box->addLayout(my_grid);
    //coloring
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::black);
    main_window->setAutoFillBackground(true);
    main_window->setPalette(pal);
    main_window->show();
    return a.exec();
}
