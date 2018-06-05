#include "myudp.h"

MyUDP::MyUDP(QObject *parent, QString ip) : QObject(parent)
{
    ipAdress = ip;
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any,42069);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
}

void MyUDP::SayHello()
{
    QByteArray Data;
    Data.append("testing with sending some random data");
    sendData(Data);

}

void MyUDP::StartGlobe()
{
    QByteArray Data;
    Data.append("1");
    sendData(Data);
}

void MyUDP::StopGlobe()
{
    QByteArray Data;
    Data.append("0");
    sendData(Data);
}

void MyUDP::ChangeValue(int value)
{
    QByteArray Data;
    Data.append("2");
    Data.append(QString::number(value));
    sendData(Data);
}

void MyUDP::sendToLeds(QByteArray byteArray)
{
    //a lot of work to do
    qDebug() << byteArray.toLower() << ipAdress;

    socket->writeDatagram(byteArray,QHostAddress(ipAdress),4210);

}

void MyUDP::readyRead() //will be called when data is received on the udp interface
{
    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(Buffer.data(),Buffer.size(),&sender,&senderPort);

    //qDebug() << "Message From: " << sender.toString();
    //qDebug() << "Message Port: " << senderPort;
    //qDebug() << "Message: " << Buffer;

    emit newData(Buffer); //callback to mainwindow


}

void MyUDP::sendData(QByteArray message)
{
    socket->writeDatagram(message,QHostAddress(ipAdress),42069);
}
