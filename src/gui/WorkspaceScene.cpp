#include "WorkspaceScene.h"
#include <QGraphicsView>
#include <QInputEvent>

WorkspaceScene::WorkspaceScene(QMenu* itemMenu, QObject *parent)
    :QGraphicsScene(parent), m_ItemMenu(itemMenu)
{
    init();
}
WorkspaceScene::WorkspaceScene(QMenu* itemMenu,
                               const QRectF &sceneRect, QObject *parent)
    :QGraphicsScene(sceneRect, parent), m_ItemMenu(itemMenu)
{
    init();
}
WorkspaceScene::WorkspaceScene(QMenu* itemMenu,
                               qreal x, qreal y, qreal width, qreal height,
                               QObject *parent)
    :QGraphicsScene(x, y, width, height, parent), m_ItemMenu(itemMenu)
{
    init();
}

void WorkspaceScene::init()
{
}

void WorkspaceScene::addCarGenerator(QGraphicsSceneMouseEvent *mouseEvent)
{
    CarGenerator* carGeneratorItem = 
        new CarGenerator(m_ItemMenu, mouseEvent->scenePos());
    addItem(carGeneratorItem);
    QGraphicsScene::mousePressEvent(mouseEvent);
    emit isModified();
}

void WorkspaceScene::addRoad(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> list = selectedItems();
    RoadPoint* roadPointItem =
        new RoadPoint(m_ItemMenu, mouseEvent->scenePos());
    addItem(roadPointItem);
    for (auto item : list) {
        if (item->type() == (int)ModelTypes::RoadPoint) {
            RoadPoint* roadPoint = dynamic_cast<RoadPoint*>(item);

            Road* roadItem = new Road(m_ItemMenu, roadPoint, roadPointItem);

            roadPoint->connect(roadPointItem, roadItem);
            roadPointItem->connected(roadPoint, roadItem);
//                        addLine(QLineF(roadPoint->getPoint(), mouseEvent->scenePos()),
//                                QPen(Qt::black, 2));
        }
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
    emit isModified();
    list = selectedItems();
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
}

void WorkspaceScene::addRoadPoint(QGraphicsSceneMouseEvent *mouseEvent)
{
    RoadPoint* roadPointItem =
        new RoadPoint(m_ItemMenu, mouseEvent->scenePos());
    addItem(roadPointItem);
    QGraphicsScene::mousePressEvent(mouseEvent);
    emit isModified();
}

void WorkspaceScene::addTrafficlight(QGraphicsSceneMouseEvent *mouseEvent)
{
   Trafficlight* trafficlightItem =
    new Trafficlight(m_ItemMenu, mouseEvent->scenePos());
   addItem(trafficlightItem);
   QGraphicsScene::mousePressEvent(mouseEvent);
   emit isModified();
}

void WorkspaceScene::connect(QGraphicsSceneMouseEvent *mouseEvent,
                            Road::Type roadType)
{
    QList<QGraphicsItem*> list = selectedItems();
    QGraphicsItem* item;
    if((item = itemAt(mouseEvent->scenePos(), QTransform())) &&
        item->type() == (int)ModelTypes::RoadPoint) {
        RoadPoint* roadPointItem = dynamic_cast<RoadPoint*>(item);
        for (auto to_connect : list) {
            if (to_connect->type() == (int)ModelTypes::RoadPoint ||
                to_connect->type() == (int)ModelTypes::CarGenerator ||
                to_connect->type() == (int)ModelTypes::Trafficlight) {
                Road::Type type = 
                    to_connect->type() == (int)ModelTypes::RoadPoint ?
                        roadType : Road::Connection;
                RoadPoint* roadPoint = dynamic_cast<RoadPoint*>(to_connect);
                Road* roadItem = 
                    new Road(m_ItemMenu, roadPoint, roadPointItem, type);
                if (to_connect->type() == (int)ModelTypes::CarGenerator ||
                    to_connect->type() == (int)ModelTypes::Trafficlight) {
                    if (roadPoint->getConnections().size() == 1)
                        roadPoint->
                            deleteConnection(roadPoint->getConnections()[0]);
                }
                roadPoint->connect(roadPointItem, roadItem);
                roadPointItem->connected(roadPoint, roadItem);
            }
//            else if (to_connect->type() == (int)ModelTypes::CarGenerator) {
//                CarGenerator* carGenerator = dynamic_cast<CarGenerator*>(to_connect);
//                Road* roadItem = new Road(m_ItemMenu, carGenerator, roadPointItem, Road::Connection);
//                carGenerator->connect(roadPointItem, roadItem);
//                roadPointItem->connected(carGenerator, roadItem);
//            }
//            else if (to_connect->type() == (int)ModelTypes::Trafficlight) {

//            }
        }
    }
   setState(ActionType::None);
   emit isModified();
}

void WorkspaceScene::disconnect(QGraphicsSceneMouseEvent *mouseEvent)
{
    QList<QGraphicsItem*> list; list = selectedItems();
    QGraphicsItem* item;
    if((item = itemAt(mouseEvent->scenePos(), QTransform())) && 
        item->type() == (int)ModelTypes::RoadPoint) {
         RoadPoint* roadPointItem = dynamic_cast<RoadPoint*>(item);
        for (auto to_disconnect : list) {
            if (to_disconnect->type() == (int)ModelTypes::RoadPoint ||
                to_disconnect->type() == (int)ModelTypes::CarGenerator ||
                to_disconnect->type() == (int)ModelTypes::Trafficlight) {
                RoadPoint* roadPoint = dynamic_cast<RoadPoint*>(to_disconnect);
                roadPoint->deleteConnection(roadPointItem);
                roadPointItem->deleteConnected(roadPoint);
            }
//            else if (to_disconnect->type() == (int)ModelTypes::CarGenerator) {
//                CarGenerator* carGenerator = dynamic_cast<CarGenerator*>(to_disconnect);
//                carGenerator->deleteConnection(roadPointItem);
//                roadPointItem->deleteConnected(carGenerator);
//            }
            //else if (to_)
        }
    }
    setState(ActionType::None);
    emit isModified();
}

void WorkspaceScene::slotSetAction(ActionType type)
{
    m_ActionType = type;
}

void WorkspaceScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::MouseButton::LeftButton) {
        switch (m_ActionType) {
            case ActionType::AddCarGenerator:
                addCarGenerator(mouseEvent);
                break;
            case ActionType::AddRoidPoint:
                addRoadPoint(mouseEvent);
                break;
            case ActionType::AddRoad:
                addRoad(mouseEvent);
                break;
            case ActionType::AddTrafficlight:
                addTrafficlight(mouseEvent);
                break;
            case ActionType::ConnectMainRoad:
                connect(mouseEvent, Road::Main);
                break;
            case ActionType::ConnectNotMainRoad:
                connect(mouseEvent, Road::NotMain);
                break;
            case ActionType::Disconnect:
                disconnect(mouseEvent);
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

 void WorkspaceScene::slotConnectMainRoad()
 {
     setState(ActionType::ConnectMainRoad);
 }

 void WorkspaceScene::slotConnectNotMainRoad()
 {
     setState(ActionType::ConnectNotMainRoad);
 }

 void WorkspaceScene::slotDisconnect()
 {
     setState(ActionType::Disconnect);
 }

 void WorkspaceScene::slotAddDockWidget(QWidget *widget)
 {
     emit signalAddDockWidget(widget);
 }

 void WorkspaceScene::slotRemoveDockWidget(QWidget *widget)
 {
     emit signalRemoveDockWidget(widget);
 }
