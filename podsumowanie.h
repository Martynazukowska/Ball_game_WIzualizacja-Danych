#ifndef PODSUMOWANIE_H
#define PODSUMOWANIE_H

#include <QDialog>

namespace Ui {
class podsumowanie;
}

class podsumowanie : public QDialog
{
    Q_OBJECT

public:
    explicit podsumowanie(QWidget *parent = nullptr,int wynik=0);
    ~podsumowanie();

private:
    Ui::podsumowanie *ui;
};

#endif // PODSUMOWANIE_H
