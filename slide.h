#ifndef SLIDE_H
#define SLIDE_H

#include <QPushButton>
#include <QPixmap>
#include <QGraphicsScene>
#include <QPainter>

class Slide : public QPushButton
{
    Q_OBJECT
public:
    explicit Slide(QWidget *parent = nullptr, QGraphicsScene *myS = new QGraphicsScene(),const QString oName = "");
    QString getObjetName();
    QImage getImage();
    QGraphicsScene *getScene();
    void setScene(QGraphicsScene* i);
    void setImage(QImage i);
    QString myObjectName;

    void safe();
private:
    QPixmap myIconPixmap;
    QGraphicsScene *myScene;
    QImage myImage;
    QImage myScaledImageForDisplaying;
    int minimumSlideSizeWidth, minimumSlideSizeHeight;


protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *e);
signals:
    void onClick(QString name);



public slots:
};

#endif // SLIDE_H
