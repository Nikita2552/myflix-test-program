#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QDebug>
#include <cmath>

#include "intclient.h"
#include "tcpclient.h"
#include "udpclient.h"

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

private:
    Ui::Client *ui;    

    intClient *client;

    QRadioButton *tcpradio;
    QRadioButton *udpradio;

    QSlider *yaw;
    QSlider *pitch;
    QSlider *roll;
    QSlider *thrust;

    QLabel *lyaw;
    QLabel *lpitch;
    QLabel *lroll;
    QLabel *lthrust;
    QLabel *lstatus;
    QLabel *lip;

    QPushButton *normalize;
    QPushButton *connection;
    QPushButton *sendmessage;

    QVBoxLayout *clientlayer;

    QHBoxLayout *protocolslayer;
    QHBoxLayout *labelslayer;
    QHBoxLayout *sliderslayer;    
    QHBoxLayout *buttonslayer;

    QSlider *setoptions(int min, int max, int step);
    QVector<int> getslidersinfo();
    QString readmessage();

private slots:
    void chooseProtocolSlot();
    void connectionSlot();
    void normalizeSlot();
    void sendmessageSlot();

public slots:
    void writemessageSlot(QString message);
    void readmessageSlot();

signals:
    void sendgetfromclient(QString clmess);
};

#endif // CLIENT_H
