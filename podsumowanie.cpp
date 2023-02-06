#include "podsumowanie.h"
#include "ui_podsumowanie.h"

podsumowanie::podsumowanie(QWidget *parent,int wynik) :
    QDialog(parent),
    ui(new Ui::podsumowanie)
{
    ui->setupUi(this);
    ui->wynik->display(wynik);

}

podsumowanie::~podsumowanie()
{
    delete ui;
}
