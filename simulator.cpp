#include "simulator.h"
#include "ui_simulator.h"

Simulator::Simulator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Simulator)
{
    ui->setupUi(this);

    this->setWindowTitle("Simulator");

    gr1 = new TwoAxesGraphic();
    gr2 = new TwoAxesGraphic();
    gr3 = new TwoAxesGraphic();

    connection = new QPushButton();
    connection->setText("Connection");

    twoaxegrlayer = new QVBoxLayout();
    twoaxegrlayer->addWidget(gr1);
    twoaxegrlayer->addWidget(gr2);
    twoaxegrlayer->addWidget(gr3);
    twoaxegrlayer->addWidget(connection);

    this->setLayout(twoaxegrlayer);

    connect(connection, SIGNAL(clicked()), this, SLOT(SerialConnection()));
    connect(this, SIGNAL(setGr1Data(QVector<float> *)), gr1, SLOT(updateData(QVector<float> *)));
    connect(this, SIGNAL(setGr2Data(QVector<float> *)), gr2, SLOT(updateData(QVector<float> *)));
    connect(this, SIGNAL(setGr3Data(QVector<float> *)), gr3, SLOT(updateData(QVector<float> *)));
}

Simulator::~Simulator()
{
    delete ui;

    delete gr1;
    delete gr2;
    delete gr3;
    delete twoaxegrlayer;
}

void Simulator::SerialConnection()
{
    qDebug() << "TEST SerialConnection";
}

void Simulator::getSerialData()
{

}

void Simulator::openSerialPort()
{
    m_serial = new QSerialPort();

//    const SettingsDialog::Settings p = m_settings->settings();
//    m_serial->setPortName(p.name);
//    m_serial->setBaudRate(p.baudRate);
//    m_serial->setDataBits(p.dataBits);
//    m_serial->setParity(p.parity);
//    m_serial->setStopBits(p.stopBits);
//    m_serial->setFlowControl(p.flowControl);
//    if (m_serial->open(QIODevice::ReadWrite)) {
//        m_console->setEnabled(true);
//        m_console->setLocalEchoEnabled(p.localEchoEnabled);
//        m_ui->actionConnect->setEnabled(false);
//        m_ui->actionDisconnect->setEnabled(true);
//        m_ui->actionConfigure->setEnabled(false);
//        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
//                          .arg(p.name, p.stringBaudRate, p.stringDataBits,
//                               p.stringParity, p.stringStopBits, p.stringFlowControl));
//    } else {
//        QMessageBox::critical(this, tr("Error"), m_serial->errorString());

//        showStatusMessage(tr("Open error"));
//    }

    connect(m_serial, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(m_serial, SIGNAL(bytesWritten()), this, SLOT(handleBytesWritten()));
}

void Simulator::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
//    m_console->setEnabled(false);
//    m_ui->actionConnect->setEnabled(true);
//    m_ui->actionDisconnect->setEnabled(false);
//    m_ui->actionConfigure->setEnabled(true);
//    showStatusMessage(tr("Disconnected"));

    disconnect(m_serial, SIGNAL(readyRead()), this, SLOT(readData()));
    disconnect(m_serial, SIGNAL(bytesWritten()), this, SLOT(handleBytesWritten()));
}

void Simulator::writeData(const QByteArray &data)
{
    const qint64 written = m_serial->write(data);
//    if (written == data.size()) {
//        m_bytesToWrite += written;
//        m_timer->start(kWriteTimeout);
//    } else {
//        const QString error = tr("Failed to write all data to port %1.\n"
//                                 "Error: %2").arg(m_serial->portName(),
//                                                  m_serial->errorString());
//        showWriteError(error);
//    }
}

void Simulator::handleBytesWritten(qint64 bytes)
{
//    m_bytesToWrite -= bytes;
//    if (m_bytesToWrite == 0)
//        m_timer->stop();
}

void Simulator::readData()
{
//    const QByteArray data = m_serial->readAll();
//    m_console->putData(data);
}
