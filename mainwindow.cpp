#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "informacje.h"
#include <QDebug>

#define POLYNOMIAL_9 0x0161

#include <QList>
#include <QSerialPortInfo>
#include <QSerialPort>

#include <QDateTime>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QLCDNumber>
#include <QtOpenGL>
#include <sstream>


typedef unsigned char byte;

unsigned int CRC8_SingleByte_v2(unsigned int Data2){
    unsigned int Poly = (POLYNOMIAL_9 << 7);

    for (byte Idx = 0; Idx < 8; ++Idx){
        if ((Data2 & 0x8000) != 0)
            Data2 ^= Poly;
        Data2 <<=1;
    }
    return Data2;
}

byte CRC8_DataArray(const byte *pData, byte Len){
    unsigned int Data2 = pData[0] << 8;

    for (unsigned int Idx = 1; Idx < Len; ++Idx) {
        Data2 |= pData[Idx];
        Data2 = CRC8_SingleByte_v2(Data2);
    }
    Data2 = CRC8_SingleByte_v2(Data2);

    return (byte) (Data2 >> 8);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->device = new QSerialPort;
    this->punkty=0;
    serialBuffer="";
}

MainWindow::~MainWindow()
{
    delete ui;
    delete device;
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type()==QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        return;
    }
    QMainWindow::changeEvent(event);
}


void MainWindow::on_pushButton_Polacz_clicked()
{
    qDebug() << tr("Connect");

    if(this->Port==0)
    {
      qDebug() << tr("No port");
      return;
    }
    else
    {
        QString portName = "/dev/" + this->Port;
        //QString portName="/dev/ttyACM0";
        this->device->setPortName(portName);
         qDebug() <<  portName;

        // OTWÓRZ I SKONFIGURUJ PORT:
        if(device->open(QSerialPort::ReadWrite))
        {
          this->device->setBaudRate(QSerialPort::Baud9600);
          this->device->setDataBits(QSerialPort::Data8);
          this->device->setParity(QSerialPort::NoParity);
          this->device->setStopBits(QSerialPort::OneStop);
          this->device->setFlowControl(QSerialPort::NoFlowControl);

          qDebug() << tr( "Port Open.");

          // CONNECT:
          connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
        }
        else
        {
           qDebug() << tr("Problem with port openning ");
        }
    }
}


void MainWindow::on_pushButton_Ustawienia_clicked()
{
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
       }
    info=new informacje(this,this->device);
    info->show();


}


void MainWindow::on_pushButton_Rozlacz_clicked()
{
    if(this->device->isOpen())
    {
      this->device->close();
       qDebug() << tr("Connection closed");
    }
    else
    {
      qDebug() << tr("Port isn't open");
      return;
    }


}

void MainWindow::readFromPort()
{
    while(this->device->canReadLine()) {
    QString line = this->device->readLine();

    std::istringstream Napis(line.toStdString());

    char znak;
    unsigned int kontrolna;

    float czytaj_x;
    float czytaj_y;

    Napis>>znak>>czytaj_x>>czytaj_y;

    std::hex(Napis);

    Napis>>kontrolna;

    std::istringstream Napis2(line.toStdString());
    const std::string& tmp=Napis2.str();
    const char* Tresc=tmp.c_str();

    if(static_cast<byte>(kontrolna)==CRC8_DataArray(reinterpret_cast<const byte*>(Tresc),strlen(Tresc)-4))
    {
        this->x=czytaj_x;
    }
    ui->gra->y=y;

    float pom;
    pom=this->x;

    QString x_qstring = QString::number(pom);
    info->addToLogs(x_qstring,"0");


       ui->gra->x=(this->x-60)/10;

       punkty=ui->gra->wynik;

       ui->Punkty->display(ui->gra->wynik);
    }
}


void MainWindow::on_pushButton_NowaGra_clicked()
{
    punkty=0;
    ui->gra->wynik=punkty;
    ui->gra->x=-1;
    ui->gra->y=1;
    ui->gra->z=0;
    ui->gra->R=0.25;
    ui->gra->wired=true;
    ui->gra->y=1.5;

}





void MainWindow::on_Jezyk_stateChanged(int arg1)
{
    static QTranslator *jezyk =new QTranslator();
    if(arg1)
    {
        if(jezyk->load("../nienazwany/nienazwany_PL.qm","."))
        {
            qApp->installTranslator(jezyk);
        }
        else
            qDebug()<<tr("error");
    }
    else
    {
        qApp->removeTranslator(jezyk);
    }
}

