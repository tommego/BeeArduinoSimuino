#ifndef PINENTITY_H
#define PINENTITY_H

#include "../ecs/entity.h"

class PinEntity : public Entity
{
    Q_OBJECT
public:
    PinEntity(QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    const int& pinMode(){return mPinMode;}
    void setPinMode(const int& mode);
    const int& pinVal(){return mPinVal;}
    void setPinVal(const int& val);
    void resetState();

signals:
    void pinValChanged(const int& val);
    void pinModeChanged(const int& mode);

private:
    int mPinMode; // 0: INPUT, 1: OUTPUT
    int mPinVal;
};

#endif // PINENTITY_H
