#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSerialPort>
#include <QDebug>
#include "twoaxesgraphic.h"

namespace Ui {
class Simulator;
}

class Simulator : public QWidget
{
    Q_OBJECT

public:
    explicit Simulator(QWidget *parent = nullptr);
    ~Simulator();

private:
    Ui::Simulator *ui;

    TwoAxesGraphic *gr1 = nullptr;
    TwoAxesGraphic *gr2 = nullptr;
    TwoAxesGraphic *gr3 = nullptr;

    QVBoxLayout *twoaxegrlayer = nullptr;

    QPushButton *connection = nullptr;

    QSerialPort *m_serial = nullptr;

    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);

private slots:
    void SerialConnection();
    void getSerialData();
    void handleBytesWritten(qint64 bytes);
    void readData();

signals:
    void setGr1Data(QVector<float> *xdata);
    void setGr2Data(QVector<float> *ydata);
    void setGr3Data(QVector<float> *zdata);
};

#endif // SIMULATOR_H
