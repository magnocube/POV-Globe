#include "pixeleditor.h"
#include "ui_pixeleditor.h"

PixelEditor::PixelEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PixelEditor)
{
    ui->setupUi(this);
//   scene = new QGraphicsScene(this);
//   ui->pixelGraphicsView->setScene(scene);

//   for(int i = 0; i < 10; i++){
//       for(int j = 0; j <5; j++){
//           QRect r(i*30,j*30,30,30);
//           scene->addRect(r);

//       }
//   }
//   scene->setBackgroundBrush(QBrush(Qt::red));


}

PixelEditor::~PixelEditor()
{
    delete ui;
}

void PixelEditor::setCurrentSlide(Slide *s)
{
    myCurrentSlide = s;
    ui->pixelGraphicsView->setScene(myCurrentSlide->getScene());
    repaint(); //needed for obvious reasons  (forces to repaint the gui)
}

void PixelEditor::on_SafeButton_clicked()
{
//    myCurrentSlide->getScene()->clearSelection();                                                  // Selections would also render to the file
//    myCurrentSlide->getScene()->setSceneRect(scene->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
//    QImage image(myCurrentSlide->getScene()->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
//    image.fill(Qt::transparent);

//    QPainter painter(&image);
//    myCurrentSlide->getScene()->render(&painter);
//    myCurrentSlide->setImage(image);
//    QRectF myRect(10,10,30,30);
//    myCurrentSlide->getScene()->addRect(myRect,QPen(),QBrush());

    myCurrentSlide->safe();
}

void PixelEditor::on_zoomInButton_clicked()
{
    ui->pixelGraphicsView->scale(1.1,1.1);
}

void PixelEditor::on_zoomOutButton_clicked()
{
    ui->pixelGraphicsView->scale(0.9,0.9);
}
