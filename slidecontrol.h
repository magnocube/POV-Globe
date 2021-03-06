#ifndef SLIDECONTROL_H
#define SLIDECONTROL_H

#include <QWidget>
#include <QScrollArea>
#include <QApplication>
#include "slide.h"
#include "myudp.h"
#include <QFileDialog>
#include <QBuffer>
#include <QMatrix>
#include <QTimer>
#include <QProcess>
#include <QScreen>



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
    void setResolution(int x,int y);


private slots:


    void on_pushButton_clicked();

    void on_addImageButton_clicked();

    void on_sendToGlobeButton_clicked();

    void on_safeToPc_clicked();

    void sendRotationSettings(uint8_t rotation);
    void sendBrighnessSettings(uint8_t brigness);
    void sendGamma(int gamma);
    void handleVideo();
    void handleScreen();
    void on_gammaSlider_valueChanged(int value);

    void on_rotatieSlider_valueChanged(int value);

    void on_brightnessSlider_valueChanged(int value);

    void on_startVideo_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_contrastSlider_valueChanged(int value);


private:
    Ui::SlideControl *ui;
    Slide *myCurrentSlide = nullptr;
    MyUDP *udpToLedsConnection;

    QTimer *videoTimer;
    QTimer *screenTimer;

    bool screenStarted = false;

    const int PACKETSIZE=1460;
    const int DATALENGTH=1455;

    QImage PrepreImageForSending(QImage image);
    void sendImage(QImage image);

    char flowLabel=0;
    int currentVideoFrame;
    int numVideoFrames;
    bool videoIsRunning = false;
    QString fileName;

    int xResolution;
    int yResolution;

    int degrees=360;
    int oldDegrees=360;
    QScreen *screen;

signals:
    void NewSlide(QString type, QString param);



};

#endif // SLIDECONTROL_H
