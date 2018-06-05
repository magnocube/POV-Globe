#include "helper.h"
#include "ui_helper.h"

helper::helper(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helper)
{
    ui->setupUi(this);
}

helper::~helper()
{
    delete ui;
}
