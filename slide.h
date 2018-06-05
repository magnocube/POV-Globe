#ifndef SLIDE_H
#define SLIDE_H

#include <QPushButton>
#include <QPixmap>
#include <QGraphicsScene>
#include <QPainter>
#include <QImageWriter>
#include <QDebug>
#include <QFileDialog>

class Slide : public QPushButton
{
    Q_OBJECT
public:
    explicit Slide(QWidget *parent = nullptr, QGraphicsScene *myS = new QGraphicsScene(),const QString oName = "",int width = 256, int height = 128);
    QString getObjetName();
    QImage getImage();
    QGraphicsScene *getScene();
    void setScene(QGraphicsScene* i);
    void setImage(QImage i);
    QString myObjectName;

    void safe();
    QString safeToDisk(QString path);
private:
    QPixmap myIconPixmap;
    QGraphicsScene *myScene;
    QImage myImage;
    QImage myScaledImageForDisplaying;
    int minimumSlideSizeWidth, minimumSlideSizeHeight;

    int resolutionX;
    int resolutionY;


protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *e);
signals:
    void onClick(QString name);



public slots:
};

#endif // SLIDE_H
