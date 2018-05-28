#ifndef PIXELEDITOR_H
#define PIXELEDITOR_H

#include <QWidget>
#include <QGraphicsScene>
#include <QString>
#include "slide.h"
#include <QImage>

#include <QDebug>
#include <QFileDialog>

#include "customellipse.h"
#include "customrect.h"
#include "customtext.h"
#include "customimage.h"



namespace Ui {
class PixelEditor;
}

class PixelEditor : public QWidget
{
    Q_OBJECT

public:
    explicit PixelEditor(QWidget *parent = 0);
    ~PixelEditor();
    void setCurrentSlide(Slide *s);

private slots:
    void on_SafeButton_clicked();
    void on_zoomInButton_clicked();
    void on_zoomOutButton_clicked();
    void on_addEllipseButton_clicked();

    void on_addRectangleButton_clicked();

    void on_addTextButton_clicked();

    void on_addImageButton_clicked();

public slots:
    void updateGraphicsview();


private:
    Ui::PixelEditor *ui;
    Slide *myCurrentSlide;
    void setupLayout();

protected:
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent  *e);
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
};

#endif // PIXELEDITOR_H
