#include "entity.h"
#include "../global/defines.h"
#include <QVariant>

Entity::Entity(QGraphicsItem *parent) : QGraphicsObject(parent)
{
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptDrops(true);
    initConnections();
}

ComponentList Entity::components()
{
    return mComponents;
}

void Entity::initConnections()
{
    QGraphicsObject* p = this->parentObject();
    while (p) {
        connect(p, &QGraphicsObject::xChanged, [=]{emit scenePosChanged();});
        connect(p, &QGraphicsObject::yChanged, [=]{emit scenePosChanged();});
        Entity* e = qobject_cast<Entity*>(p);
        if(e) {
            connect(e, &Entity::tick, [=]{emit tick();});
        }
        p = p->parentObject();
    }
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

void Entity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
    emit tick();
}

void Entity::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Entity::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
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

QVariant Entity::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
//    qDebug () << "item change " << change << "," << value;
    if(change == QGraphicsItem::ItemSelectedChange) {
        if(value.toInt() == 0)
            emit diselected(this);
        if(value.toInt() == 1)
            emit selected(this);
    }
    return value;
}
