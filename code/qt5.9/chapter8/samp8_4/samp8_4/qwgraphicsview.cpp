#include "qwgraphicsview.h"
#include <QMouseEvent>

QWGraphicsView::QWGraphicsView(QWidget *parent):QGraphicsView(parent)
{

}

// 鼠标移动事件
void QWGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos();	// QGraphicsView的坐标
    emit mouseMovePoint(point);
    QGraphicsView::mouseMoveEvent(event);
}

// 鼠标左键按下事件
void QWGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPoint point = event->pos();	// QGraphicsView的坐标
        emit mouseClicked(point);
    }
    QGraphicsView::mousePressEvent(event);
}
