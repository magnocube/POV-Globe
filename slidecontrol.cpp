#include "slidecontrol.h"
#include "ui_slidecontrol.h"

#include <QDateTime>
#define LOSSLESS
SlideControl::SlideControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SlideControl)
{
    ui->setupUi(this);

    screen = QGuiApplication::primaryScreen();

    videoTimer = new QTimer(this);
    screenTimer = new QTimer(this);
    connect(videoTimer,SIGNAL(timeout()),SLOT(handleVideo()));
    connect(screenTimer,SIGNAL(timeout()),SLOT(handleScreen()));
    xResolution = 16;
    yResolution = 16;

    ui->recordingStatusLabel->setStyleSheet("background-color: #666666; color: #000000");

}
SlideControl::~SlideControl()
{
    delete ui;
}
void SlideControl::setCurrentImage(Slide *theSlide)
{
    myCurrentSlide = theSlide;
    ui->imageLabel->setPixmap(QPixmap::fromImage(theSlide->getImage().scaled(256, 128)));
}
void SlideControl::setUpUdpLeds(QString ipstring)
{
    udpToLedsConnection = new MyUDP(this,ipstring);
}
void SlideControl::setResolution(int x, int y)
{
    xResolution = x;
    yResolution = y;
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
    QImage image = myCurrentSlide->getImage();
    sendImage(image);
}
void SlideControl:: sendRotationSettings(uint8_t rotation)
{
        QByteArray header(2,'^');  //0 is the default value
        header[0]= 5;//packet type
        header[1] = rotation+128;
        udpToLedsConnection->sendToLeds(header);
        qDebug() << "new rotation sended";
}
void SlideControl::sendBrighnessSettings(uint8_t brighness)
{
        QByteArray header(2,'^');  //0 is the default value
        header[0]= 6;//packet type
        header[1] = brighness;
        udpToLedsConnection->sendToLeds(header);
        qDebug() << "new brighness sended";
}
void SlideControl::sendGamma(int gamma)
{
        QByteArray header(2,'0');  //0 is the default value
        header[0]= 7;//packet type
        header[1] = gamma;;
        udpToLedsConnection->sendToLeds(header);
        qDebug() << "new gamma correction sended";
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
#ifdef LOSSLESS
    //- add them
    QImage result(image.width(), image.height(), image.format()); // image to hold the join of image 1 & 2
    QPainter painter(&result);
    painter.drawImage(0, 0.5*image.height(), image2);                //print image2(64 pixels shifted) above, and image 1 below
    painter.drawImage(0,0,image1);
    painter.end(); //cant save a device that is being painted.
    QMatrix rm;
    rm.rotate(90);
    result = result.transformed(rm);

#else
    QImage shifted1;
    QImage shifted2;
    shifted1 = image2.copy(0,0,0.5*image2.width(),image2.height());
    shifted2 = image2.copy(0.5*image2.width(),0,image2.width(),image2.height());


    //- add them
    QImage result(image.width(), image.height(), image.format()); // image to hold the join of image 1 & 2
    QPainter painter(&result);
    painter.drawImage(0, 0.5*image.height(), shifted2);                //print image2(64 pixels shifted) above, and image 1 below
    painter.drawImage(0.5*image.width(), 0.5*image.height(), shifted1);
    painter.drawImage(0,0,image1);
    painter.end(); //cant save a device that is being painted.
    QMatrix rm;
    rm.rotate(90);
    result = result.transformed(rm);

#endif


    return result;








}
void delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(100);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void SlideControl::sendImage(QImage image)
{
     QString path = QDir::currentPath();

#ifdef LOSSLESS
    int mode=0;
    int dataSize;
    double bytes;
    int xResolution;
    bool clearMemory=false;
    if(ui->resolutionHigh->isChecked())
    {
        xResolution=512;
    }
    else if(ui->resolutionMedium->isChecked())
    {
        xResolution=256;
    }
    else//low resolution
    {
        xResolution=128;
    }
    QImage imageToSend;

    if(ui->degrees360->isChecked())
    {
        imageToSend = PrepreImageForSending(image.scaled(xResolution, image.height()));
        degrees=360;
    }
    else if(ui->degrees240->isChecked())
    {
        imageToSend = PrepreImageForSending(image.scaled(xResolution/1.5, image.height()));
        degrees=240;
    }
    else if(ui->degrees180->isChecked())
    {
        imageToSend = PrepreImageForSending(image.scaled(xResolution/2, image.height()));
        degrees=180;
    }
    if(degrees<oldDegrees)
    {
        clearMemory=true;
    }
    oldDegrees=degrees;
    if(ui->bits4->isChecked())
    {
        mode=1;
    }
    else//8bit
    {
        mode=0;
    }

    bool oneLedStrip=false;
    if(mode==0)
    {
        imageToSend= imageToSend.convertToFormat(QImage::Format_RGB888);
        dataSize=1452;
        bytes=3;
    }
    else if(mode==1)
    {
        imageToSend= imageToSend.convertToFormat(QImage::Format_RGB888);
        dataSize=1452;
        bytes=1.5;
    }
    uchar* bits = imageToSend.bits();
    if(mode==1)//8bit to 4bit conversion
    {
        for(int i=0;i<imageToSend.width() * imageToSend.height()*3;i++)
        {
            if(i%2==0)
            {
                bits[i/2]=bits[i]&0xF0;
            }else
            {
                bits[i/2]+=(bits[i]&0xF0)>>4;
            }
        }
    }
    int imagePart=0;
    for(uint32_t pixelPointer=0;pixelPointer<imageToSend.width() * imageToSend.height()*bytes;pixelPointer+=dataSize)
    {
        int length=dataSize+1;
        if(pixelPointer+dataSize>(imageToSend.width() * imageToSend.height()*bytes))
        {
           length= (imageToSend.width() * imageToSend.height()*bytes)-pixelPointer;
        }
        QByteArray partBuffer = QByteArray::fromRawData((char*)bits+pixelPointer, length);
        QByteArray header(5,0);
        header[0] = 4;
        header[1] = pixelPointer & 0x00ff;
        header[2] =  (pixelPointer & 0x00ff00) >> 8;
        header[3] = (pixelPointer & 0xff0000) >> 16;
        header[4] = mode+((xResolution/64)<<4)+(clearMemory<<3);
         clearMemory=false;
        QByteArray toSend = header;
        toSend.append(partBuffer);

        udpToLedsConnection->sendToLeds(toSend,4210+imagePart%16);
        imagePart++;
        if(imagePart==50)
        {
            delay();
        }
        if(imagePart==80)
        {
            delay();
        }
        if(imagePart==100)
        {
            delay();
        }
    }
#else
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    imageToSend.save(&buffer, "jpg",ui->compressieSlider->value());

//    QFile file(path);
//    file.open(QIODevice::ReadOnly);
//    QByteArray ba = file.readAll();
    qDebug() << ba.length();
    int parts = ceil((double)ba.length()/PACKETSIZE);
    int progress =0;


    for(uint8_t part = 0; progress < ba.length();part++){
        int imagePartLength=DATALENGTH;
        if(progress+DATALENGTH>ba.length())
        {
            imagePartLength=ba.length()-progress;
        }
        QByteArray partBuffer = ba.mid(progress,imagePartLength);
        progress+=imagePartLength;

        QByteArray header(5,'^');  //^ is the default value
        header[0] = 0;
        header[1] = flowLabel;
        header[2] = parts;
        header[3] = part;
        header[4] = 2;//version
        //if(part==parts-1)
        //{
        //    header[3] = 1;
       // }
        qDebug() << part<<" "<<parts<<endl;
        QByteArray toSend = partBuffer;
        toSend.append(header);

        udpToLedsConnection->sendToLeds(toSend);

    }
    flowLabel++;
#endif


}
void SlideControl::handleVideo()
{
    QString path = QDir::currentPath();  //home dir of project
    path.append("/videoMap/image");
    if(currentVideoFrame < 10){
        path.append("000");
    }else if(currentVideoFrame < 100){
        path.append("00");
    }else if(currentVideoFrame < 1000){
        path.append("0");
    }
    path.append(QString::number(currentVideoFrame));
    path.append(".jpg");

    QImage videoImage(path);
    videoImage = videoImage.scaled(xResolution, yResolution, Qt::IgnoreAspectRatio);
//    QLabel *l = ui->imageLabel;
//    QPainter p(l);
//    p.drawImage(0,0,videoImage);
     ui->imageLabel->setPixmap(QPixmap::fromImage(videoImage.scaled(256, 128)));
    sendImage(videoImage);


    currentVideoFrame+=2;
    if(currentVideoFrame > numVideoFrames){
        if(ui->loopCheckBox->isChecked()){
            //videoTimer->stop();
        }
        currentVideoFrame=0;
    }
    videoTimer->setInterval(ui->speedSlider->value());

}
void SlideControl::handleScreen()
{
    if (screen)
    {
        QImage toSend = screen->grabWindow(0).toImage().scaled(xResolution, yResolution, Qt::IgnoreAspectRatio);
        ui->imageLabel->setPixmap(QPixmap::fromImage(toSend.scaled(256, 128)));
        sendImage(toSend);
    } else{
        qDebug() << "no screen";
    }
}

void SlideControl::on_contrastSlider_valueChanged(int value)
{
    videoTimer->setInterval(ui->speedSlider->value());
    screenTimer->setInterval(ui->speedSlider->value());
}

void SlideControl::on_gammaSlider_valueChanged(int value)
{
    sendGamma(value);
}
void SlideControl::on_rotatieSlider_valueChanged(int value)
{
    sendRotationSettings(value);
}
void SlideControl::on_brightnessSlider_valueChanged(int value)
{
    sendBrighnessSettings(value);
}

void SlideControl::on_startVideo_clicked()
{

    QString path = QDir::currentPath();  //home dir of project
    QDir dir(path);
    path.append("/videoMap");


    dir.setPath(path);

    dir.removeRecursively();
    dir.setPath(QDir::currentPath());
    dir.mkdir("videoMap");
    dir.setPath(path);


    //ask for vido
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Video"), "/home", tr("Video Files (*.mp4 *.avi *.gif)"));

    if(fileName == ""){
        return;
    }

    QString command;
    command.append("ffmpeg -i \"");
    command.append(fileName);
    command.append("\" \"");
    command.append(path);
    command.append("/image%04d.jpg\"");
    command.append(" -hide_banner");

    qDebug() << "command for ffmpeg: " << command.toUtf8().constData();

    //split video in frames
    QProcess cmd;
    cmd.setWorkingDirectory(QDir::currentPath());
    cmd.execute(command);
    //cmd.execute("notepad");

    //set some global variables
    numVideoFrames = dir.count() - 2;  // files gaan van 1 tot numVideoFrames.. idk waarom er 2 extra files worden weergegeven.
    currentVideoFrame = 1;
    qDebug() << "total number of frames: " << numVideoFrames;
    //start timer for handleVideo
    videoTimer->start(200); //delay between each frame...
}

void SlideControl::on_pushButton_2_clicked()
{
    videoTimer->stop();
    currentVideoFrame = 0;
}

void SlideControl::on_pushButton_3_clicked()
{
    if(screenStarted)
    {
        ui->recordingStatusLabel->setText("Not recording");
        ui->recordingStatusLabel->setStyleSheet("background-color: #666666; color: #000000");
        screenTimer->stop();
    }else
    {
        screenTimer->start(100);
        ui->recordingStatusLabel->setText("Recording");
        ui->recordingStatusLabel->setStyleSheet("background-color: #aaffaa; color: #000000");

    }
    screenStarted=!screenStarted;
}


