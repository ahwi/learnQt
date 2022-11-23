#ifndef QWGRAPHICSVIEW_H
#define QWGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>

class QWGraphicsView: public QGraphicsView
{
    Q_OBJECT;
public:
    QWGraphicsView(QWidget *parent=0);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void mouseMovePoint(QPoint point);
    void mouseClicked(QPoint point);

};

#endif // QWGRAPHICSVIEW_H
