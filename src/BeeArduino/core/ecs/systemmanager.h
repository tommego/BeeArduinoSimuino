#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <QObject>

class SystemManager : public QObject
{
    Q_OBJECT
public:
    explicit SystemManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SYSTEMMANAGER_H