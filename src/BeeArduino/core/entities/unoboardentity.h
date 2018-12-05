#ifndef UNOBOARDENTITY_H
#define UNOBOARDENTITY_H

#include "../ecs/entity.h"
#include "../global/defines.h"
#include <QGraphicsSceneMouseEvent>

class UnoBoardEntity: public Entity
{
    Q_OBJECT

public:
    UnoBoardEntity(QGraphicsItem* parent= nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QImage mBoardImg;
    QImage mDrawImg;
    QSize mBoardSize;
}; 

#endif // UNOBOARDENTITY_H
