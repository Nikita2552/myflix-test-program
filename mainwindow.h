#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include "client.h"
#include "simulator.h"
#include "scenariowriter.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Client *cl;
    Simulator *sim;
    ScenarioWriter *scw;

    QWidget *parentwidget;
    QVBoxLayout *parentlayer;

    QRadioButton *clientradio;
    QRadioButton *simulatorradio;
    QRadioButton *scenariowriterradio;

    QPushButton *choosewindow;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void chooseWindowSlot();
};
#endif // MAINWINDOW_H
