#ifndef TWOAXESGRAPHIC_H
#define TWOAXESGRAPHIC_H

#include <QWidget>
#include <QVector>

class TwoAxesGraphic : public QWidget
{
    Q_OBJECT
public:
    explicit TwoAxesGraphic(QWidget *parent = nullptr);
    ~TwoAxesGraphic();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QVector<float> *data;

public slots:
    void updateData(QVector<float> *data);
};

#endif // TWOAXESGRAPHIC_H
