#include "Workspace.h"
#include <QMouseEvent>

Workspace::Workspace(WorkspaceScene* scene, QWidget *parent)
    :QGraphicsView(scene, parent), m_IsUpdated(false), rubberBand(nullptr)
{
    connect(scene, &WorkspaceScene::isModified, this, &Workspace::slotSceneUpdated);
}

void Workspace::mousePressEvent(QMouseEvent *event)
{
    origin = event->pos();
    if (!rubberBand)
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    if (scene()->selectedItems().size() == 0) {
        rubberBand->setGeometry(QRect(origin, QSize()));
        rubberBand->show();
    }
//    if (event->buttons() == Qt::RightButton)
//            setDragMode(QGraphicsView::NoDrag);
    QGraphicsView::mousePressEvent(event);
}

void Workspace::mouseMoveEvent(QMouseEvent *event)
{
    if (scene()->selectedItems().size() == 0) {
        rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void Workspace::mouseReleaseEvent(QMouseEvent *event)
{
    if (scene()->selectedItems().size() == 0) {
        rubberBand->hide();
        QPainterPath path;
        path.addRect(rubberBand->geometry());
        scene()->setSelectionArea(mapToScene(path));
        rubberBand->setGeometry(QRect(origin, QSize()));
    }


//    if (event->button() == Qt::RightButton)
//           setDragMode(QGraphicsView::RubberBandDrag);
    QGraphicsView::mouseReleaseEvent(event);
}

void Workspace::slotSceneUpdated()
{
    if (!isUpdated())
        emit signalModified();
   setUpdated(true);
}
