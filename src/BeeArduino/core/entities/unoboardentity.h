#ifndef UNOBOARDENTITY_H
#define UNOBOARDENTITY_H

#include "../ecs/entity.h"
#include "../global/defines.h"
#include <QGraphicsSceneMouseEvent>
#include "pinentity.h"

class UnoBoardEntity: public PinEntity
{
    Q_OBJECT

public:
    UnoBoardEntity(QGraphicsItem* parent= nullptr);
    void initConnections();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
//    void toggleStart(PinEntity* pin);
//    void toggleEnd(PinEntity* pin);
//    void toogleDrop(PinEntity* pin);

private:
    QImage mBoardImg;
    QImage mDrawImg;
    QSize mBoardSize;
    QList<QSharedPointer<PinEntity>> mPins;
}; 

#endif // UNOBOARDENTITY_H
