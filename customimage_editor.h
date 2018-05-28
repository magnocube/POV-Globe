#ifndef CUSTOMIMAGE_EDITOR_H
#define CUSTOMIMAGE_EDITOR_H

#include <QDialog>
#include <QColorDialog>

namespace Ui {
class CustomImage_Editor;
}

class CustomImage_Editor : public QDialog
{
    Q_OBJECT

public:
    explicit CustomImage_Editor(int width, int height, QColor color, QColor lineColor, int lineThickness, int rotation, int borderRadius);
    ~CustomImage_Editor();

private:
    Ui::CustomImage_Editor *ui;
    void saveChanges();
    QColor backgroundColor;
    QColor lineColor;

signals:
    void propertyChanged(int width, int height, int lineThichness, int rotation, QColor backColor, QColor lineColor, int borderRadius);
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
    void on_sizeSliderBorderRadius_valueChanged(int value);
    void on_borderRadiusLineEdit_textChanged(const QString &arg1);
};

#endif // CUSTOMIMAGE_EDITOR_H
