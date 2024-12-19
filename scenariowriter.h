#ifndef SCENARIOWRITER_H
#define SCENARIOWRITER_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QDial>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QHeaderView>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include "client.h"

namespace Ui {
class ScenarioWriter;
}

class ScenarioWriter : public QWidget
{
    Q_OBJECT

public:
    explicit ScenarioWriter(QWidget *parent = nullptr);
    ~ScenarioWriter();

public slots:
    void saveToFile();
    void loadFromFile();
    void handleTableItemClicked(QTableWidgetItem *item);
    void handleDialValueChanged(int value);
    void addRow();
    void addRowFromClient(QString clrow);
    void removeRow();
    void chooseWindowSlot();
    void sendmessagesSlot();
    void onTimerTimeout(); // Слот для обработки события таймер

private:
    Ui::ScenarioWriter *ui;
    QTableWidget *tableWidget;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *addButton; // Кнопка добавления строки
    QPushButton *removeButton; // Кнопка удаления строки
    QPushButton *choosewindow;
    QPushButton *sendmessages;
    QDial *dial;    
    QTimer *timer; // Таймер
    int currentRow; // Текущая строка для обновления времени
    int timerIndex; // Индекс текущего таймера

    Client *cl;

signals:
    void writemessageSignal(QString mess);
    void initgetfromclient();
};

#endif // SCENARIOWRITER_H
