#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <homepage.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    HomePage hPage;

    void setupLayout();

};

#endif // MAINWINDOW_H
