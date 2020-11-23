#ifndef _ITEM_H_
#define _ITEM_H_

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>


class RoadPoint;
enum class ModelTypes
{
    Road = 10, CarGenerator, RoadPoint
};

class CarGenerator : public QGraphicsItem
{
public:
   CarGenerator(QMenu* contextMenu, const QPointF& pos, QGraphicsItem* parent = nullptr);
   virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
   virtual QRectF boundingRect() const override;
   virtual int type() const override;
   void connect(RoadPoint* point);
   void disconnect();
   RoadPoint* getConnection() const;
protected:
   virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
private:
   QMenu* m_ContextMenu;
   RoadPoint* m_Connection;
};

class Road : public QGraphicsItem
{
public:
    Road(QMenu* contextMenu, RoadPoint* start, RoadPoint* end,QGraphicsItem* parent = nullptr);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual QRectF boundingRect() const override;
    virtual int type() const override;
protected:
   virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
private:
    RoadPoint* m_Start;
    RoadPoint* m_End;
    QMenu* m_ContextMenu;
};

class RoadPoint : public QGraphicsItem
{
public:
    RoadPoint(QMenu* contextMenu, const QPointF& pos, QGraphicsItem* parent = nullptr);
    ~RoadPoint();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual QRectF boundingRect() const override;
    void connect(RoadPoint* point, Road* road);
    const QList<RoadPoint*>& getConnections() const;
    void connected(RoadPoint* point, Road* road);
    virtual int type() const override;
    const QPointF getPoint() const;
    void deleteConnection(RoadPoint* point);
    void deleteConnected(RoadPoint* point);
protected:
   virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
private:
    QList<RoadPoint*> m_Connections;
    QList<RoadPoint*> m_Connected;
    QList<Road*> m_OutRoads;
    QList<Road*> m_InRoads;
    QMenu* m_ContextMenu;
};

#endif // ITEM_H
