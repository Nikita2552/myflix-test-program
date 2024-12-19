#include "scenariowriter.h"
#include "ui_scenariowriter.h"

ScenarioWriter::ScenarioWriter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScenarioWriter)
{
    ui->setupUi(this);

    this->setWindowTitle("Scenario Writer");

    // Создание таблицы
    tableWidget = new QTableWidget(0, 2, this);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Отсылаемая команда" << "Время");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Создание кнопок
    saveButton = new QPushButton("Сохранить", this);
    loadButton = new QPushButton("Загрузить", this);
    addButton = new QPushButton("Добавить строку", this); // Кнопка добавления
    removeButton = new QPushButton("Удалить строку", this); // Кнопка удаления    

    choosewindow = new QPushButton();
    choosewindow->setText("Открыть клиент");

    sendmessages = new QPushButton();
    sendmessages->setText("Отправить сообщения");

    // Создание QDial
    dial = new QDial(this);
    dial->setRange(0, 60); // Установка диапазона от 0 до 60 секунд

    // Установка компоновки
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tableWidget);
    layout->addWidget(dial);
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);
    layout->addWidget(addButton); // Добавление кнопки в компоновку
    layout->addWidget(removeButton); // Добавление кнопки в компоновку
    layout->addWidget(sendmessages);
    layout->addWidget(choosewindow);

    this->setLayout(layout);

    cl = new Client();
    connect(choosewindow, SIGNAL(clicked()), this, SLOT(chooseWindowSlot()));

    // Создание таймера
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout())); // Подключение сигнала таймера к слоту

    // Подключение сигналов и слотов
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveToFile()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadFromFile()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addRow())); // Подключение кнопки добавления
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeRow())); // Подключение кнопки удаления
    connect(tableWidget, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(handleTableItemClicked(QTableWidgetItem *)));
    connect(dial, SIGNAL(valueChanged(int )), this, SLOT(handleDialValueChanged(int )));
    connect(sendmessages, SIGNAL(clicked()), this, SLOT(sendmessagesSlot()));
    connect(this, SIGNAL(writemessageSignal(QString )), cl, SLOT(writemessageSlot(QString )));
    connect(this, SIGNAL(initgetfromclient()), cl, SLOT(readmessageSlot()));
    connect(cl, SIGNAL(sendgetfromclient(QString )), this, SLOT(addRowFromClient(QString )));
}

ScenarioWriter::~ScenarioWriter()
{
    delete ui;
}

void ScenarioWriter::saveToFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        QString command = tableWidget->item(row, 0) ? tableWidget->item(row, 0)->text() : "";
        QString time = tableWidget->item(row, 1) ? tableWidget->item(row, 1)->text() : "";
        out << command << "\t" << time << "\n";
    }
    file.close();
}

void ScenarioWriter::loadFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить файл", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    tableWidget->setRowCount(0); // Очистить таблицу
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split("\t");
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        for (int col = 0; col < fields.size(); ++col) {
            tableWidget->setItem(row, col, new QTableWidgetItem(fields[col]));
        }
    }
    file.close();
}

void ScenarioWriter::handleTableItemClicked(QTableWidgetItem *item) {
    // Обработка активации строки таблицы
    qDebug() << "test handleTableItemClicked";
    currentRow = tableWidget->currentRow(); // Получаем текущую строку
    if (currentRow >= 0) {
        // Устанавливаем значение QDial в соответствии с текущей ячейкой времени
        QString timeText = tableWidget->item(currentRow, 1) ? tableWidget->item(currentRow, 1)->text() : "0";
        dial->setValue(timeText.toInt());
    }
}

void ScenarioWriter::handleDialValueChanged(int value) {
    // Обработка изменения значения QDial
    if ((currentRow >= 0) && (tableWidget->rowCount() > 0)) {
        // Обновляем значение времени в активированной строке таблицы
        tableWidget->item(currentRow, 1)->setText(QString::number(value));
    }
}

void ScenarioWriter::addRow() {
    if (cl->isHidden())
    {
        addRowFromClient("P:Y+000R+000P+000T+000.");
    }
    else
    {
        emit initgetfromclient();
    }
}

void ScenarioWriter::addRowFromClient(QString clrow)
{
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    tableWidget->setItem(row, 0, new QTableWidgetItem(clrow)); // Пример добавления текста
    tableWidget->setItem(row, 1, new QTableWidgetItem("0")); // Пример добавления времени
}

void ScenarioWriter::removeRow() {
    int currentRow = tableWidget->currentRow(); // Получаем текущую строку
    if (currentRow >= 0) {
        tableWidget->removeRow(currentRow); // Удаляем строку
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите строку для удаления.");
    }
}

void ScenarioWriter::chooseWindowSlot()
{
    qDebug() << "chooseWindowSlot TEST!";

    if (cl->isHidden())
        cl->show();

}

void ScenarioWriter::sendmessagesSlot()
{
    qDebug() << "sendMessagesSlot TEST!";

    timerIndex = 0; // Сбрасываем индекс таймера
    int row = 0;
    if (tableWidget->rowCount() > 0) {
        QString timeText = tableWidget->item(row, 1) ? tableWidget->item(row, 1)->text() : "0";
        int timeValue = timeText.toInt();
        timer->start(timeValue * 1000); // Запускаем таймер на время из ячейки (в миллисекундах)
        timerIndex = row; // Сохраняем текущий индекс таймера
    }
}

void ScenarioWriter::onTimerTimeout() {
    if (timerIndex < tableWidget->rowCount()) {
        QString command = tableWidget->item(timerIndex, 0) ? tableWidget->item(timerIndex, 0)->text() : "";

        emit writemessageSignal(command);

        // Переходим к следующему таймеру
        timerIndex++;
        if (timerIndex < tableWidget->rowCount()) {
            QString timeText = tableWidget->item(timerIndex, 1) ? tableWidget->item(timerIndex, 1)->text() : "0";
            int timeValue = timeText.toInt();
            if (timeValue > 0) {
                timer->start(timeValue * 1000); // Запускаем следующий таймер
            }
        } else {
            timer->stop(); // Останавливаем таймер, если достигли конца таблицы
        }
    }
}
