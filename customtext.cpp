#include "customtext.h"

CustomText::CustomText()
{
    x_location =0;
    y_location =0;
    width =200;
    height =50;
    color = Qt::red;
    textString = "Hello World";

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

    QBrush brush(color);

    painter->setBrush(brush);
    painter->drawText(rec,textString,QTextOption());
}

void CustomText::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e)
{
    QMessageBox msgBox;
    msgBox.setText("you are now editing this item.");
    msgBox.exec();

}


