#include "connectorsystem.h"
#include "../entities/pinentity.h"
#include <QDebug>
#include <QCursor>
#include <QGraphicsView>

ConnectorSystem::ConnectorSystem(QObject *parent, QGraphicsScene* scene): System (parent),
    scene(QSharedPointer<QGraphicsScene>(scene)),mDrawConnectorTimer(new QTimer(this))
{
    initConnections();
    mDrawConnectorTimer->setInterval(30);
}

void ConnectorSystem::initConnections()
{
    foreach (QGraphicsItem* item, scene->items()) {
        PinEntity* pin = static_cast<PinEntity*>(item);
        if(pin) {
            connect(pin, &PinEntity::toggleStart, this, &ConnectorSystem::pinToggleStart);
            connect(pin, &PinEntity::toggleEnd, this, &ConnectorSystem::pinToggleEnd);
            connect(pin, &PinEntity::toggleDrop, this, &ConnectorSystem::pinDrop);
        }
    }

    connect(mDrawConnectorTimer, &QTimer::timeout, this, &ConnectorSystem::updateDrawConnector);
}

void ConnectorSystem::pinToggleStart(PinEntity *pin)
{
    qDebug() << this << "detect pin toggle start " << pin;
    mcurrentDragePin = pin;
    mConnector = new ConnectorEntity;
    mConnector->setEnabled(false);
    scene->addItem(mConnector);
    mConnector->setStartPos(pin->pos());
    mConnector->setEndPos(pin->pos());
    mDrawConnectorTimer->start();

    QDrag* drag = new QDrag(pin);
    QMimeData* mimeData = new QMimeData;

    mimeData = new QMimeData;
    mimeData->setText("connect pin");
    drag->setMimeData(mimeData);
    drag->exec();
}

void ConnectorSystem::pinToggleEnd(PinEntity *pin)
{
    qDebug() << this << "detect pin toggle end " << pin;
    mDrawConnectorTimer->stop();
    scene->removeItem(mConnector);
    mConnector = nullptr;

}

void ConnectorSystem::pinDrop(PinEntity *pin)
{
    qDebug() << this << "detect pin toggle drop " << pin;
    mcurrentDropPin = pin;
    mcurrentDragePin->resetState();
    mDrawConnectorTimer->stop();
    scene->removeItem(mConnector);
    mConnector = nullptr;
}

void ConnectorSystem::updateDrawConnector()
{
    if(mConnector) {
        QPoint gPos = QCursor::pos();
        QPoint wPos = scene->views().first()->window()->mapFromGlobal(gPos);
        QPointF sPos = scene->views().first()->mapToScene(wPos);
        mConnector->setEndPos(sPos);
        scene->update(scene->sceneRect());
    }
}
