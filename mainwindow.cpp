#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(&hPage);

    setupLayout();
    setLayout(QLayout());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()   //simple login function
{
    QString pw = ui->lineEdit->text();
    QString IP = ui->IPLineEdit->text();
    int x = ui->lineEditX->text().toInt();
    int y = ui->lineEditY->text().toInt();

    if(pw == "1234"){
        ui->stackedWidget->setCurrentWidget(&hPage);
    } else {
        ui->lineEdit->setText("wrong...  try again");
    }
    hPage.setupUDP(IP);
    hPage.setResolution(x,y);
}

void MainWindow::setupLayout()
{
        QPixmap pixmap(":/icons/icons/Staff-Login.jpg");
        QIcon myIcon(pixmap);

        ui->startButton->setIcon(myIcon);
        ui->startButton->setIconSize(QSize(180,60));
        ui->startButton->setStyleSheet("border-radius: 11px;");
        ui->startButton->setText("");



}
