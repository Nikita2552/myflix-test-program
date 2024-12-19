#include "tcpclient.h"

tcpClient::tcpClient()
{

}

tcpClient::~tcpClient()
{
    if (clientsocket)
    {
        clientsocket->close();
        delete clientsocket;
    }
}

QString tcpClient::getstatus()
{
    return status;
}

void tcpClient::setstatus(QString st)
{
    status = st;
}

QVector<unsigned int> tcpClient::getip()
{
    return ipaddress;
}

void tcpClient::setip(QVector<unsigned int> addr)
{
    ipaddress = addr;
}

unsigned int tcpClient::geport()
{
    return port;
}

void tcpClient::setport(unsigned int po)
{
    port = po;
}

bool tcpClient::gesockstatus()
{
    if (clientsocket)
        return true;
    else
        return false;
}

bool tcpClient::setconnection()
{
    clientsocket = new QTcpSocket();
    clientsocket->connectToHost(*converiptostring(ipaddress), port); /* Соединение соккетов из таблицы с хостами */

    if (!clientsocket->waitForConnected(1000))
    {
        delete clientsocket;
        clientsocket = nullptr;

        return false;
    }
    return true;
}

bool tcpClient::resetconnection()
{
    if (clientsocket)
    {
        clientsocket->close();
        delete clientsocket;
        clientsocket = nullptr;

        return true;
    }
    return false;
}

QString* converiptostring(QVector<unsigned int> ipaddr)
{
    QString *str = new QString
            (
                QString::number(ipaddr.at(0)) + "." +
                QString::number(ipaddr.at(1)) + "." +
                QString::number(ipaddr.at(2)) + "." +
                QString::number(ipaddr.at(3))
            );
    return str;
}

void tcpClient::writemessage(QString message)
{
    QByteArray array;
    array.append(message);

    unsigned int tr = 0;
    while (tr < SENDTRIES)
    {
        if (clientsocket->write(array) > 0)
            return;
         tr++;
    }
    status = "send message failed";
}
