#ifndef COMM_H
#define COMM_H

#include <QObject>
#include <QString>
#include <stdint.h>

class Comm : public QObject
{
    Q_OBJECT

    enum Sensor {
        PHOTO = 0,
        CONTACT,
        TEMP,
        MOTOR,
        LED
    };

    struct SMess {
        uint8_t sensor: 5,
                 idx: 3;
        uint8_t val;
    };


public:
    explicit Comm(QObject *parent = 0);
    Comm(const QString &i2cDevice, int idx);

    uint8_t poll(const SMess mess);

    bool buttonValue(int idx);
    int tempValue();
    int analogValue();
    int motor(int idx, int cmd);


signals:
    void error(const QString &msg, int addr = 0x40);

public slots:
    void openDevice(const QString &msg, int addr);
    void setLed(int idx, bool v);
private:
    int fd = -1;
};

#endif // COMM_H
