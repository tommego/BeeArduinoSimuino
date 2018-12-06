#ifndef CONNECTORENTITY_H
#define CONNECTORENTITY_H

#include "../ecs/entity.h"
#include "pinentity.h"

class ConnectorEntity : public Entity
{
    Q_OBJECT
public:
    ConnectorEntity(QGraphicsItem* parent = nullptr, PinEntity* start = nullptr, PinEntity* end = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void initConnections();

public slots:

private:
    QSharedPointer<PinEntity> mStartPin;
    QSharedPointer<PinEntity> mEndPin;
};

#endif // CONNECTORENTITY_H
