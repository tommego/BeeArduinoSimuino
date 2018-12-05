#ifndef CONNECTORENTITY_H
#define CONNECTORENTITY_H

#include "../ecs/entity.h"
#include "pinentity.h"

class ConnectorEntity : public Entity
{
    Q_OBJECT
public:
    ConnectorEntity(QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    const QPointF& startPos(){return mStartPos;}
    const QPointF& endPos(){return mEndPos;}
    void setStartPos(const QPointF& startPos);
    void setEndPos(const QPointF& endPos);


private:
    QSharedPointer<PinEntity> mInputPin;
    QSharedPointer<PinEntity> mOutputPin;
    QPointF mStartPos;
    QPointF mEndPos;
    void updatePos();
};

#endif // CONNECTORENTITY_H
