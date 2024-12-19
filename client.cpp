#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    this->setWindowTitle("Client");

    tcpradio = new QRadioButton();
    tcpradio->setText("TCP");

    udpradio = new QRadioButton();
    udpradio->setText("UDP");

    yaw = setoptions(-100, 100, 1);
    roll = setoptions(-100, 100, 1);
    pitch = setoptions(-100, 100, 1);
    thrust = setoptions(0, 100, 1);

    lyaw = new QLabel("yaw (-1..1):");
    lroll = new QLabel("roll  (-1..1):");
    lpitch = new QLabel("pitch  (-1..1):");
    lthrust = new QLabel("thrust  (0..1):");

    client = new tcpClient();

    lstatus = new QLabel("status: " + client->getstatus());
    lip = new QLabel("ip: " + *converiptostring(client->getip()) + ":" + QString::number(client->geport()));

    normalize = new QPushButton();
    normalize->setText("Normalize");

    connection = new QPushButton();
    connection->setText("Connection");

    sendmessage = new QPushButton();
    sendmessage->setText("Send Message");

    protocolslayer = new QHBoxLayout();
    protocolslayer->addWidget(tcpradio);
    protocolslayer->addWidget(udpradio);

    labelslayer = new QHBoxLayout();
    labelslayer->addWidget(lstatus);
    labelslayer->addWidget(lip);

    sliderslayer = new QHBoxLayout();
    sliderslayer->addWidget(lyaw);
    sliderslayer->addWidget(yaw);
    sliderslayer->addWidget(lroll);
    sliderslayer->addWidget(roll);
    sliderslayer->addWidget(lpitch);
    sliderslayer->addWidget(pitch);
    sliderslayer->addWidget(lthrust);
    sliderslayer->addWidget(thrust);

    buttonslayer = new QHBoxLayout();
    buttonslayer->addWidget(connection);
    buttonslayer->addWidget(sendmessage);
    buttonslayer->addWidget(normalize);

    clientlayer = new QVBoxLayout();
    clientlayer->addLayout(protocolslayer);
    clientlayer->addLayout(labelslayer);
    clientlayer->addLayout(sliderslayer);
    clientlayer->addLayout(buttonslayer);

    this->setLayout(clientlayer);

    tcpradio->setChecked(true);

    connect(connection, SIGNAL(clicked()), this, SLOT(connectionSlot()));
    connect(normalize, SIGNAL(clicked()), this, SLOT(normalizeSlot()));
    connect(sendmessage, SIGNAL(clicked()), this, SLOT(sendmessageSlot()));
    connect(tcpradio, SIGNAL(clicked()), this, SLOT(chooseProtocolSlot()));
    connect(udpradio, SIGNAL(clicked()), this, SLOT(chooseProtocolSlot()));
}

Client::~Client()
{
    delete ui;

    delete tcpradio;
    delete udpradio;

    delete yaw;
    delete roll;
    delete pitch;
    delete thrust;

    delete lyaw;
    delete lroll;
    delete lpitch;
    delete lthrust;
    delete lstatus;
    delete lip;

    delete normalize;
    delete connection;
    delete sendmessage;

    delete labelslayer;
    delete sliderslayer;
    delete buttonslayer;

    delete client;

    delete clientlayer;
}

QSlider *Client::setoptions(int min, int max, int step)
{
    QSlider *sl = new QSlider();
    sl->setMinimum(min);
    sl->setMaximum(max);
    sl->setTickInterval(step);
    sl->setTickPosition(QSlider::TicksBothSides);

    return sl;
}

QVector<int> Client::getslidersinfo()
{
    return QVector<int>{yaw->value(), roll->value(), pitch->value(), thrust->value()};
}

QVector <QString> par({"Y", "R", "P", "T"});

QString Client::readmessage()
{
    QVector<int> vect = getslidersinfo();
    qDebug() << vect;

    QString outputmessage = "P:";

    int i = 0;
    while (i < par.count())
    {
        outputmessage += par.at(i);

        if (vect.at(i) >= 0)
        {
            outputmessage += "+";
        }
        else
        {
            outputmessage += "-";
        }

        if ((vect.at(i) < 100) && (vect.at(i) > -100))
        {
            outputmessage += "0";
            if ((vect.at(i) < 10) && (vect.at(i) > -10))
                outputmessage += "0";
        }
        outputmessage += QString::number(abs(vect.at(i)));
        i++;
    }

    outputmessage += ".";

    return outputmessage;
}

void Client::chooseProtocolSlot()
{
    qDebug() << "chooseProtocolSlot TEST!";

    delete client;

    if (tcpradio->isChecked())
    {
        client = new tcpClient();
        connection->show();
        //lstatus->show();
        //lstatus->setText("status: " + client->getstatus());
    }
    else if (udpradio->isChecked())
    {
        client = new udpClient();
        //connection->hide();
        //lstatus->setText("");
    }

    lstatus->setText("status: " + client->getstatus());
    lip->setText("ip: " + *converiptostring(client->getip()) + ":" + QString::number(client->geport()));
}

void Client::connectionSlot()
{
    qDebug() << "connectionSlot TEST!";

    if (client->getstatus() == "not connected")
    {        
        if (!client->setconnection())
             client->setstatus("connection failed");
        else
             client->setstatus("connected");
    }
    else
    {        
        if (!client->resetconnection())
            client->setstatus("no connection to reset");
       else
            client->setstatus("not connected");
    }
    lstatus->setText("status: " + client->getstatus());
}

void Client::normalizeSlot()
{
    qDebug() << "normalizeSLOT TEST!";

//    if (client->gesockstatus())
//    {
//        QString outputmessage = "C.";
//        qDebug() << outputmessage;

//        client->writemessage(outputmessage);
//    }
//    lstatus->setText("status: " + client->getstatus());

    yaw->setValue(0);
    roll->setValue(0);
    pitch->setValue(0);
    thrust->setValue(0);
}

void Client::sendmessageSlot()
{
    qDebug() << "sendmessageSLOT TEST!";

    if (client->gesockstatus())
    {
        QString outputmessage = readmessage();

        qDebug() << outputmessage;

        client->writemessage(outputmessage);
    }
    lstatus->setText("status: " + client->getstatus());
}

void Client::writemessageSlot(QString message)
{
    if (client->gesockstatus())
    {
        qDebug() << message;

        client->writemessage(message);
    }
}

void Client::readmessageSlot()
{
    QString mess = readmessage();

    emit sendgetfromclient(mess);
}
