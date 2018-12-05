#include "unoboardentity.h"
#include <QStyleOptionGraphicsItem>

UnoBoardEntity::UnoBoardEntity(QGraphicsItem *parent): Entity (parent)
{
    mBoardImg = QImage(":/icons/icon_mega.png");
    mBoardImg = mBoardImg.scaled(680, mBoardImg.height() * 680 / mBoardImg.width(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    mBoardSize = mBoardImg.size();
    mDrawImg = mBoardImg;
}

QRectF UnoBoardEntity::boundingRect() const
{
    return QRectF(-mBoardSize.width() / 2, -mBoardSize.height() / 2, mBoardSize.width(), mBoardSize.height());
}

void UnoBoardEntity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor drawColor(255, 255, 255);
    QPen pen;
    pen.setColor(drawColor);
    painter->setPen(pen);
    if(option->state & QStyle::State_MouseOver) {
        painter->drawRect(boundingRect());
    }

    if(option->state & QStyle::State_Selected) {
        drawColor = QColor(255, 255, 189);
        pen.setColor(drawColor);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
    }

    painter->drawImage(boundingRect(), mDrawImg);
}

void UnoBoardEntity::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void UnoBoardEntity::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void UnoBoardEntity::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
