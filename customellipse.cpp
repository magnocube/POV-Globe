#include "customellipse.h"

CustomEllipse::CustomEllipse()
{
    x_location =0;
    y_location =0;
    width =50;
    height =50;
    color = Qt::blue;
    rotation =0;
    lineColor = Qt::black;
    lineThickness =1;


    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);



}

QRectF CustomEllipse::boundingRect() const
{
    return QRectF(x_location,y_location,width,height);
}

void CustomEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();


    QBrush brush(color);
    QPen pen(lineColor);
    pen.setWidth(lineThickness);




    painter->setPen(pen);
    painter->setBrush(brush);
    painter->rotate(rotation);
    painter->drawEllipse(rec);
}

void CustomEllipse::newProperties(int width, int height, int lineThichness, int rotation, QColor backColor, QColor lineColor)
{
    qDebug() << width << "   " << height << "   " << lineThichness << "   " << rotation << "   " << backColor.name() << "   " << lineColor.name();
    this->width = width;
    this->height = height;
    this->lineThickness = lineThichness;
    this->rotation = rotation;
    this->color = backColor;
    this->lineColor = lineColor;

    emit updateGraphics();
}

void CustomEllipse::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e)
{
    CustomEllipse_Editor * myEditor = new CustomEllipse_Editor(width,height,color,lineColor,lineThickness,rotation);  //dont forget to delete this pointer from the heap when the wondow closes
    connect(myEditor,SIGNAL(propertyChanged(int,int,int,int,QColor,QColor)),this,SLOT(newProperties(int,int,int,int,QColor,QColor)));

    myEditor->show();
    //Todo,,, find a solution to removing the dialogs (memory leaking)

}


