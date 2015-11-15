#include "commserial.h"
#include <QDebug>

#ifdef __linux__
#define SERIAL "ttyUsb0"
#elif _WIN32
#define SERIAL "COM3"
#else
#define SERIAL "default"
#endif

CommSerial::CommSerial(QObject *parent):
    Comm(parent),
    port()
{
    port.setPortName(SERIAL);
    qDebug() << "Out Size:" << sizeof(Out);
}

bool CommSerial::buttonValue(int idx)
{
    SMess m;
    m.sensor = CONTACT;
    m.idx = idx;

    Out out;

    port.write((const char*)&m, sizeof(m));
    port.waitForBytesWritten(1000);
    port.waitForReadyRead(1000);
    port.read((char*)&out, sizeof(Out));

    qDebug() << "button" << idx << ": " << out;

    return out;
}

float CommSerial::tempValue()
{
    SMess m;
    m.sensor = TEMP;
    Out out;

    port.write((const char*)&m, sizeof(m));
    port.waitForBytesWritten(1000);
    port.waitForReadyRead(1000);
    port.read((char*)&out, sizeof(Out));

    qDebug() << "temp: " << out;

    return float(out)/100.0f;

}

int CommSerial::analogValue()
{
    SMess m;
    m.sensor = ANALOG;
    Out out;

    port.write((const char*)&m, sizeof(m));
    port.waitForBytesWritten(1000);
    port.waitForReadyRead(1000);
    port.read((char*)&out, sizeof(Out));

    qDebug() << "analog: " << out;

    return out;

}

void CommSerial::motor(int idx, int cmd)
{
    SMess m;
    m.sensor = MOTOR;
    m.idx = idx;
    m.val = cmd;

    Out out;

    port.write((const char*)&m, sizeof(m));
    port.waitForBytesWritten(1000);
    port.waitForReadyRead(1000);
    port.read((char*)&out, sizeof(Out));

    qDebug() << "motor" << idx << ": " << out;
}

void CommSerial::setLed(int idx, bool v)
{
    SMess m;
    m.sensor = LED;
    m.idx = idx;
    m.val = v;

    Out out;

    port.write((const char*)&m, sizeof(m));
    port.waitForBytesWritten(1000);
    port.waitForReadyRead(1000);
    port.read((char*)&out, sizeof(Out));

    qDebug() << "led" << idx << ": " << out;
}

bool CommSerial::open()
{
    return port.open(QIODevice::ReadWrite);

}

