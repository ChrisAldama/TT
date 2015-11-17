#include "comm.h"
#include "math.h"
#include <QDebug>

Comm::Comm(QObject *parent) : QObject(parent),
    fd(-1)
{

}


bool Comm::buttonValue(int idx)
{
    Q_UNUSED(idx);
    static bool v = true;

    bool r= v;
    v = !v;
    return r;
}

float Comm::tempValue()
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

void Comm::motor(int idx, int cmd)
{
    qDebug() << "Motor" << idx << ":" << cmd;
}



void Comm::setLed(int idx, bool v)
{
    qDebug() << "Led" << idx << ":" << v;

}

bool Comm::open()
{
    return true;

}

