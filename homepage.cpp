#include "homepage.h"
#include "ui_homepage.h"

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    tab_slideControl = new SlideControl(this);
    tab_pixelEditor = new PixelEditor(this);


    ui->tabWidget->removeTab(0);   //delete the first tab in the tabwidget. it only functions for reviewing the layout.
    ui->tabWidget->addTab(tab_slideControl, "Slide Control");
    ui->tabWidget->addTab(tab_pixelEditor, "Edit Pixels");

    time = new QDateTime(); //time instance that will be accessable in this class
 lastUDPMessageReceivedTime =  time->currentMSecsSinceEpoch();
    ui->connectionStatusLabel->setText("Globe not connected!");
    ui->connectionStatusLabel->setStyleSheet("background-color : rgb(255, 0, 0);\nfont: 25 12pt \"Malgun Gothic Semilight\"; border:2px solid grey; border-radius: 5px;");

    connect(tab_slideControl,SIGNAL(NewSlide(QString,QString)),this,SLOT(addNewSlide(QString,QString)));
    globeIsConnected = false; //when the gui starts the globe can not be instantly connected; (therefore hardcoded)
}

void HomePage::setupUDP(QString ipString) //lot of errors if this method does not get called when the program runs (run from mainwindow.cpp)
{
    GlobePipeConnection = new MyUDP(this,ipString);
    connect(GlobePipeConnection,SIGNAL(newData(QString)),this,SLOT(newDataReceived(QString)));


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(getNewSpeed()));
    timer->start(1000);
}

void HomePage::setResolution(int x, int y)
{
    resolutionX = x;
    resolutionY = y;
}



HomePage::~HomePage()
{
    delete ui;
}

void HomePage::addNewSlide(QString type, QString param) //will be activated on the press of a button (in slidecontrol), and will add a slide to the list
{
    while(1==1){  //needed for break
    QVBoxLayout* myLayout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents_2->layout());
    QImage myImage;
    Slide *s;
    QString slideName = "name" + QString::number(time->currentMSecsSinceEpoch()); // so the name is never the same
    QGraphicsScene* theScene;

    if(type == "default"){
        if(param == "3image"){
            myImage = QImage(":/loginPage/slide.jpg");
        } else if (param == "white"){
            QColor color = QColorDialog::getColor(Qt::white,this,"Choose desired background color");
            myImage = QPixmap(100, 100).toImage();
            myImage.fill(color);
        } else if (param == "image"){
            QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open Image"), "/C", tr("Image Files (*.png *.jpg *.bmp *.jpeg *.gif)"));
            qDebug() << fileName;
            if(fileName != ""){
                 myImage = QImage(fileName);
            } else{
                break;
            }
        }
    }

    theScene = new QGraphicsScene(this);
    myImage = myImage.scaled(resolutionX, resolutionY, Qt::IgnoreAspectRatio);

    QGraphicsPixmapItem *imageItem = new QGraphicsPixmapItem( QPixmap::fromImage(myImage));// mooi verhaal dit
    theScene->addItem(imageItem);



    s = new Slide(this, theScene, slideName);
    myLayout->insertWidget(0,s);


    connect(s,SIGNAL(onClick(QString)),this,SLOT(slideWantsAttention(QString)));
//    Slide *mySlide = ui->scrollAreaWidgetContents_2->findChild<Slide *>("Button");
//    if(mySlide != 0){
//        mySlide->setText("trololol");
//    }


    //het verkrijgven van een pointer naar een widget.: -> dit zal wss moeten worden toegepast in de methode "slideWantsAttention".
    //1. zorg dat het widget een objetname heeft.
    //2. gebruik findchild met een cast
    //2. (voorbeeld):  Slide *mySlide = ui->scrollAreaWidgetContents_2->findChild<Slide *>("Button");
    break; //to exit while loop
    }
}

void HomePage::slideWantsAttention(QString name)//method called when a slide is pressed
{
    ui->label->setText("A BUTTON HAS BEEN PRESSED!!!");
    Slide *currentSlide = ui->scrollAreaWidgetContents_2->findChild<Slide *>(name);
    //currentSlide->hide();
    qDebug() << currentSlide->getObjetName();


    //display the current slide to all the editors...
    tab_slideControl->setCurrentImage(currentSlide);
    tab_pixelEditor->setCurrentSlide(currentSlide);


}

void HomePage::newDataReceived(QString data) //all data received is from the UDP class
{
    lastUDPMessageReceivedTime = time->currentMSecsSinceEpoch();
    ui->label->setText("RPM: "+data);
}

void HomePage::getNewSpeed() //to get new speed AND check if globe is online
{
    long timeSinceLastPacket = time->currentMSecsSinceEpoch()-lastUDPMessageReceivedTime;

    if(timeSinceLastPacket > 2000){
        globeIsConnected = false;
        ui->connectionStatusLabel->setText("Globe not connected!");
        ui->connectionStatusLabel->setStyleSheet("background-color : rgb(255, 0, 0);\nfont: 25 12pt \"Malgun Gothic Semilight\"; border:2px solid grey; border-radius: 5px;");
    } else{
        globeIsConnected = true;
        ui->connectionStatusLabel->setText("Globe connected!");
        ui->connectionStatusLabel->setStyleSheet("background-color : rgb(0, 255, 0);\nfont: 25 12pt \"Malgun Gothic Semilight\"; border:2px solid grey; border-radius: 5px;");
    }
    int value = ui->GlobeSpeedSlider->value();
    GlobePipeConnection->ChangeValue(value); //globe will send udp packet back with the speed
}

void HomePage::on_pushButton_clicked() //startbutton motor with question
{
    QMessageBox::StandardButton reply;

    QMessageBox *mensaje = new QMessageBox(this);
    reply = QMessageBox::question(this, "Please confirm your action", "Are you sure you want to strt the Cat-Schredder?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        GlobePipeConnection->StartGlobe();
    }

}

void HomePage::on_StopPushButton_clicked()
{
    GlobePipeConnection->StopGlobe();
}

void HomePage::on_GlobeSpeedSlider_valueChanged(int value)
{
    GlobePipeConnection->ChangeValue(value);
}
