#ifndef MYGRID_H
#define MYGRID_H
#include <QGridLayout>
#include <QMessageBox>
#include <QTimer>
#include <QLabel>
#include <QRandomGenerator>
#include <QStringList>
#include <QLabel>
#include <QApplication>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QWidget>
#include <QPushButton>
#include "mycard.h"

//MyGrid is a child of GirdLayout class (inhertance)
class MyGrid : public QGridLayout
{
    Q_OBJECT

public:
    //constuctor
    MyGrid(QWidget *parent = nullptr);

public slots:
    void create_grid(); //called in main func

private:
    //to generate random set of names
    int avliable[15];
    QStringList animals;
    mycard *arr[30]; //array of 30 mycard objects
    mycard *flippedC;
    int score;
    int remaining;
    int stop;
    QLabel *scoreL;
    QLabel *triesL;
    QPalette sample_palette;
private slots:
    QString random_name_generator();
    void flip_card(mycard *card);
};
#endif // MYGRID_H






