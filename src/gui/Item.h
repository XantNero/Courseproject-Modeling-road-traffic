#ifndef _ITEM_H_
#define _ITEM_H_

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include "ItemWindow.h"


enum class ModelTypes
{
    Road = 10, CarGenerator, RoadPoint, Trafficlight
};

class RoadPoint;

class Road : public QGraphicsItem
{
public:
    enum Type
    {
        Main, NotMain, Connection
    };
public:
    Road(QMenu* contextMenu, RoadPoint* start, RoadPoint* end,
         Type type = Main, QGraphicsItem* parent = nullptr);
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = nullptr) override;
    virtual QRectF boundingRect() const override;
    virtual int type() const override;
    inline Type getRoadType() const { return m_Type; }
protected:
   virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *ev) override;
private:
    RoadPoint* m_Start;
    RoadPoint* m_End;
    QMenu* m_ContextMenu;
    Type m_Type;

};


class RoadPoint : public QGraphicsItem
{
public:
    RoadPoint(QMenu* contextMenu, const QPointF& pos,
              QGraphicsItem* parent = nullptr);
    ~RoadPoint();
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = nullptr) override;
    virtual QRectF boundingRect() const override;
    void connect(RoadPoint* point, Road* road);
    const QList<RoadPoint*>& getConnections() const;
    Road::Type getRoadType(RoadPoint* point);
    void connected(RoadPoint* point, Road* road);
    virtual int type() const override;
    const QPointF getPoint() const;
    void deleteConnection(RoadPoint* point);
    void deleteConnected(RoadPoint* point);
protected:
   virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *ev) override;
protected:
    QList<RoadPoint*> m_Connections;
    QList<RoadPoint*> m_Connected;
    QList<Road*> m_OutRoads;
    QList<Road*> m_InRoads;
    QMenu* m_ContextMenu;
};

class CarGenerator : public RoadPoint
{
public:
   CarGenerator(QMenu* contextMenu, const QPointF& pos,
                int timing = 1000, QGraphicsItem* parent = nullptr);
   virtual void paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget = nullptr) override;
   virtual QRectF boundingRect() const override;
   virtual int type() const override;
   inline unsigned int getRate() const { return m_Window->getRate();}
//   void connect(RoadPoint* point);
//   void disconnect();
//   RoadPoint* getConnection() const;
protected:
   virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *ev) override;
   virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change,
                               const QVariant &value) override;
private:
   CarGeneratorWindow* m_Window;
};



class Trafficlight : public RoadPoint
{
public:
    Trafficlight(QMenu* contextMenu, const QPointF& pos,
                 LightTimings timings = {0, 0, 0},
                 QGraphicsItem* parent = nullptr);
   virtual void paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget = nullptr) override;
   virtual QRectF boundingRect() const override;
   virtual int type() const override;
   inline LightTimings getTimings() const { return m_Window->getTimings(); }
//   void connect(RoadPoint* point);
//   void disconnect();
//   RoadPoint* getConnection() const;
protected:
   virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *ev) override;
   virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change,
                               const QVariant &value) override;
private:
    TrafficlightWindow* m_Window;
};

#endif // ITEM_H
