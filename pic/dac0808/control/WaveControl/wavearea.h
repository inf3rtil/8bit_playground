#ifndef WAVEAREA_H
#define WAVEAREA_H

#include <QWidget>

#define DRAW_OFFSET 5

class WaveArea : public QWidget
{
    Q_OBJECT
    QPoint lastPoint = QPoint(0,0);
    QColor myPenColor = Qt::blue;
    QImage image;
    bool scribbling = true;
    void drawLineTo(const QPoint &endPoint);
    bool modified = false;
    qreal myPenWidth = 4;
    void resizeImage(QImage *image, const QSize &newSize);
    //std::vector<QPoint> points;
public:
    explicit WaveArea(QWidget *parent = nullptr);
    void clearWave(void);
    void setResolutionH(unsigned int resolution);
    std::array<int, 1024> points;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

signals:
};

#endif // WAVEAREA_H
