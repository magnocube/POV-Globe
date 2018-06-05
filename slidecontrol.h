#ifndef SLIDECONTROL_H
#define SLIDECONTROL_H

#include <QWidget>
#include <QScrollArea>
#include "slide.h"
#include "myudp.h"
#include <QFileDialog>
#include <QBuffer>
#include <QMatrix>

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
    void setUpUdpLeds(QString ipstring);


private slots:
    void on_addSlideButton_clicked();

    void on_pushButton_clicked();

    void on_addImageButton_clicked();

    void on_sendToGlobeButton_clicked();

    void on_safeToPc_clicked();

private:
    Ui::SlideControl *ui;
    Slide *myCurrentSlide;
    MyUDP *udpToLedsConnection;

    const int PACKETSIZE=1460;
    const int DATALENGTH=1450;

signals:
    void NewSlide(QString type, QString param);



};

#endif // SLIDECONTROL_H
