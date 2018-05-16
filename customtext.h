#ifndef CUSTOMTEXT_H
#define CUSTOMTEXT_H



#include <QGraphicsObject>
#include <QPainter>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include "customtext_editor.h"


class CustomText : public QGraphicsObject
{
    Q_OBJECT

public:
    CustomText();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int x_location;
    int y_location;
    int width;
    int height;
    QColor color;
    QString textString;
    QFont font;
    int size;
    int rotation;





signals:
    void updateGraphics();

public slots:
    void newProperties(int size,int rotation ,QColor color,QFont font,QString text);



signals:
    void whenClicked(QString name);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent  *e);
};

#endif // CUSTOMTEXT_H
