#ifndef CUSTOMIMAGE_H
#define CUSTOMIMAGE_H


#include <QGraphicsObject>
#include <QPainter>
#include <QDateTime>
#include <QMessageBox>

#include "customimage_editor.h"
#include <QDebug>

class CustomImage : public QGraphicsObject
{
    Q_OBJECT

public:
    CustomImage();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void resize(int w, int h);
    void setImage(QImage image);

private:
    int x_location;
    int y_location;
    int width;
    int height;
    QColor color;
    int rotation;
    QColor lineColor;
    int lineThickness;
    int borderRadius;

    QImage originalImage;
    QImage resisedImage;

signals:
    void updateGraphics();


public slots:
    void newProperties(int width, int height, int lineThichness, int rotation, QColor backColor, QColor lineColor, int borderRadius);


protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent  *e);
};

#endif // CUSTOMIMAGE_H
