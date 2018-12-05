#ifndef CONNECTORSYSTEM_H
#define CONNECTORSYSTEM_H

#include "../ecs/system.h"
#include <QGraphicsScene>
#include <QDrag>
#include <QMimeData>
#include "../entities/connectorentity.h"
#include <QTimer>

class PinEntity;
class ConnectorSystem : public System
{
    Q_OBJECT
public:
    ConnectorSystem(QObject* parent = nullptr, QGraphicsScene* scene = nullptr);
    void initConnections();

public slots:
    void pinToggleStart(PinEntity* pin);
    void pinToggleEnd(PinEntity* pin);
    void pinDrop(PinEntity* pin);
    void updateDrawConnector();

private:
    QSharedPointer<QGraphicsScene> scene;
    PinEntity* mcurrentDragePin;
    PinEntity* mcurrentDropPin;
    QTimer* mDrawConnectorTimer;
    ConnectorEntity* mConnector;

};

#endif // CONNECTORSYSTEM_H
