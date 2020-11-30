#include "Workspace.h"

Workspace::Workspace(WorkspaceScene* scene, QWidget *parent)
    :QGraphicsView(scene, parent), m_IsUpdated(false)
{
    connect(scene, &WorkspaceScene::isModified, this, &Workspace::slotSceneUpdated);
}

void Workspace::slotSceneUpdated()
{
    if (!isUpdated())
        emit signalModified();
   setUpdated(true);
}
