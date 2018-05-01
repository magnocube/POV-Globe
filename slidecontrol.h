#ifndef SLIDECONTROL_H
#define SLIDECONTROL_H

#include <QWidget>
#include <QScrollArea>
#include "slide.h"

namespace Ui {
class SlideControl;
}

class SlideControl : public QWidget
{
    Q_OBJECT

public:
    explicit SlideControl(QWidget *parent = 0);
    ~SlideControl();
    void setCurrentImage(Slide *theSlide);



private slots:
    void on_addSlideButton_clicked();

    void on_pushButton_clicked();

    void on_addImageButton_clicked();

private:
    Ui::SlideControl *ui;
    Slide *myCurrentSlide;

signals:
    void NewSlide(QString type, QString param);



};

#endif // SLIDECONTROL_H
