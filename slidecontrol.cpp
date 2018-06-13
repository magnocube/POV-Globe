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


    QImage image = myCurrentSlide->getImage();
    QImage imageToSend = PrepreImageForSending(image);



    QImage imageToSafe =imageToSend;
    //do edits on 'imageToSafe'
    path = QDir::currentPath();
    path.append("/testShiftedImage.jpg");
    qDebug() << path;
    qDebug() << QString(imageToSafe.save(path,"jpg",25));   //quallity 25. size of 3.1kb




    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    imageToSafe.save(&buffer, "jpg",25);

//    QFile file(path);
//    file.open(QIODevice::ReadOnly);
//    QByteArray ba = file.readAll();

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
        header[2] = (char)(imagePartLength);
        header[3] = part;
        header[4] = parts;
        header[5] = flowLabel;
        header[6] = (char)ui->rotatieSlider->value();
        header[7] = (char)ui->brightnessSlider->value();
        header[8] = (char)ui->gammaSlider->value();

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

QImage SlideControl::PrepreImageForSending(QImage image)
{
    //- make 2 images, with even and uneven slices
    QImage image1 = QImage(image.width(),image.height()/2,image.format());
    QImage image2 = QImage(image.width(),image.height()/2,image.format());
    for(int i = 0; i< image.height()/2;i++){

        for(int w = 0; w< image.width();w++){
            image1.setPixel(w,i,image.pixel(w,2*i));
            image2.setPixel(w,i,image.pixel(w,2*i+1));
        }

    }


    //- shift 1 image by resulution/2 pixels
    QImage shifted1;
    QImage shifted2;
    shifted1 = image2.copy(0,0,0.5*image2.width(),image2.height());
    shifted2 = image2.copy(0.5*image2.width(),0,image2.width(),image2.height());


    //- add them
    QImage result(image.width(), image.height(), image.format()); // image to hold the join of image 1 & 2
    QPainter painter(&result);
    painter.drawImage(0, 0, shifted2);                //print image2(64 pixels shifted) above, and image 1 below
    painter.drawImage(0.5*image.width(), 0, shifted1);
    painter.drawImage(0,0.5*image.height(),image1);
    painter.end(); //cant save a device that is being painted.

    // rotate them
    QMatrix rm;
    rm.rotate(270);
    result = result.transformed(rm);


    qDebug() <<  result.width() <<  "  " << result.height();

    return result;








}
