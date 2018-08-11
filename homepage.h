#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "slidecontrol.h"
#include "pixeleditor.h"
#include "slide.h"
#include "myudp.h"
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include "helper.h"



namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = 0);
    void setupUDP(QString ipString);
    void setupLedUDP(QString ipstring);
    void setResolution(int x, int y);
    ~HomePage();


private:
    Ui::HomePage *ui;

    SlideControl *tab_slideControl;
    PixelEditor *tab_pixelEditor;
    MyUDP *GlobePipeConnection;
    long lastUDPMessageReceivedTime;
    QDateTime *time;
    bool globeIsConnected;

    int resolutionX;
    int resolutionY;

    void addSlideByImage(QImage image);

public slots:
    void addNewSlide(QString type, QString param);
    void slideWantsAttention(QString name);
    void newDataReceived(QString data);
    void getNewSpeed();



private slots:
    void on_pushButton_clicked();
    void on_StopPushButton_clicked();
    void on_GlobeSpeedSlider_valueChanged(int value);
    void on_pushButton_2_clicked();
};

#endif // HOMEPAGE_H
