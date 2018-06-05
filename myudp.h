#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>
#include <QDebug>


class MyUDP : public QObject
{
    Q_OBJECT
public:
    explicit MyUDP(QObject *parent = nullptr,QString ip = "0.0.0.0");
    void SayHello();
    void StartGlobe();
    void StopGlobe();
    void ChangeValue(int value);
    void sendToLeds(QByteArray byteArray);


signals:
    void newData(QString msg);

public slots:
    void readyRead();

private:
    QUdpSocket *socket;
    void sendData(QByteArray message);
    QString ipAdress;

public slots:
};

#endif // MYUDP_H
