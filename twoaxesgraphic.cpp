#include "twoaxesgraphic.h"

TwoAxesGraphic::TwoAxesGraphic(QWidget *parent)
    : QWidget{parent}
{
    data = new QVector<float>{0, 0, 0};
}

TwoAxesGraphic::~TwoAxesGraphic()
{
    delete[] data;
}

void TwoAxesGraphic::updateData(QVector<float> *data)
{
    if (data->count() == 2)
    {
        this->data->push_back(data->at(0));
        this->data->push_back(data->at(1));
        repaint();
    }
}

void TwoAxesGraphic::paintEvent(QPaintEvent *event)
{

}
