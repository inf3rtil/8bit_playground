#ifndef WAVEAREA_H
#define WAVEAREA_H

#include <QWidget>

class waveArea : public QWidget
{
    Q_OBJECT
    QPoint lastPoint;
    QColor myPenColor = Qt::blue;
    QImage image;
    bool scribbling = false;
    void drawLineTo(const QPoint &endPoint);
public:
    explicit waveArea(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

signals:
};

#endif // WAVEAREA_H
