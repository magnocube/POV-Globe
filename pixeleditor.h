#ifndef PIXELEDITOR_H
#define PIXELEDITOR_H

#include <QWidget>
#include <QGraphicsScene>
#include "slide.h"

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

private:
    Ui::PixelEditor *ui;

    Slide *myCurrentSlide;
};

#endif // PIXELEDITOR_H
