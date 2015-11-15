#ifndef COMMSERIAL_H
#define COMMSERIAL_H

#include "comm.h"
#include <QObject>
#include <QtSerialPort>

class CommSerial : public Comm
{
public:
    explicit CommSerial(QObject *parent = 0);

    virtual bool buttonValue(int idx) override;
    virtual float tempValue() override;
    virtual int analogValue() override;
    virtual void motor(int idx, int cmd) override;
    virtual void setLed(int idx, bool v) override;
    virtual bool open() override;

    QSerialPort port;
};

#endif // COMMSERIAL_H
