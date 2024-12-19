#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QUdpSocket>
#include <QHostAddress>
#include <QAbstractSocket>

#include "intclient.h"
#include "tcpclient.h"

#define SENDTRIES 10

class udpClient : public intClient
{
public:
    udpClient();
    ~udpClient();

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
    QUdpSocket *clientsocket = nullptr;

    QVector<unsigned int> ipaddress{192, 168, 4, 1};
    unsigned int port = 49152;
    QString status = "not connected";
};

#endif // UDPCLIENT_H
