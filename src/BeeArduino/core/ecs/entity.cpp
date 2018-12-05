#include "entity.h"
#include "../global/defines.h"

Entity::Entity(QGraphicsItem *parent) : QGraphicsObject(parent)
{
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

ComponentList Entity::components()
{
    return mComponents;
}

int Entity::id()
{
    return mId;
}

void Entity::setID(const int &id)
{
    mId = id;
}

bool Entity::isValid()
{
    return (mId != -1);
}

void Entity::addComponent(QSharedPointer<Component> com)
{
    mComponents.append(com);
}

QPainterPath Entity::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Entity::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Entity::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << ">>>";
    if (event->modifiers() & Qt::ShiftModifier) {
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Entity::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
