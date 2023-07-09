#include "mycard.h"

//define the constructor
mycard::mycard( const QString& text,
                QWidget* parent):
    QPushButton(text, parent)
{
    flipped=0;//to check whether it flipped or not
    out=0;//to check whether card is out or not

    QPalette pal = palette();
    pal.setColor(QPalette::Button, QColor(QColorConstants::Svg::lightsteelblue));
    setFlat(true);
    setAutoFillBackground(true);
    setPalette(pal);
    update();
}
