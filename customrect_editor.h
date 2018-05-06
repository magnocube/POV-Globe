#ifndef CUSTOMRECT_EDITOR_H
#define CUSTOMRECT_EDITOR_H

#include <QDialog>
#include <QColorDialog>

namespace Ui {
class CustomRect_Editor;
}

class CustomRect_Editor : public QDialog
{
    Q_OBJECT

public:
    explicit CustomRect_Editor(int width, int height, QColor color, QColor lineColor, int lineThickness, int rotation, int borderRadius);
    ~CustomRect_Editor();

private:
    Ui::CustomRect_Editor *ui;
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

#endif // CUSTOMRECT_EDITOR_H
