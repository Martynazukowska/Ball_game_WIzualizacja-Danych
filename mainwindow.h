#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QSerialPort>
#include "informacje.h"
#include "podsumowanie.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString Port;
    QString Urzadzenie;
    int punkty;
    float R;
    float x,y,z;
    int koniec;
   virtual void changeEvent(QEvent *event)override;


private slots:
    void on_pushButton_Polacz_clicked();

    void on_pushButton_Ustawienia_clicked();

    void on_pushButton_Rozlacz_clicked();

    void readFromPort();

    void on_pushButton_NowaGra_clicked();

    void on_Jezyk_stateChanged(int arg1);


private:
    QSerialPort *device; // Wskaznik na obiekt QSerialPort
    Ui::MainWindow *ui;
    informacje *info;
    podsumowanie *pod;
    QByteArray serialData;
    QString serialBuffer;
};
#endif // MAINWINDOW_H
