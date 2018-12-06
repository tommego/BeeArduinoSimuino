#include "arduino.h"
#include <QDebug>

Arduino::Arduino(QObject *parent) : QProcess(parent),
    isRunning(false)
{
    setProgram("servuino");
    setWorkingDirectory("./");
//    setProgram("ls");
    initConnection();
    mPid = new qint64(10000);
    for(int i = 0; i < MAX_PIN_LENGTH; i++) {
        mAnaVals.append(0);
        mDigVals.append(0);
        mPinMods.append(0);
        mpinRWs.append(0);
    }
}

Arduino::~Arduino()
{
    isRunning = false;
    stop();
}

void Arduino::initConnection()
{
    connect(this, &Arduino::readyReadStandardOutput, [=]{
        this->updateStatus();
    });
}

void Arduino::start()
{
    qDebug() << "start simulating arduino";
    this->open(QIODevice::ReadOnly);
    isRunning = true;

    QtConcurrent::run([=]{
        this->updateStatus();
    });
}

void Arduino::stop()
{
    isRunning = false;
    this->terminate();
//    QString program = "kill";
//    QStringList args;
//    args << QString::number(*mPid);
//    QProcess::startDetached(program, args);
}

void Arduino::updateStatus()
{
    char data[100];
    qint64 len = -1;
    if(!isRunning)
        return;

    if(this->canReadLine()) {
        len = this->readLine(data, 100);
        if(len > 0) {
            QString line(data);
            QStringList cmps = line.split(":");
            if(cmps.at(0) == "digVal") {
                this->updateDigVals(cmps.at(1));
            }
            if(cmps.at(0) == "anaVal") {
                this->updateAnaVals(cmps.at(1));
            }
            if(cmps.at(0) == "pinMod") {
                this->updatePinMods(cmps.at(1));
            }
            if(cmps.at(0) == "pinRW") {
                this->updatePinRWs(cmps.at(1));
            }
        }
    }
}

void Arduino::updateAnaVals(QString datas)
{
    QStringList sValues = datas.split(",");
    sValues.removeLast();
    for(int i = 0; i < MAX_PIN_LENGTH; i++) {
        QString sValue = sValues.at(i);
        mAnaVals[i] = sValue.toInt();
    }
    emit anaValsChanged();
}

void Arduino::updateDigVals(QString datas)
{
    QStringList sValues = datas.split(",");
    sValues.removeLast();
    for(int i = 0; i < MAX_PIN_LENGTH; i++) {
        QString sValue = sValues.at(i);
        mDigVals[i] = sValue.toInt();
    }
    emit digValsChanged();
}

void Arduino::updatePinMods(QString datas)
{
    QStringList sValues = datas.split(",");
    sValues.removeLast();
    for(int i = 0; i < MAX_PIN_LENGTH; i++) {
        QString sValue = sValues.at(i);
        mPinMods[i] = sValue.toInt();
    }
    emit pinModVasChanged();
}

void Arduino::updatePinRWs(QString datas)
{
    QStringList sValues = datas.split(",");
    sValues.removeLast();
    for(int i = 0; i < MAX_PIN_LENGTH; i++) {
        QString sValue = sValues.at(i);
        mpinRWs[i] = sValue.toInt();
    }
    emit pinRWValsChanged();
}
