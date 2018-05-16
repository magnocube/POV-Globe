#include "customtext_editor.h"
#include "ui_customtext_editor.h"

CustomText_Editor::CustomText_Editor(int size,int rotation ,QColor color,QFont font,QString text) :
    QDialog(),
    ui(new Ui::CustomText_Editor)
{
    ui->setupUi(this);

    backgroundColor = color;
    myFont = font;
    ui->TextLineEdit->setText(text);



    ui->rotationDial->setValue(rotation);
    QString colorStylesheet ="background-color: " ;
            colorStylesheet.append(color.name());
    ui->colorLabelHolder->setStyleSheet(colorStylesheet);
    ui->fontLabel->setText(myFont.toString());


    ui->rotationLineEdit->setText( QString::number(rotation));

    saveChanges();

}

CustomText_Editor::~CustomText_Editor()
{
    delete ui;
}

void CustomText_Editor::on_rotationDial_valueChanged(int value)
{
    ui->rotationLineEdit->setText( QString::number(value));
    saveChanges();
}

void CustomText_Editor::on_rotationLineEdit_textChanged(const QString &arg1)
{
    ui->rotationDial->setValue(arg1.toInt());
    saveChanges();
}



void CustomText_Editor::saveChanges()
{


   int width = 10;
   int height = 10;

   int rotation = ui->rotationDial->value();
   int size = ui->sizeSliderSize->value();
   QString Text = ui->TextLineEdit->text();

   emit propertyChanged(size,rotation ,backgroundColor,myFont, Text);
}









void CustomText_Editor::on_fontButton_clicked()
{

    bool ok;
    myFont = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);
    if (ok) {
        // the user clicked OK and font is set to the font the user selected
    } else {
        // the user canceled the dialog; font is set to the initial
        // value, in this case Helvetica [Cronyx], 10
    }
    saveChanges();
}

void CustomText_Editor::on_colorPicker_clicked()
{
    backgroundColor = QColorDialog::getColor(Qt::black,this,"Choose desired background color");
    QString colorStylesheet ="background-color: " ;
            colorStylesheet.append(backgroundColor.name());
    ui->colorLabelHolder->setStyleSheet(colorStylesheet);
    saveChanges();
}

void CustomText_Editor::on_sizeSliderSize_valueChanged(int value)
{
    ui->SizeLineEdit->setText(QString::number(value));
    myFont.setPointSize(value);
    saveChanges();
}

void CustomText_Editor::on_TextLineEdit_returnPressed()
{
    saveChanges();
}
