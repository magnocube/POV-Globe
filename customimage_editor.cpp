#include "customimage_editor.h"
#include "ui_customimage_editor.h"

CustomImage_Editor::CustomImage_Editor(int width,int height,QColor color,QColor lineColor,int lineThickness,int rotation, int borderRadius) :
    QDialog(),
    ui(new Ui::CustomImage_Editor)
{
    ui->setupUi(this);

    backgroundColor = color;
    lineColor = lineColor;

    ui->sizeSliderWidth->setValue(width);
    ui->sizeSliderHeight->setValue(height);
    ui->rotationDial->setValue(rotation);
    QString colorStylesheet ="background-color: " ;
            colorStylesheet.append(color.name());
    ui->colorLabelHolder->setStyleSheet(colorStylesheet);

    QString colorLineThicknessStylesheet ="background-color: " ;
            colorLineThicknessStylesheet.append(lineColor.name());
    ui->lineColorLabelHolder->setStyleSheet(colorLineThicknessStylesheet);


    ui->widthSizeLineEdit->setText( QString::number(width));
    ui->heigthSizeLineEdit->setText( QString::number(height));
    ui->rotationLineEdit->setText( QString::number(rotation));
    ui->lineThicknessSizeLineEdit_2->setText( QString::number(lineThickness));


    //set border radius
}

CustomImage_Editor::~CustomImage_Editor()
{
    delete ui;
}

void CustomImage_Editor::on_rotationDial_valueChanged(int value)
{
    ui->rotationLineEdit->setText( QString::number(value));
    saveChanges();
}

void CustomImage_Editor::on_rotationLineEdit_textChanged(const QString &arg1)
{
    ui->rotationDial->setValue(arg1.toInt());
    saveChanges();
}

void CustomImage_Editor::on_sizeSliderWidth_valueChanged(int value)
{
    ui->widthSizeLineEdit->setText(QString::number(value));
    saveChanges();
}

void CustomImage_Editor::on_widthSizeLineEdit_textChanged(const QString &arg1)
{
    ui->sizeSliderWidth->setValue(arg1.toInt());
    saveChanges();
}

void CustomImage_Editor::on_sizeSliderHeight_valueChanged(int value)
{
    ui->heigthSizeLineEdit->setText(QString::number(value));
    saveChanges();
}

void CustomImage_Editor::on_heigthSizeLineEdit_textChanged(const QString &arg1)
{
    ui->sizeSliderHeight->setValue(arg1.toInt());
    saveChanges();
}

void CustomImage_Editor::on_sizeSliderLineThickness_valueChanged(int value)
{
    ui->lineThicknessSizeLineEdit_2->setText(QString::number(value));
    saveChanges();
}

void CustomImage_Editor::on_lineThicknessSizeLineEdit_2_textChanged(const QString &arg1)
{
    ui->sizeSliderLineThickness->setValue(arg1.toInt());
    saveChanges();
}

void CustomImage_Editor::saveChanges()
{


   int width = ui->sizeSliderWidth->value();
   int height = ui->sizeSliderHeight->value();
   int lineThickness = ui->sizeSliderLineThickness->value();
   int rotation = ui->rotationDial->value();
   int borderRadius = ui->sizeSliderBorderRadius->value();

   emit propertyChanged(width,height,lineThickness,rotation,backgroundColor,lineColor, borderRadius);
}

void CustomImage_Editor::on_colorPicker_clicked()
{
    backgroundColor = QColorDialog::getColor(Qt::black,this,"Choose desired background color");
    QString colorStylesheet ="background-color: " ;
            colorStylesheet.append(backgroundColor.name());
    ui->colorLabelHolder->setStyleSheet(colorStylesheet);
    saveChanges();
}

void CustomImage_Editor::on_pushButton_clicked()
{
    lineColor= QColorDialog::getColor(Qt::black,this,"Choose desired line color");
    QString colorLineThicknessStylesheet ="background-color: " ;
            colorLineThicknessStylesheet.append(lineColor.name());
    ui->lineColorLabelHolder->setStyleSheet(colorLineThicknessStylesheet);

    saveChanges();
}

void CustomImage_Editor::on_sizeSliderBorderRadius_valueChanged(int value)
{
    ui->borderRadiusLineEdit->setText(QString::number(value));
    saveChanges();
}

void CustomImage_Editor::on_borderRadiusLineEdit_textChanged(const QString &arg1)
{
    ui->sizeSliderBorderRadius->setValue(arg1.toInt());
    saveChanges();
}
