#include "slide.h"


Slide::Slide(QWidget *parent, QGraphicsScene *myS, const QString oName, int width, int height) : QPushButton(parent)
{
    myObjectName = oName;
    setObjectName(oName);

    resolutionX = width;
    resolutionY = height;


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
    safe();
}

void Slide::safe()
{

    //myScene->clearSelection();                                                  // Selections would also render to the file
    myScene->setSceneRect(myScene->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
    QImage image(myScene->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
    image.fill(Qt::transparent);

    QPainter painter(&image);
    myScene->render(&painter);


    myImage = image.scaled(resolutionX, resolutionY, Qt::IgnoreAspectRatio);;

    myScaledImageForDisplaying = myImage.scaled(minimumSlideSizeWidth, minimumSlideSizeHeight, Qt::IgnoreAspectRatio);
    repaint(); //so it updates instantly in the slides
}

QString Slide::safeToDisk(QString path)
{

    QImage imageToSafe = myImage;
    //do edits on 'imageToSafe'




    if(path == ""){   //if no path is given, get a path!.
        QFileDialog dialof(this);
        path =  dialof.getSaveFileName(this,tr("select output folder"),QDir::currentPath(),tr("jpg"));
        path.append(".jpg");

    }
    qDebug() << path;
    qDebug() << QString(imageToSafe.save(path,"jpg",25));   //quallity 25. size of 3.1kb

    return("C:/Users/stefa/desktop");
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
