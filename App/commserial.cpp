#include "commserial.h"

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

    return out.v;
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

    return out.f;

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

    return out.b;

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
}

bool CommSerial::open()
{
    return port.open(QIODevice::ReadWrite);

}

