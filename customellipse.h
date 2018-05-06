#ifndef CUSTOMELLIPSE_H
#define CUSTOMELLIPSE_H



#include <QGraphicsObject>
#include <QPainter>
#include <QDateTime>
#include <QMessageBox>

#include <QDebug>
#include "customellipse_editor.h"




class CustomEllipse : public QGraphicsObject
{
    Q_OBJECT

public:
    CustomEllipse();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int x_location;
    int y_location;
    int width;
    int height;
    QColor color;
    int rotation;
    QColor lineColor;
    int lineThickness;



public slots:
    void newProperties(int width, int height, int lineThichness, int rotation, QColor backColor, QColor lineColor);


signals:
    void whenClicked(QString name);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent  *e);
};

#endif // CUSTOMELLIPSE_H
