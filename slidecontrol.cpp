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
