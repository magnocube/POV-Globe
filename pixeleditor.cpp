#include "pixeleditor.h"
#include "ui_pixeleditor.h"

PixelEditor::PixelEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PixelEditor)
{
    ui->setupUi(this);

    ui->pixelGraphicsView->acceptDrops(); //------------------------------------------ try to remove when evrrything is done
    setupLayout();


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
    ui->pixelGraphicsView->scale(1.3,1.3);
}

void PixelEditor::on_zoomOutButton_clicked()
{
    ui->pixelGraphicsView->scale(0.7,0.7);
}

void PixelEditor::setupLayout()
{
    int width = 40;
    int height = 40;


    QPixmap pixmapRect(":/icons/icons/rectangle.png");
    QIcon rectIcon(pixmapRect);
    ui->addRectangleButton->setIconSize(QSize(width,height));
    ui->addRectangleButton->setIcon(rectIcon);

    QPixmap pixmapEllipse(":/icons/icons/ellipse.png");
    QIcon ellipseIcon(pixmapEllipse);
    ui->addEllipseButton->setIconSize(QSize(width,height));
    ui->addEllipseButton->setIcon(ellipseIcon);

    QPixmap pixmapText(":/icons/icons/text.png");
    QIcon textIcon(pixmapText);
    ui->addTextButton->setIconSize(QSize(width,height));
    ui->addTextButton->setIcon(textIcon);



}



void PixelEditor::on_addEllipseButton_clicked()
{

    CustomEllipse *ellipse = new  CustomEllipse();
    myCurrentSlide->getScene()->addItem(ellipse);


}

void PixelEditor::on_addRectangleButton_clicked()
{

    CustomRect *rect = new  CustomRect();
    myCurrentSlide->getScene()->addItem(rect);

}

void PixelEditor::on_addTextButton_clicked()
{
    CustomText *text = new CustomText();
    myCurrentSlide->getScene()->addItem(text);

}

