#include "slide.h"


Slide::Slide(QWidget *parent, QGraphicsScene *myS,const QString oName) : QPushButton(parent)
{
    myObjectName = oName;
    setObjectName(oName);



    myScene = myS;
    minimumSlideSizeWidth = 120;
    minimumSlideSizeHeight = 60;



    this->setMinimumHeight(minimumSlideSizeHeight);
    this->setMinimumWidth(minimumSlideSizeWidth);

    safe();

}

QString Slide::getObjetName()
{
    return objectName();
}

QImage Slide::getImage()
{
    return myImage;
}

QGraphicsScene *Slide::getScene()
{
    return myScene;
}

void Slide::setScene(QGraphicsScene* i)
{
    myScene = i;
    safe();
}

void Slide::setImage(QImage i)
{
    myImage = i;
    myScaledImageForDisplaying = myImage.scaled(minimumSlideSizeWidth, minimumSlideSizeHeight, Qt::IgnoreAspectRatio);
}

void Slide::safe()
{
    //myScene->clearSelection();                                                  // Selections would also render to the file
    myScene->setSceneRect(myScene->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
    QImage image(myScene->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
    image.fill(Qt::transparent);

    QPainter painter(&image);
    myScene->render(&painter);


    myImage = image;
    myScaledImageForDisplaying = myImage.scaled(minimumSlideSizeWidth, minimumSlideSizeHeight, Qt::IgnoreAspectRatio);
    repaint(); //so it updates instantly in the slides
}

void Slide::paintEvent(QPaintEvent *event)  //maybe for displaying an image in sted of a pixmap
{
    QPainter painter(this);
    painter.drawImage(QPoint(0,0),myScaledImageForDisplaying);
}

void Slide::mousePressEvent(QMouseEvent *e)
{
    emit onClick(objectName());
}
