#include "udpclient.h"

udpClient::udpClient()
{

}

udpClient::~udpClient()
{
    if (clientsocket)
    {
        clientsocket->close();
        delete clientsocket;
    }
}

QString udpClient::getstatus()
{
    return status;
}

void udpClient::setstatus(QString st)
{
    status = st;
}

QVector<unsigned int> udpClient::getip()
{
    return ipaddress;
}

void udpClient::setip(QVector<unsigned int> addr)
{
    ipaddress = addr;
}

unsigned int udpClient::geport()
{
    return port;
}

void udpClient::setport(unsigned int po)
{
    port = po;
}

bool udpClient::gesockstatus()
{
    if (clientsocket)
        return true;
    else
        return false;
}

bool udpClient::setconnection()
{
    clientsocket = new QUdpSocket();
    clientsocket->connectToHost(*converiptostring(ipaddress), port); /* Соединение соккетов из таблицы с хостами */

    if (!clientsocket->waitForConnected(1000))
    {
        delete clientsocket;
        clientsocket = nullptr;

        return false;
    }
    return true;
}

bool udpClient::resetconnection()
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

void udpClient::writemessage(QString message)
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
