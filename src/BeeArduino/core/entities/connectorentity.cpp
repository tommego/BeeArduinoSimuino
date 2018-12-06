#include "connectorentity.h"
#include <QPen>
#include <QPainter>
#include <QDebug>


ConnectorEntity::ConnectorEntity(QGraphicsItem *parent, PinEntity* start, PinEntity* end): Entity (parent),
    mStartPin(QSharedPointer<PinEntity>(start)),
    mEndPin(QSharedPointer<PinEntity>(end))
{
    setFlags(ItemIsSelectable);
    initConnections();
    setZValue(1);
}

QRectF ConnectorEntity::boundingRect() const
{
    QPointF gap = mEndPin->pos() - mStartPin->pos();
    qreal w, h;
    w = qAbs(gap.x()) + 6;
    h = qAbs(gap.y()) + 6;

    return QRectF( -w / 2 - 3, -h / 2 - 3, w, h);
}

void ConnectorEntity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    QPen pen;
    pen.setWidth(2);
    QColor drawColor(40, 255, 20);
    pen.setColor(drawColor);
    painter->setPen(pen);
    painter->drawLine(mStartPin->scenePos() - this->pos(), mEndPin->scenePos() - this->pos());
}

void ConnectorEntity::initConnections()
{
    connect(mStartPin.data(), &Entity::scenePosChanged, [=]{
        this->prepareGeometryChange();
    });
    connect(mEndPin.data(), &Entity::scenePosChanged, [=]{
        this->prepareGeometryChange();
    });

    connect(mEndPin.data(), &Entity::tick, [=]{
        this->prepareGeometryChange();
    });
}
