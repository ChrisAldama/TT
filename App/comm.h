#ifndef COMM_H
#define COMM_H

#include <QObject>
#include <QString>
#include <stdint.h>

//using Out = uint8_t;
typedef uint8_t Out;

class Comm : public QObject
{
    Q_OBJECT

public:

    enum Sensor {
        CONTACT = 0,
        TEMP,
        MOTOR,
        LED,
        ANALOG

    };

    struct SMess {
        uint8_t sensor;
        uint8_t idx;
        uint8_t val;
    };

public:
    explicit Comm(QObject *parent = 0);

    virtual bool buttonValue(int idx);
    virtual float tempValue();
    virtual int analogValue();
    virtual void motor(int idx, int cmd);
    virtual void setLed(int idx, bool v);
    virtual bool open();

signals:
    void error(const QString &msg, int addr = 0x40);

public slots:
private:
    int fd;
};

#endif // COMM_H
