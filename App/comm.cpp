#include "comm.h"
#include <unistd.h>
#include <fcntl.h>
//#include <linux/i2c-dev.h>
//#include <sys/ioctl.h>


Comm::Comm(QObject *parent) : QObject(parent)
{

}

uint8_t Comm::poll(const SMess mess)
{
    /*const u_int8_t *data = (u_int8_t*)(&mess);
    const size_t size = sizeof(mess);

    for(size_t i = 0; i < size; ++i){
        int res = i2c_smbus_write_byte_data(fd, 0x10, data[i]);
        if(res < 0){
            error("Falló Mandar Lectura de Sensor");
            return 0x00;
        }
    }*/




}

Comm::Comm(const QString &i2cDevice, int idx)
{
    openDevice(i2cDevice, idx);
}

void Comm::openDevice(const QString &msg, int addr)
{
    /*if(fd > 0){
        close(fd);
    }
    const char *file = msg.toLocal8Bit().data();
    fd = open(file, O_RDWR);
    if(fd <= 0){
        error("Falló Abrir: " + msg);
        return;
    }
    if(ioctl(fd, I2C_SLAVE, addr) < 0){
        close(fd);
        fd = -1;
        error("Falló ioctl: " + msg);
    }*/
}

