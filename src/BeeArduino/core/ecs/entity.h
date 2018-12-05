#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include "component.h"

class Entity : public QGraphicsObject, QSharedData
{
    Q_OBJECT
public:
    explicit Entity(QGraphicsItem *parent = nullptr);
    ComponentList components();
    int id();
    void setID(const int& id);
    bool isValid();
    void addComponent(QSharedPointer<Component> com);
    QPainterPath shape() const override;

signals:

public slots:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    ComponentList mComponents;
    int mId;
};

typedef  QList<Entity*> EntityList;
typedef  QMap<int, Entity*> EntityMap;

#endif // ENTITY_H
