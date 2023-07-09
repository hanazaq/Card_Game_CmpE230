#ifndef MYCARD_H
#define MYCARD_H
#include <QPushButton>
#include <QPalette>

class mycard : public QPushButton
{
    Q_OBJECT
public:
    mycard(const QString& text,
           QWidget* parent = 0);
    int flipped;
    int out;
};


#endif // MYCARD_H


