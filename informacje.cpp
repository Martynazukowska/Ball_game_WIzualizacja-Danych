#include "informacje.h"
#include "ui_informacje.h"

#include <QDebug>

#include <QList>
#include <QSerialPortInfo>
#include <QDateTime>

informacje::informacje(QWidget *parent, QSerialPort *dev) :
    QDialog(parent),
    ui(new Ui::informacje)
{
    ui->setupUi(this);
    device=dev;

}

informacje::~informacje()
{
    delete ui;
}

void informacje::addToLogs(QString x,QString y)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->informacja->append(currentDateTime + "\t X:" + x+"\t Y:"+y);
}




void informacje::on_odswiez_clicked()
{
//    ui->predkoscW->clear();
//    ui->bity_slowaW->clear();
//    ui->ParzystoscW->clear();
//    ui->bity_stopuW->clear();

    qDebug() << "Info";

    QList<QSerialPortInfo> devices; //tworzymy liste obiektów
    devices = QSerialPortInfo::availablePorts();  //przypisujemy wartosc zwracana

    for(int i = 0; i < devices.count(); i++)
    {
      qDebug() << devices.at(i).portName() << devices.at(i).description();

      this->Port=devices.at(i).portName();
      this->Urzadzenie=devices.at(i).description();

      int index = 0;
      if((devices.count() - 1) >= index) {
       devices.at(index);
      }
       devices.at(i).portName();
       //if(ui->port==devices.at(i).portName() + " " + devices.at(i).description()) zapytac sie
       ui->Nazwa_portu_W->addItem(devices.at(i).portName() + " " + devices.at(i).description());
    }
    if(ui->Nazwa_portu_W->count() != 0)
        {
        QString predkoscWq="9600";
        QString bity_slowaWq=tr("8 bits");
        QString ParzystoscWq=tr("No parity");
        QString bity_stopuWq="1";

        ui->predkoscW->setText(predkoscWq);
        ui->bity_slowaW->setText(bity_slowaWq);
        ui->ParzystoscW->setText(ParzystoscWq);
        ui->bity_stopuW->setText(bity_stopuWq);
        }

}





