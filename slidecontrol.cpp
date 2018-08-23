#include "slidecontrol.h"
#include "ui_slidecontrol.h"

#include <QDateTime>

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
    ui->imageLabel->setPixmap(QPixmap::fromImage(theSlide->getImage()));
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
void SlideControl::sendSettings()
{
        QByteArray header(5,'^');  //^ is the default value
        header[0]=0;
        header[1] = (char)(128-ui->rotatieSlider->value());
        header[2] = (char)ui->brightnessSlider->value();
        header[3] = (char)ui->gammaSlider->value();
        header[4] = 1;
        udpToLedsConnection->sendToLeds(header);
        qDebug() << "new settings sended";
}
void SlideControl::sendGamma(int gamma)
{
        QByteArray gammaTable(256,'0');
        for(float i=0.0; i<=255.0; i++) {
              gammaTable[(int)i]=(uint8_t)(pow(i / 255.0,(gamma/50.0)) * 255.0 + 0.5);
         }
        QByteArray header(5,'0');  //^ is the default value
        header[0]= 0;
        header[1] = 0;
        header[2] = 0;
        header[3] = 0;
        header[4] = 3;
        QByteArray toSend = gammaTable;
        toSend.append(header);
        udpToLedsConnection->sendToLeds(toSend);
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


    //qDebug() <<  result.width() <<  "  " << result.height();

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
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
     QString path = QDir::currentPath();
    QImage imageToSend = PrepreImageForSending(image);



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
    qDebug() << "path for video: " << path;

    QImage videoImage(path);
    videoImage = videoImage.scaled(xResolution, yResolution, Qt::IgnoreAspectRatio);
//    QLabel *l = ui->imageLabel;
//    QPainter p(l);
//    p.drawImage(0,0,videoImage);
    sendImage(videoImage);

    currentVideoFrame+=2;
    if(currentVideoFrame > numVideoFrames){
        if(ui->loopCheckBox->isChecked()){
            //videoTimer->stop();
        }
        currentVideoFrame=0;
    }
    videoTimer->setInterval(ui->contrastSlider->value());

}
void SlideControl::handleScreen()
{
    if (screen)
    {
        QImage toSend = screen->grabWindow(0).toImage().scaled(xResolution, yResolution, Qt::IgnoreAspectRatio);;
        sendImage(toSend);
    } else{
        qDebug() << "no screen";
    }
}

void SlideControl::on_contrastSlider_valueChanged(int value)
{
    videoTimer->setInterval(ui->contrastSlider->value());
    screenTimer->setInterval(ui->contrastSlider->value());
}
void SlideControl::on_compressieSlider_valueChanged(int value)
{
    // do nothing
}
void SlideControl::on_gammaSlider_valueChanged(int value)
{
    sendGamma(value);
}
void SlideControl::on_rotatieSlider_valueChanged(int value)
{
    sendSettings();
}
void SlideControl::on_brightnessSlider_valueChanged(int value)
{
    sendSettings();
}
void SlideControl::on_verticalSlider_valueChanged(int value)
{

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


