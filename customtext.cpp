#include "customtext.h"

CustomText::CustomText()
{
    x_location =0;
    y_location =0;
    width =200;
    height =50;
    color = Qt::red;
    textString = "enter Text";
    size = 10;

    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);



}

QRectF CustomText::boundingRect() const
{
    return QRectF(x_location,y_location,width,height);
}

void CustomText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();

    QPen pen(color);


    painter->setFont(font);
    painter->rotate(rotation);


    painter->setPen(pen);
    painter->drawText(rec,textString,QTextOption());
}

void CustomText::newProperties(int size,int rotation ,QColor color,QFont font, QString text)
{
    qDebug() << size << "   " << rotation << "   " << color.name() << "   " << font.toString() ;

    this->rotation = rotation;
    this->color = color;
    this->font = font;
    this->textString = text;

     emit updateGraphics();
}

void CustomText::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e)
{
    CustomText_Editor * myEditor = new CustomText_Editor(size,rotation ,color, font, textString);  //dont forget to delete this pointer from the heap when the wondow closes
    connect(myEditor,SIGNAL(propertyChanged(int,int,QColor,QFont,QString)),this,SLOT(newProperties(int,int,QColor,QFont,QString)));

    myEditor->show();
    //Todo,,, find a solution to removing the windows

}


