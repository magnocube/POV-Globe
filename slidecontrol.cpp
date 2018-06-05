#include "slidecontrol.h"
#include "ui_slidecontrol.h"

SlideControl::SlideControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SlideControl)
{
    ui->setupUi(this);



}

SlideControl::~SlideControl()
{
    delete ui;
}

void SlideControl::setCurrentImage(Slide *theSlide)
{
    myCurrentSlide = theSlide;
    ui->imageLabel->setPixmap(QPixmap::fromImage(theSlide->getImage()));
}

void SlideControl::setUpUdpLeds(QString ipstring)
{
    udpToLedsConnection = new MyUDP(this,ipstring);
}


void SlideControl::on_addSlideButton_clicked()
{
    emit NewSlide("default","3image");



}

void SlideControl::on_pushButton_clicked()
{
    emit NewSlide("default","white");
}

void SlideControl::on_addImageButton_clicked()
{
    emit NewSlide("default","image");
}

void SlideControl::on_sendToGlobeButton_clicked()
{

    QString path = QDir::currentPath();
    path.append("/latestSlide.jpg");
    myCurrentSlide->safeToDisk(path);      //safe the image in a relative path to store it.


    QImage image = myCurrentSlide->getImage();
    qDebug() << "image dimaensions: " << QString::number(image.width()) << "  " << QString::number(image.height());

            QMatrix rm;
            rm.rotate(270);
            image = image.transformed(rm);
    qDebug() << "image dimaensions: " << QString::number(image.width()) << "  " << QString::number(image.height());


    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "jpg",25); // writes image into ba in jpg format

    qDebug() << ba.length();


    int parts = ceil((double)ba.length()/PACKETSIZE);
    int progress =0;
    char flowLabel=0;

    for(char part = 0; progress < ba.length();part++){
        int imagePartLength=DATALENGTH;
        if(progress+DATALENGTH>ba.length())
        {
            imagePartLength=ba.length()-progress;
        }
        QByteArray partBuffer = ba.mid(progress,imagePartLength);
        progress+=imagePartLength;

        QByteArray header(10,'^');  //^ is the default value
        header[0] = 0;
        header[1] = (char)(imagePartLength>>8);
        header[3] = part;
        header[4] = parts;
        header[5] = flowLabel;

        QByteArray toSend = header;
        toSend.append(partBuffer);

        udpToLedsConnection->sendToLeds(toSend);
    }

}

void SlideControl::on_safeToPc_clicked()
{
    // get the path..
    myCurrentSlide->safeToDisk("");
}
