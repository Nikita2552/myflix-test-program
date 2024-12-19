#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Quadro main");

    clientradio = new QRadioButton();
    clientradio->setText("Client");

    simulatorradio = new QRadioButton();
    simulatorradio->setText("Simulator");

    scenariowriterradio = new QRadioButton();
    scenariowriterradio->setText("Scenario Writer");

    choosewindow = new QPushButton();
    choosewindow->setText("Open");

    parentlayer = new QVBoxLayout();
    parentlayer->addWidget(clientradio);
    parentlayer->addWidget(simulatorradio);
    parentlayer->addWidget(scenariowriterradio);
    parentlayer->addWidget(choosewindow);

    parentwidget = new QWidget();
    parentwidget->setLayout(parentlayer);
    this->setCentralWidget(parentwidget);

    cl = new Client();
    sim = new Simulator();
    scw = new ScenarioWriter();

    clientradio->setChecked(true);

    connect(choosewindow, SIGNAL(clicked()), this, SLOT(chooseWindowSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete clientradio;
    delete simulatorradio;
    delete choosewindow;
    delete parentlayer;
    delete parentwidget;
    delete cl;
    delete sim;
}

void MainWindow::chooseWindowSlot()
{
    qDebug() << "chooseWindowSlot TEST!";

    if (clientradio->isChecked())
    {
        sim->hide();
        scw->hide();
        cl->show();
    }
    else if (simulatorradio->isChecked())
    {
        cl->hide();
        scw->hide();
        sim->show();
    }
    else if (scenariowriterradio->isChecked())
    {
        cl->hide();
        sim->hide();
        scw->show();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
 {
    qDebug() << "closeEvent TEST!";

    cl->hide();
    sim->hide();
 }

