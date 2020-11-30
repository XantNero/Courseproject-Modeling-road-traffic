#include "WorkspaceScene.h"
#include "Item.h"
#include <QGraphicsView>
#include <QInputEvent>

WorkspaceScene::WorkspaceScene(QMenu* itemMenu, QObject *parent)
    :QGraphicsScene(parent), m_ItemMenu(itemMenu)
{
    init();
}
WorkspaceScene::WorkspaceScene(QMenu* itemMenu, const QRectF &sceneRect, QObject *parent)
    :QGraphicsScene(sceneRect, parent), m_ItemMenu(itemMenu)
{
    init();
}
WorkspaceScene::WorkspaceScene(QMenu* itemMenu, qreal x, qreal y, qreal width, qreal height, QObject *parent)
    :QGraphicsScene(x, y, width, height, parent), m_ItemMenu(itemMenu)
{
    init();
}

void WorkspaceScene::init()
{

}

void WorkspaceScene::slotSetAction(ActionType type)
{
    m_ActionType = type;
}

void WorkspaceScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    CarGenerator* carGeneratorItem;
    Road* roadItem;
    RoadPoint* roadPointItem;
    QList<QGraphicsItem*> list;
    QGraphicsItem* item;
    if (mouseEvent->button() == Qt::MouseButton::LeftButton) {
        switch (m_ActionType) {
            case ActionType::AddCarGenerator:
                carGeneratorItem = new CarGenerator(m_ItemMenu, mouseEvent->scenePos());

                addItem(carGeneratorItem);
                QGraphicsScene::mousePressEvent(mouseEvent);
                emit isModified();
                break;
            case ActionType::AddRoad:
//                list = selectedItems();
//                if (list.size() != 1 || list[0]->type() != (int)ModelTypes::Road) {
//                    roadItem = new Road(mouseEvent->scenePos());
//                    roadItem->setFlag(QGraphicsItem::ItemIsMovable, true);
//                    roadItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
//                    roadItem->setFlag(QGraphicsItem::ItemIsFocusable, true);
//                    roadItem->setSelected(true);
//                    addItem(roadItem);
//                    list = selectedItems();
//                    break;
//                }
//                roadItem = dynamic_cast<Road*>(list[0]);
//                roadItem->addPoint(roadItem->mapFromScene(mouseEvent->scenePos()));
                list = selectedItems();
                roadPointItem = new RoadPoint(m_ItemMenu, mouseEvent->scenePos());
                addItem(roadPointItem);
                for (auto item : list) {
                    if (item->type() == (int)ModelTypes::RoadPoint) {
                        RoadPoint* roadPoint = dynamic_cast<RoadPoint*>(item);

                        roadItem = new Road(m_ItemMenu, roadPoint, roadPointItem);

                        roadPoint->connect(roadPointItem, roadItem);
                        roadPointItem->connected(roadPoint, roadItem);
//                        addLine(QLineF(roadPoint->getPoint(), mouseEvent->scenePos()),
//                                QPen(Qt::black, 2));
                    }
                }
                QGraphicsScene::mousePressEvent(mouseEvent);
                emit isModified();
                break;
            case ActionType::Connect:
                 list = selectedItems();
                 if((item = itemAt(mouseEvent->scenePos(), QTransform())) && item->type() == (int)ModelTypes::RoadPoint) {
                     roadPointItem = dynamic_cast<RoadPoint*>(item);
                     for (auto to_connect : list) {
                         if (to_connect->type() == (int)ModelTypes::RoadPoint) {
                             RoadPoint* roadPoint = dynamic_cast<RoadPoint*>(to_connect);
                             roadItem = new Road(m_ItemMenu, roadPoint, roadPointItem);
                             roadPoint->connect(roadPointItem, roadItem);
                             roadPointItem->connected(roadPoint, roadItem);
                         }
                         else if (to_connect->type() == (int)ModelTypes::CarGenerator) {
                             CarGenerator* carGenerator = dynamic_cast<CarGenerator*>(to_connect);
                             carGenerator->connect(roadPointItem);
                         }
                     }
                 }
                setState(ActionType::None);
                emit isModified();
                break;
            case ActionType::Disconnect:
                list = selectedItems();
                if((item = itemAt(mouseEvent->scenePos(), QTransform())) && item->type() == (int)ModelTypes::RoadPoint) {
                    roadPointItem = dynamic_cast<RoadPoint*>(item);
                    for (auto to_disconnect : list) {
                        if (to_disconnect->type() == (int)ModelTypes::RoadPoint) {
                            RoadPoint* roadPoint = dynamic_cast<RoadPoint*>(to_disconnect);
                            roadPoint->deleteConnection(roadPointItem);
                            roadPointItem->deleteConnected(roadPoint);
                        }
                        else if (to_disconnect->type() == (int)ModelTypes::CarGenerator) {
                            CarGenerator* carGenerator = dynamic_cast<CarGenerator*>(to_disconnect);
                            carGenerator->disconnect();
                        }
                    }
                }
                setState(ActionType::None);
                emit isModified();
                break;
            default: QGraphicsScene::mousePressEvent(mouseEvent);
        }

    }
    else if (mouseEvent->button() == Qt::RightButton) {
        if (itemAt(mouseEvent->scenePos(), QTransform()) == nullptr)
            m_ItemMenu->exec(mouseEvent->screenPos());
    }


}

 void WorkspaceScene::keyPressEvent(QKeyEvent *event)
 {
     if (event->key() == Qt::Key_Delete) {
         slotDelete();
     }
 }

 void WorkspaceScene::slotDelete()
 {
     QList<QGraphicsItem*> list = selectedItems();
     for (auto item : list) {
         removeItem(item);
         delete item;
     }
     emit isModified();
 }

 void WorkspaceScene::slotConnect()
 {
    setState(ActionType::Connect);
 }
 void WorkspaceScene::slotDisconnect()
 {
    setState(ActionType::Disconnect);
 }
