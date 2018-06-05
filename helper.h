#ifndef HELPER_H
#define HELPER_H

#include <QDialog>

namespace Ui {
class helper;
}

class helper : public QDialog
{
    Q_OBJECT

public:
    explicit helper(QWidget *parent = 0);
    ~helper();

private:
    Ui::helper *ui;
};

#endif // HELPER_H
