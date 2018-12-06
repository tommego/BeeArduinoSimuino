#include "connectorsystem.h"
#include "../entities/pinentity.h"
#include <QDebug>
#include <QCursor>
#include <QGraphicsView>

ConnectorSystem::ConnectorSystem(QObject *parent, QGraphicsScene* scene): System (parent),
    scene(QSharedPointer<QGraphicsScene>(scene))
{
    initConnections();
    mSelectedPin = nullptr;
}

void ConnectorSystem::initConnections()
{
    foreach (QGraphicsItem* item, scene->items()) {
        Entity* entity = static_cast<Entity*>(item);
        if(entity) {
            connect(entity, &Entity::selected, this, &ConnectorSystem::onItemSelected);
            connect(entity, &Entity::diselected, this, &ConnectorSystem::onItemDiselected);
        }
    }

}

void ConnectorSystem::onItemSelected(Entity *entity)
{
    PinEntity* pin = qobject_cast<PinEntity*>(entity);
    if(!pin) {
        if(mSelectedPin)
            mSelectedPin = nullptr;
        return;
    }

    if(!mSelectedPin) {
        mSelectedPin = pin;
        return;
    }

    if(mSelectedPin && mSelectedPin != pin){
        connectPin(mSelectedPin, pin);
    }

}

void ConnectorSystem::onItemDiselected(Entity *entity)
{
    Q_UNUSED(entity)
}

void ConnectorSystem::connectPin(PinEntity *startPin, PinEntity *endPin)
{
    ConnectorEntity* conPin = new ConnectorEntity(nullptr, startPin, endPin);
    scene->addItem(conPin);
    startPin->setSelected(false);
    endPin->setSelected(false);
    mSelectedPin = nullptr;
}

