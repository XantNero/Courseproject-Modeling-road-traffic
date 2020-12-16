#ifndef _WORKSPACE_H_
#define _WORKSPACE_H_
#include <QGraphicsView>
#include "WorkspaceScene.h"
#include <QRubberBand>
class Workspace : public QGraphicsView
{
    Q_OBJECT
public:
     Workspace(WorkspaceScene *scene, QWidget *parent = nullptr);
     inline bool isUpdated() const { return m_IsUpdated; }
     inline void setUpdated(bool value) { m_IsUpdated = value; }
protected:
     virtual void mousePressEvent(QMouseEvent* event) override;
     virtual void mouseMoveEvent(QMouseEvent* event) override;
     virtual void mouseReleaseEvent(QMouseEvent* event) override;
private slots:
     void slotSceneUpdated();
signals:
     void signalModified();
private:
     bool m_IsUpdated;
     QRubberBand *rubberBand;
     QPoint origin;
};

#endif
