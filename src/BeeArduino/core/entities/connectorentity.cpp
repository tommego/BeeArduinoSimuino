#include "connectorentity.h"
#include <QPen>
#include <QPainter>


ConnectorEntity::ConnectorEntity(QGraphicsItem *parent): Entity (parent)
{
    mStartPos = QPointF(0, 0);
    mEndPos = QPoint(0, 0);
    setFlags(ItemIsSelectable);
}

QRectF ConnectorEntity::boundingRect() const
{
    QPointF gap = mEndPos - mStartPos;
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
    painter->drawLine(mStartPos - this->pos(), mEndPos - this->pos());
}

void ConnectorEntity::setStartPos(const QPointF &startPos)
{
    mStartPos = startPos;
    updatePos();
}

void ConnectorEntity::setEndPos(const QPointF &endPos)
{
    mEndPos = endPos;
    updatePos();
}

void ConnectorEntity::updatePos()
{
    QPointF gap = mEndPos - mStartPos;
    setPos(mStartPos.x() + gap.x() / 2, mEndPos.y() + gap.y() / 2);
    update();
}
