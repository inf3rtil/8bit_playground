#include "widget.h"
#include "./ui_widget.h"
#include <QSerialPort>
#include "wavearea.h"
#include <math.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , serialPort( new QSerialPort)
{
    QByteArray data;
    ui->setupUi(this);
    serialPort->setPortName("/dev/ttyUSB0");
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->open(QIODevice::ReadWrite);
    for(unsigned char x = 0; x <= 180; x++){
        data.clear();
        data.append(x);
        data.append((unsigned char)(sin(x * M_PI / 180.0)*127));
        serialPort->write("BS");
        serialPort->write(data);
        if(serialPort->waitForReadyRead(1000)){
            data = serialPort->readAll();
        }
        else{
            data.clear();
        }
    }
    QCoreApplication::quit();
}

Widget::~Widget()
{
    delete ui;
}
