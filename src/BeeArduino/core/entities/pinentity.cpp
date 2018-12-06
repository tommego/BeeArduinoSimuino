#include "pinentity.h"
#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

PinEntity::PinEntity(QGraphicsItem *parent) : Entity (parent)
{
    setFlags(ItemIsSelectable);
}

QRectF PinEntity::boundingRect() const
{
    return QRectF(-8, -8, 16, 16);
}

void PinEntity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    QPen pen;
    pen.setWidth(2);
    QColor drawColor(40, 40, 40);
    pen.setColor(drawColor);
    painter->setPen(pen);
    QSizeF size = boundingRect().size() * 0.8;
    QRectF rect = boundingRect();
    rect.setSize(size);
    rect.moveCenter(boundingRect().center());
    painter->fillRect(rect, QColor(200, 160, 200));
    painter->drawRect(rect);

    if(option->state & QStyle::State_MouseOver || option->state & QStyle::State_Selected) {
        painter->fillRect(rect, QColor(255, 160, 200));
        pen.setColor(QColor(255, 255, 255));
        painter->setPen(pen);
        painter->drawRect(rect);
    }

    if(option->state & QStyle::State_Selected) {
        painter->fillRect(rect, QColor(255, 160, 200));
        pen.setColor(QColor(100, 255, 255));
        pen.setWidth(1);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
    }

    emit tick();
}

void PinEntity::setPinMode(const int &mode)
{
    mPinMode = mode;
    update();
    emit tick();
    emit pinModeChanged(mode);
}

void PinEntity::setPinVal(const int &val)
{
    mPinVal = val;
    update();
    emit tick();
    emit pinValChanged(val);
}

void PinEntity::resetState()
{
    update();
    emit tick();
}
