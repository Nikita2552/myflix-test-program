#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QAbstractSocket>

#include "intclient.h"

#define SENDTRIES 10

class tcpClient : public intClient
{
public:
    tcpClient();
    ~tcpClient();

    QString getstatus();
    void setstatus(QString st);

    QVector<unsigned int> getip();
    void setip(QVector<unsigned int> addr);

    unsigned int geport();
    void setport(unsigned int po);

    bool gesockstatus();

    bool setconnection();
    bool resetconnection();
    void writemessage(QString message);

private:
    QTcpSocket *clientsocket = nullptr;

    QVector<unsigned int> ipaddress{192, 168, 4, 1};
    unsigned int port = 80;
    QString status = "not connected";
};

QString* converiptostring(QVector<unsigned int> ipaddr);

#endif // TCPCLIENT_H
