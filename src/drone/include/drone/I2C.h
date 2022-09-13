#if !defined( I2C_H )
#define I2C_H

#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>

/**
* @brief класс I2C. Предоставляет API для взаимодействия
* с шиной i2c через Linux.
*/
class I2C
{
    public:

        char *i2c_bus;

        /**
        * @brief конструктор класса I2C
        */
        I2C();


        /**
        * @brief конструктор класса I2C
        * @param i2c_bus путь к шине i2c
        */
        I2C(char*);


        /**
        * @brief выбор устройства на шине для взаимодействия
        * @param fd файловый дескриптор
        * @param addr адрес устройства на шине
        * @param name имя устройства
        * @return статус чтения шины
        */
        int  selectDevice(int, int, char*);


        /**
        * @brief отправка байта в указанный регистр
        * @param fd файловый дескриптор
        * @param reg регистр устройства
        * @return статус отправки
        */
        bool i2c_write(int, int);


        /**
        * @brief отправка значения в указанный регистр
        * @param fd файловый дескриптор
        * @param reg регистр устройства
        * @param val значение для отправки
        */
        void i2c_write_register(int, int, int);
        

        /**
        * @brief чтение указанного регистра
        * @param fd файловый дескриптор
        * @param reg регистр устройства
        * @return значение регистра
        */
        int  i2c_read_register(int, int);
        

        /**
        * @brief чтение блока данных из регистров
        * @param fd файловый дескриптор
        * @param buffer буффер для записи данных
        * @param len длина блока
        * @return статус чтения
        */
        bool i2c_read_block(int, unsigned char *, int);
};

#endif