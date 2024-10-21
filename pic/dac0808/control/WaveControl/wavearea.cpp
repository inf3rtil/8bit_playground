#include "wavearea.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

void WaveArea::drawLineTo(const QPoint &endPoint)
{
    qDebug() << endPoint;
    if(endPoint.x() > lastPoint.x()){
    QPainter painter(&image);
    painter.setPen(QPen(QColor(qRgb(0,255,127)), myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
               .adjusted(-rad, -rad, +rad, +rad));
    points[lastPoint.x()] = lastPoint.y();
    lastPoint = endPoint;
    }
}

WaveArea::WaveArea(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_StaticContents);
}

void WaveArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if(event->position().toPoint().x() > lastPoint.x()){
            lastPoint = event->position().toPoint();
        }
        scribbling = true;
    }
}

void WaveArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->position().toPoint());
}

void WaveArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->position().toPoint());
        scribbling = false;
    }
}

void WaveArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void WaveArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 500, image.width());
        int newHeight = qMax(height() + 500, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void WaveArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(0,109,80));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}


void WaveArea::clearWave()
{
    image.fill(qRgb(0,109,80));
    modified = true;
    update();
    lastPoint = QPoint(0,0);
    points.fill(0);
}

