#ifndef CUSTOMRECT_H
#define CUSTOMRECT_H


#include <QGraphicsObject>
#include <QPainter>
#include <QDateTime>
#include <QMessageBox>

#include "customrect_editor.h"
#include <QDebug>

class CustomRect : public QGraphicsObject
{
    Q_OBJECT

public:
    CustomRect();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void resize(int w, int h);

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


public slots:
    void newProperties(int width, int height, int lineThichness, int rotation, QColor backColor, QColor lineColor, int borderRadius);


protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent  *e);
};

#endif // CUSTOMRECT_H
