#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qserialport.h>

#define MAX_HORIZONTAL_RES 1024

class WaveArea;

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pbClear_clicked();

    void on_pbSend_clicked();

    void on_hResSlider_actionTriggered(int action);

    void on_hResSpin_valueChanged(int arg1);

private:
    WaveArea *waveArea = nullptr;
    QSerialPort *serialPort = nullptr;
    Ui::Widget *ui;
    void setHresolution(unsigned int resolution);
    unsigned int horizontalResolution = 255;
};
#endif // WIDGET_H
