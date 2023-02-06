#ifndef INFORMACJE_H
#define INFORMACJE_H

#include <QDialog>
#include <QSerialPortInfo>

/*!
 *
 * \brief Tworzenie nowego okienka w aplikacji
 */

namespace Ui {
class informacje;
}

/*!
 *
 * \brief Zawiera definicję klasy informacje
 * dzieki niej jest możliwość otworzeniu w nowym okienku opcji ustawień i wyświetlenia info
 * dotyczące portu szeregowego, którego jest prowadzona komunikacja
 */

class informacje : public QDialog
{
    Q_OBJECT

public:
    explicit informacje(QWidget *parent = nullptr, QSerialPort *dev=nullptr);
    ~informacje();
    QString Port;
    QString Urzadzenie;
    QSerialPort *device;
    void addToLogs(QString x,QString y);

private slots:
    void on_odswiez_clicked();

private:
    Ui::informacje *ui;
};

#endif // INFORMACJE_H
