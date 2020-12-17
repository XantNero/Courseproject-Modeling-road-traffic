#ifndef _WORKSPACESCENE_H_
#define _WORKSPACESCENE_H_

#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QMenu>
#include "ItemWindow.h"
#include "Item.h"

class WorkspaceScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum class ActionType
    {
        None = 0,
        AddRoidPoint,
        AddRoad,
        AddCarGenerator,
        AddTrafficlight,
        Move,
        ConnectMainRoad,
        ConnectNotMainRoad,
        Disconnect,
        Delete
    };
public:
    WorkspaceScene(QMenu* itemMenu, QObject *parent = nullptr);
    WorkspaceScene(QMenu* itemMenu, const QRectF &sceneRect,
                   QObject *parent = nullptr);
    WorkspaceScene(QMenu* itemMenu, qreal x, qreal y, qreal width, qreal height,
                   QObject *parent = nullptr);
    inline ActionType getState() { return m_ActionType; }
public slots:
    void slotSetAction(ActionType);
    void slotDelete();
    void slotConnectMainRoad();
    void slotConnectNotMainRoad();
    void slotDisconnect();
    void slotAddDockWidget(QWidget* widget);
    void slotRemoveDockWidget(QWidget* widget);
signals:
    void isModified();
    void signalAddDockWidget(QWidget* widget);
    void signalRemoveDockWidget(QWidget* widget);
protected:
    void init();
    void setState(ActionType type) { m_ActionType = type; }
    void addCarGenerator(QGraphicsSceneMouseEvent *mouseEvent);
    void addRoad(QGraphicsSceneMouseEvent *mouseEvent);
    void addRoadPoint(QGraphicsSceneMouseEvent *mouseEvent);
    void addTrafficlight(QGraphicsSceneMouseEvent *mouseEvent);
    void connect(QGraphicsSceneMouseEvent *mouseEvent, Road::Type roadType);
    void disconnect(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
private:
    ActionType m_ActionType = ActionType::None;
    QMenu* m_ItemMenu;
};

#endif // WORKSPACESCENE_H
