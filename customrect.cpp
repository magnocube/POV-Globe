#include "customrect.h"

CustomRect::CustomRect()
{
    x_location =0;
    y_location =0;
    width =50;
    height =50;
    color = Qt::green;
    rotation =0;
    lineColor = Qt::black;
    lineThickness =1;


    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);


}

QRectF CustomRect::boundingRect() const
{
    return QRectF(x_location,y_location,width,height);
}

void CustomRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->rotate(rotation);

    QRectF rec = boundingRect();



//    QBrush brush(color);
//    QPen pen(lineColor);

//    pen.setWidth(lineThickness);


//    painter->setPen(pen);
//    painter->setBrush(brush);


//    painter->drawRect(rec);






    painter->setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(rec, borderRadius, borderRadius);
    QPen pen(lineColor, lineThickness);
    painter->setPen(pen);
    painter->fillPath(path, color);
    painter->drawPath(path);
}

void CustomRect::resize(int w, int h)
{
    width = w;
    height = h;
}

void CustomRect::newProperties(int width, int height, int lineThichness, int rotation, QColor backColor, QColor lineColor, int borderRadius)
{
    qDebug() << width << "   " << height << "   " << lineThichness << "   " << rotation << "   " << backColor.name() << "   " << lineColor.name() << "  " << borderRadius;
    this->width = width;
    this->height = height;
    this->lineThickness = lineThichness;
    this->rotation = rotation;
    this->color = backColor;
    this->lineColor = lineColor;
    this->borderRadius = borderRadius;
     emit updateGraphics();
}



void CustomRect::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e)
{


    CustomRect_Editor * myEditor = new CustomRect_Editor(width,height,color,lineColor,lineThickness,rotation,borderRadius);  //dont forget to delete this pointer from the heap when the wondow closes
    connect(myEditor,SIGNAL(propertyChanged(int,int,int,int,QColor,QColor,int)),this,SLOT(newProperties(int,int,int,int,QColor,QColor,int)));

    myEditor->show();
    //Todo,,, find a solution to removing the windows


}
