#ifndef CUSTOMTEXT_EDITOR_H
#define CUSTOMTEXT_EDITOR_H

#include <QDialog>
#include <QColorDialog>
#include <QFontDialog>

namespace Ui {
class CustomText_Editor;
}

class CustomText_Editor : public QDialog
{
    Q_OBJECT

public:
    explicit CustomText_Editor(int size,int rotation ,QColor color,QFont font,QString text);
    ~CustomText_Editor();

private:
    Ui::CustomText_Editor *ui;
    void saveChanges();
    QColor backgroundColor;
    QColor lineColor;
    QFont myFont;

signals:
    void propertyChanged(int size,int rotation ,QColor color,QFont font, QString text);
private slots:
    void on_rotationDial_valueChanged(int value);
    void on_rotationLineEdit_textChanged(const QString &arg1);


    void on_fontButton_clicked();
    void on_colorPicker_clicked();
    void on_sizeSliderSize_valueChanged(int value);
    void on_TextLineEdit_returnPressed();
};

#endif // CUSTOMELLIPSE_EDITOR_H
