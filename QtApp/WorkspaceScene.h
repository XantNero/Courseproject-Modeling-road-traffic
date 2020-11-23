#ifndef _WORKSPACESCENE_H_
#define _WORKSPACESCENE_H_

#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QMenu>

class WorkspaceScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum class ActionType
    {
        None = 0, AddRoad, AddCarGenerator, Move, Connect, Disconnect, Delete
    };
public:
    WorkspaceScene(QMenu* itemMenu, QObject *parent = nullptr);
    WorkspaceScene(QMenu* itemMenu, const QRectF &sceneRect, QObject *parent = nullptr);
    WorkspaceScene(QMenu* itemMenu, qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
    inline ActionType getState() { return m_ActionType; }
public slots:
    void slotSetAction(ActionType);
    void slotDelete();
    void slotConnect();
    void slotDisconnect();
protected:
    void init();
    void setState(ActionType type) { m_ActionType = type; }
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
private:
    ActionType m_ActionType = ActionType::None;
    QMenu* m_ItemMenu;
};

#endif // WORKSPACESCENE_H
