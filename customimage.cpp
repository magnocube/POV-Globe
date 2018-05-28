#include "customimage.h"

CustomImage::CustomImage()
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

QRectF CustomImage::boundingRect() const
{
    return QRectF(x_location,y_location,width,height);
}

void CustomImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->rotate(rotation);

    QRectF rec = boundingRect();



//    QBrush brush(color);
//    QPen pen(lineColor);

//    pen.setWidth(lineThickness);


//    painter->setPen(pen);
//    painter->setBrush(brush);


//    painter->drawRect(rec);


    painter->drawImage(rec,resisedImage);
}

void CustomImage::resize(int w, int h)
{
    width = w;
    height = h;
}

void CustomImage::setImage(QImage image)
{
    originalImage = image;
    resisedImage = originalImage.scaled(width, height, Qt::IgnoreAspectRatio);
}

void CustomImage::newProperties(int width, int height, int lineThichness, int rotation, QColor backColor, QColor lineColor, int borderRadius)
{
    qDebug() << width << "   " << height << "   " << lineThichness << "   " << rotation << "   " << backColor.name() << "   " << lineColor.name() << "  " << borderRadius;
    this->width = width;
    this->height = height;
    this->lineThickness = lineThichness;
    this->rotation = rotation;
    this->color = backColor;
    this->lineColor = lineColor;
    this->borderRadius = borderRadius;
    resisedImage = originalImage.scaled(width, height, Qt::IgnoreAspectRatio);
     emit updateGraphics();
}



void CustomImage::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e)
{


    CustomImage_Editor * myEditor = new CustomImage_Editor(width,height,color,lineColor,lineThickness,rotation,borderRadius);  //dont forget to delete this pointer from the heap when the wondow closes
    connect(myEditor,SIGNAL(propertyChanged(int,int,int,int,QColor,QColor,int)),this,SLOT(newProperties(int,int,int,int,QColor,QColor,int)));

    myEditor->show();
    //Todo,,, find a solution to removing the windows


}
