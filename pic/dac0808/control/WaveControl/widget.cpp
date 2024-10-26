#include "widget.h"
#include "./ui_widget.h"
#include "wavearea.h"
#include <QSerialPort>
#include <math.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , serialPort( new QSerialPort)
{
    ui->setupUi(this);
    waveArea = (new WaveArea(this->ui->waveWidget));
    waveArea->resize(MAX_HORIZONTAL_RES,255);
    this->ui->hResSlider->setMinimum(1);
    this->ui->hResSlider->setMaximum(MAX_HORIZONTAL_RES);
    this->ui->hResSpin->setMinimum(1);
    this->ui->hResSpin->setMaximum(MAX_HORIZONTAL_RES);
    this->ui->hResSlider->setValue(180);
    this->ui->hResSpin->setValue(180);
    waveArea->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pbClear_clicked()
{
    waveArea->clearWave();
}


void Widget::on_pbSend_clicked()
{
    QByteArray data;
    serialPort->setPortName("/dev/ttyACM0");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->open(QIODevice::ReadWrite);
    for(uint16_t x = 0; x < horizontalResolution; x++){
        data.clear();
        data.append((uint8_t)(x >> 8));
        data.append((uint8_t)(x));
        data.append(255 - waveArea->points[x + DRAW_OFFSET]);
        serialPort->write("BS");
        serialPort->write(data);
        this->ui->serialLog->appendPlainText(QString("Send:") + QString::number(waveArea->points[x + DRAW_OFFSET]));
        if(serialPort->waitForReadyRead(300)){
            data = serialPort->readAll();
            this->ui->serialLog->appendPlainText("Receive! ");
        }
        else{
            data.clear();
        }
    }
}


void Widget::on_hResSlider_actionTriggered(int action)
{
    this->ui->hResSpin->setValue(this->ui->hResSlider->value());
    setHresolution(this->ui->hResSlider->value());
}


void Widget::on_hResSpin_valueChanged(int arg1)
{
    this->ui->hResSlider->setValue(arg1);
    setHresolution(arg1);
}

void Widget::setHresolution(unsigned int resolution)
{
    this->horizontalResolution = resolution;
    waveArea->resize(resolution+DRAW_OFFSET,255);
}


void Widget::on_horizontalSlider_valueChanged(int value)
{
    QByteArray data;
    data.append((uint8_t)(this->ui->horizontalSlider->value()));
    serialPort->write("BT");
    serialPort->write(data);
    this->ui->serialLog->appendPlainText(QString("Send:") + QString::number(this->ui->horizontalSlider->value()));
    if(serialPort->waitForReadyRead(300)){
        data = serialPort->readAll();
        this->ui->serialLog->appendPlainText("Receive! ");
    }
    else{
        data.clear();
    }
}

