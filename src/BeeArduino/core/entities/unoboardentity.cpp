#include "unoboardentity.h"
#include <QStyleOptionGraphicsItem>

UnoBoardEntity::UnoBoardEntity(QGraphicsItem *parent): PinEntity (parent)
{
    setFlags(ItemIsSelectable | ItemIsMovable);

    mBoardImg = QImage(":/icons/icon_uno.png");
    mBoardImg = mBoardImg.scaled(680, mBoardImg.height() * 680 / mBoardImg.width(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    mBoardSize = mBoardImg.size();
    mDrawImg = mBoardImg;

    QList<QPointF> poses;
    poses << QPointF(292.0, - 219.5)
          << QPointF(269.0, - 219.5)
          << QPointF(246.0, - 219.5)
          << QPointF(223.0, - 219.5)
          << QPointF(200.8, - 219.5)
          << QPointF(177.6, - 219.5)
          << QPointF(154.2, - 219.5)
          << QPointF(131.5, - 219.5)
          << QPointF(94.5, - 219.5)
          << QPointF(71.3, - 219.5)
          << QPointF(47.8, - 219.5)
          << QPointF(25.0, - 219.5)
          << QPointF(2.3, - 219.5)
          << QPointF(-20.4, - 219.5)
          << QPointF(177.8, 218.6)
          << QPointF(200.9, 218.6)
          << QPointF(224.4, 218.6)
          << QPointF(246.4, 218.6)
          << QPointF(269.5, 218.6)
          << QPointF(292.6, 218.6);


    for(int i = 0; i < 20; i++) {
        QSharedPointer<PinEntity> pin(new PinEntity(this));
        pin->setPos(poses.at(i));
        mPins.append(pin);
    }

    initConnections();
}

void UnoBoardEntity::initConnections()
{
//    foreach (QSharedPointer<PinEntity> pin, mPins) {
//        connect(pin.data(), &PinEntity::toggleStart, [=](PinEntity* pin){
//            emit toggleStart(pin);
//            qDebug() << "board pin toggle start " << pin;
//        });

//        connect(pin.data(), &PinEntity::toggleEnd, [=](PinEntity* pin){
//            emit toggleEnd(pin);
//            qDebug() << "board pin toggle end " << pin;
//        });

//        connect(pin.data(), &PinEntity::toggleDrop, [=](PinEntity* pin){
//            emit toogleDrop(pin);
//            qDebug() << "board pin toggle drop " << pin;

//        });
//    }
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
