#include "Item.h"
#include "WorkspaceScene.h"
#include <iostream>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <cmath>

CarGenerator::CarGenerator(QMenu* contextMenu, const QPointF& pos,
                           int timing, QGraphicsItem* parent)
    : RoadPoint(contextMenu, pos, parent)
    , m_Window(new CarGeneratorWindow(timing))
{
    QTransform transform;
    transform.translate(pos.x(), pos.y());
    setTransform(transform);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}
void CarGenerator::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pix("res/textures/font_car.png");
    pix.scaled(QSize(50, 50), Qt::KeepAspectRatio);
    //painter->drawRect(0, 0, 64, 64);
    QPen pen(Qt::black, 3);
    painter->setPen(pen);
    painter->drawPixmap(QRect(-25, -25, 50, 50), pix, pix.rect());
    pen.setBrush(Qt::blue);
    pen.setStyle(Qt::DashLine);
    pen.setWidth(2);
    if (isSelected()) {
        painter->setPen(pen);
        painter->drawRect(QRectF(-25.0f, -25.0f, 50.0f, 50.0f));
    }

}
QRectF CarGenerator::boundingRect() const
{
    return QRectF(-25.0f, -25.0f, 50.0f, 50.0f);
}

int CarGenerator::type() const
{
    return (int)ModelTypes::CarGenerator;
}

void CarGenerator::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_ContextMenu->exec(event->screenPos());
}


QVariant CarGenerator::itemChange(QGraphicsItem::GraphicsItemChange change,
                                 const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange) {
        WorkspaceScene* workspaceScene = dynamic_cast<WorkspaceScene*>(scene());
        if (value == true) {
            m_Window->show();
            workspaceScene->slotAddDockWidget(m_Window);
        }
        else {
            m_Window->hide();
            workspaceScene->slotRemoveDockWidget(m_Window);
        }
        return value;
    }
    return QGraphicsItem::itemChange(change, value);
}

//void CarGenerator::connect(RoadPoint* point)
//{
//    m_Connection = point;
//    Road* road = new Road(m_ContextMenu, new RoadPoint(m_ContextMenu, scenePos()), point, Road::Connection);
//    scene()->addItem(road);
//}

//void CarGenerator::disconnect()
//{
//    m_Connection = nullptr;
//}
//RoadPoint* CarGenerator::getConnection() const
//{
//    return m_Connection;
//}


Road::Road(QMenu* contextMenu, RoadPoint* start, RoadPoint* end,
           Type type, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_Start(start), m_End(end)
    , m_ContextMenu(contextMenu), m_Type(type)
{
    setZValue(-1.0f);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsFocusable, false);
}
void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget)
{    
    prepareGeometryChange();
     QPen pen(Qt::black, 2);
    if (m_Type == Main) {
        painter->setPen(pen);
        QPointF vec = m_End->getPoint() - m_Start->getPoint();
        vec /= sqrt(vec.x() * vec.x() + vec.y() * vec.y());
        QLineF line(m_Start->getPoint(), m_End->getPoint());
        vec *= 0.3f * line.length();;
        painter->drawLine(m_Start->getPoint(), m_End->getPoint() - vec);
        pen.setBrush(Qt::green);
        painter->setPen(pen);
        painter->drawLine(m_End->getPoint() - vec, m_End->getPoint());
    }
    else if (m_Type == NotMain) {
        pen.setColor(Qt::gray);
        pen.setStyle(Qt::DashDotDotLine);
        painter->setPen(pen);
        QPointF vec = m_End->getPoint() - m_Start->getPoint();
        vec /= sqrt(vec.x() * vec.x() + vec.y() * vec.y());
        QLineF line(m_Start->getPoint(), m_End->getPoint());
        vec *= 0.3f * line.length();;
        painter->drawLine(m_Start->getPoint(), m_End->getPoint() - vec);
        pen.setBrush(Qt::green);
        painter->setPen(pen);
        painter->drawLine(m_End->getPoint() - vec, m_End->getPoint());
    }
    else if (m_Type == Connection) {
        pen.setColor(Qt::magenta);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->drawLine(m_Start->getPoint(), m_End->getPoint());
    }

}
QRectF Road::boundingRect() const
{
    QPointF aleft(std::min(m_Start->getPoint().x(), m_End->getPoint().x()),
                  std::min(m_Start->getPoint().y(), m_End->getPoint().y()));
    QPointF aright(std::max(m_Start->getPoint().x(), m_End->getPoint().x()),
                   std::max(m_Start->getPoint().y(), m_End->getPoint().y()));
    return QRectF(aleft, aright);
}

int Road::type() const
{
    return (int)ModelTypes::Road;
}

void Road::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    /*setSelected(true);*/
    //m_ContextMenu->exec(event->screenPos());
}

RoadPoint::RoadPoint(QMenu* contextMenu, const QPointF& pos,
                     QGraphicsItem* parent)
    : QGraphicsItem(parent), m_Connections(), m_ContextMenu(contextMenu)
    , m_Index(-1)
{
    QTransform transform;
    transform.translate(pos.x(), pos.y());
    setTransform(transform);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setSelected(true);
}

RoadPoint::~RoadPoint()
{
    for (auto connected : m_Connected) {
         connected->deleteConnection(this);
    }
    for (auto connection : m_Connections) {
        deleteConnection(connection);
        connection->deleteConnected(this);
    }
}

void RoadPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    QPen pen(Qt::red, 2);
    painter->setPen(pen);
    painter->drawEllipse(-10, -10, 20, 20);
    pen.setBrush(Qt::black);
    painter->setPen(pen);
//    for (auto road : m_Connections) {
//        road->update(boundingRect());
//    }
//    for (auto point : m_Connections)
//        painter->drawLine(QPointF(0.0f, 0.0f), mapFromItem(point, QPointF(0.0f, 0.0f)));
    pen.setBrush(Qt::blue);
    pen.setStyle(Qt::DashLine);
    pen.setWidth(2);
    painter->setPen(pen);
    if (isSelected()) {
        painter->drawRect(boundingRect());
    }
}
QRectF RoadPoint::boundingRect() const
{
    return QRectF(-10.0f, -10.0f, 20.0f, 20.0f);
}
void RoadPoint::connect(RoadPoint* point, Road* road)
{
    QList<RoadPoint*>::iterator it = 
        std::find(m_Connections.begin(), m_Connections.end(), point);
    if (it != m_Connections.end())
        return;
    m_Connections.push_back(point);
    m_OutRoads.push_back(road);
    scene()->addItem(road);
}
int RoadPoint::type() const
{
    return (int) ModelTypes::RoadPoint;
}

void RoadPoint::deleteConnection(RoadPoint *point)
{
    QList<RoadPoint*>::iterator it =
        std::find(m_Connections.begin(), m_Connections.end(), point);
    QList<Road*>::iterator road =
        m_OutRoads.begin() + (it - m_Connections.begin());
    if (it == m_Connections.end())
        return;
    m_Connections.erase(it);
    Road* temp = *road;
    //scene()->removeItem(temp);
    m_OutRoads.erase(road);
    delete temp;

}

void RoadPoint::deleteConnected(RoadPoint* point)
{
    QList<RoadPoint*>::iterator it =
        std::find(m_Connected.begin(), m_Connected.end(), point);
    QList<Road*>::iterator road = 
        m_InRoads.begin() + (it - m_Connected.begin());
    if (it == m_Connected.end())
        return;
    m_Connected.erase(it);
    m_InRoads.erase(road);
}

void RoadPoint::connected(RoadPoint* point, Road* road)
{
    QList<RoadPoint*>::iterator it =
        std::find(m_Connected.begin(), m_Connected.end(), point);
    if (it != m_Connected.end())
        return;
    m_Connected.push_back(point);
    m_InRoads.push_back(road);
}

const QPointF RoadPoint::getPoint() const
{
    return mapToScene(QPointF(0.0f, 0.0f));
}

void RoadPoint::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_ContextMenu->exec(event->screenPos());
}

const QList<RoadPoint*>& RoadPoint::getConnections() const
{
    return m_Connections;
}

Road::Type RoadPoint::getRoadType(RoadPoint *point)
{
    QList<RoadPoint*>::iterator it =
        std::find(m_Connections.begin(), m_Connections.end(), point);
    QList<Road*>::iterator road =
        m_OutRoads.begin() + (it - m_Connections.begin());
    return (*road)->getRoadType();
}


Trafficlight::Trafficlight(QMenu *contextMenu, const QPointF &pos,
                           LightTimings timings, QGraphicsItem *parent)
    : RoadPoint(contextMenu, pos, parent)
    , m_Window(new TrafficlightWindow(timings))
{
    QTransform transform;
    transform.translate(pos.x(), pos.y());
    setTransform(transform);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}

void Trafficlight::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pix("res/textures/traffic-light.png");
    pix.scaled(QSize(32, 64), Qt::KeepAspectRatio);
    //painter->drawRect(0, 0, 64, 64);
    QPen pen(Qt::black, 3);
    painter->setPen(pen);
    painter->drawPixmap(QRect(-16, -32, 32, 64), pix, pix.rect());
    pen.setBrush(Qt::blue);
    pen.setStyle(Qt::DashLine);
    pen.setWidth(2);
    if (isSelected()) {
        painter->setPen(pen);
        painter->drawRect(QRectF(-16.0f, -32.0f, 32.0f, 64.0f));
    }
}

QRectF Trafficlight::boundingRect() const
{
     return QRectF(-16.0f, -32.0f, 32.0f, 64.0f);
}

int Trafficlight::type() const
{
    return (int)ModelTypes::Trafficlight;
}

//void Trafficlight::connect(RoadPoint *point)
//{
//    m_Connection = point;
//}

//void Trafficlight::disconnect()
//{
//    m_Connection = nullptr;
//}

//RoadPoint *Trafficlight::getConnection() const
//{
//    return m_Connection;
//}

void Trafficlight::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_ContextMenu->exec(event->screenPos());
}

QVariant Trafficlight::itemChange(QGraphicsItem::GraphicsItemChange change,
                                  const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange) {
        WorkspaceScene* workspaceScene = dynamic_cast<WorkspaceScene*>(scene());
        if (value == true) {
            m_Window->show();
            workspaceScene->slotAddDockWidget(m_Window);
        }
        else {
            m_Window->hide();
            workspaceScene->slotRemoveDockWidget(m_Window);
        }
        return value;
    }
    return QGraphicsItem::itemChange(change, value);
}
