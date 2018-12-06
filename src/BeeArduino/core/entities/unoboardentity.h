#ifndef UNOBOARDENTITY_H
#define UNOBOARDENTITY_H

#include "../ecs/entity.h"
#include "../global/defines.h"
#include <QGraphicsSceneMouseEvent>
#include "pinentity.h"

class UnoBoardEntity: public Entity
{
    Q_OBJECT

public:
    UnoBoardEntity(QGraphicsItem* parent= nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:

signals:

private:
    QImage mBoardImg;
    QImage mDrawImg;
    QSize mBoardSize;
    QList<QSharedPointer<PinEntity>> mPins;
}; 

#endif // UNOBOARDENTITY_H
