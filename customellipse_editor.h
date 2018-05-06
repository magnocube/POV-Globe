#ifndef CUSTOMELLIPSE_EDITOR_H
#define CUSTOMELLIPSE_EDITOR_H

#include <QDialog>
#include <QColorDialog>

namespace Ui {
class CustomEllipse_Editor;
}

class CustomEllipse_Editor : public QDialog
{
    Q_OBJECT

public:
    explicit CustomEllipse_Editor(int width,int height,QColor color,QColor lineColor,int lineThickness,int rotation);
    ~CustomEllipse_Editor();

private:
    Ui::CustomEllipse_Editor *ui;
    void saveChanges();
    QColor backgroundColor;
    QColor lineColor;

signals:
    void propertyChanged(int width, int height, int lineThichness, int rotation, QColor backColor, QColor lineColor);
private slots:
    void on_rotationDial_valueChanged(int value);
    void on_rotationLineEdit_textChanged(const QString &arg1);
    void on_sizeSliderWidth_valueChanged(int value);
    void on_widthSizeLineEdit_textChanged(const QString &arg1);
    void on_sizeSliderHeight_valueChanged(int value);
    void on_heigthSizeLineEdit_textChanged(const QString &arg1);
    void on_sizeSliderLineThickness_valueChanged(int value);
    void on_lineThicknessSizeLineEdit_2_textChanged(const QString &arg1);
    void on_colorPicker_clicked();
    void on_pushButton_clicked();
};

#endif // CUSTOMELLIPSE_EDITOR_H
