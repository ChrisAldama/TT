#include "comm.h"
#include "math.h"
#include <QDebug>

Comm::Comm(QObject *parent) : QObject(parent)
{

}

uint8_t Comm::poll(const SMess mess)
{
    Q_UNUSED(mess);

    return 0;
}

bool Comm::buttonValue(int idx)
{
    Q_UNUSED(idx);
    static bool v = true;

    bool r= v;
    v = !v;
    return r;
}

int Comm::tempValue()
{
    static int t = 0;
    int r = t;
    t = (t + 1) % 101;
    return r;
}

int Comm::analogValue()
{
    static int c = 0;
    return int(sin(c++)*100);
}

int Comm::motor(int idx, int cmd)
{
    qDebug() << "Motor" << idx << ":" << cmd;
}

Comm::Comm(const QString &i2cDevice, int idx)
{
    openDevice(i2cDevice, idx);
}

void Comm::openDevice(const QString &msg, int addr)
{
    qDebug() << "open: " << msg << ":" << addr;

}

void Comm::setLed(int idx, bool v)
{
    qDebug() << "Led" << idx << ":" << v;

}

