#ifndef INTCLIENT_H
#define INTCLIENT_H

#include <QString>

class intClient
{
public:
    intClient();
    virtual ~intClient();

    virtual QString getstatus() = 0;
    virtual void setstatus(QString st) = 0;

    virtual QVector<unsigned int> getip() = 0;
    virtual void setip(QVector<unsigned int> addr) = 0;

    virtual unsigned int geport() = 0;
    virtual void setport(unsigned int po) = 0;

    virtual bool gesockstatus() = 0;

    virtual bool setconnection() = 0;
    virtual bool resetconnection() = 0;
    virtual void writemessage(QString message) = 0;
};

#endif // INTCLIENT_H
