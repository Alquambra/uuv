#if !defined( SENSORS_BASE_H)
#define SENSORS_BASE_H

#include <math.h>
#include <iostream>
#include <unistd.h>

using namespace std;


/**
* @brief класс Sensor. Является базовым для всех датчиков 
*/
class Sensor
{
    public:

        /**
        * @brief инициализация датчика
        */
        virtual void startup() {}


        /**
        * @brief
        */
        virtual void get_binary_data() {}


        /**
        * @brief калибровка
        */
        virtual void calibrate(int) {}

    protected:


        /**
        * @brief Преобразование старшего и младшего байтов в 16-битное число
        * @param low младший байт
        * @param high старший байт
        * @return value 2-х байтовое значение 
        */
        static int get_16bit_value(unsigned int low, unsigned int high)
        {
            

            int value;
            long temp;

            temp = (high << 8) | low;
            if (temp > 32768) temp -= 65536;
            value = static_cast <int> (temp);
            return value;
        }


        /**
        * @brief Преобразование данных АЦП в единицу счисления величины
        * @param value 2-х байтовое значение
        * @param range диапазон измерений датчика
        * @return действительное значение величины
        */
        static float convert(int value, int range)
        {
            
            return value / 32768.0 * range;
        }
};


/**
* @brief класс Sensor3Axis. Наследуется от Sensor. 
* Является базовым для трехосевых датчиков.
*/
class Sensor3Axis: public Sensor
{
    public:

        /**
        * @brief получить диапазон измерений датчика
        * @return диапазон измерений датчика
        */
        virtual int get_range() {}


        /**
        * @brief получить значения измерений датчика по трем осям
        * @param x значение по оси x
        * @param y значение по оси y
        * @param z значение по оси z
        */
        virtual void get_3d_magnitude(float &x, float &y ,float &z) {}


        /**
        * @brief преобразовать значения измерений датчика по трем осям 
        * от двоичных к действительным 
        */
        virtual void get_sample() {}

    protected:


        /**
        * @brief установить значения измерений датчика по трем осям
        * @param x значение по оси x
        * @param y значение по оси y
        * @param z значение по оси z
        */
        virtual void set_3d_magnitude(float x, float y, float z) {}


        /**
        * @brief установить диапазон измерений датчика
        * @param range диапазон измерений датчика
        */
        virtual void set_range(int range) {}       
};


/**
* @brief класс Accelerometer. Наследуется от Sensor3Axis.
* Является базовым для трехосевых акселерометров.
*/
class Accelerometer: public Sensor3Axis
{
    private:

        float ax, ay, az;
        int range;

    public:


        /**
        * @brief конструктор класса Accelerometer
        */
        Accelerometer()
        {
            this->ax = 0;
            this->ay = 0;
            this->az = 0;
            this->range = 0;
        }


        /**
        * @brief получить значения ускорений акселерометра по трем осям
        * @param x значение по оси x
        * @param y значение по оси y
        * @param z значение по оси z
        */
        void get_3d_magnitude(float &x, float &y ,float &z)
        {
            x = this->ax;
            y = this->ay;
            z = this->az;
        }


        /**
        * @brief получить диапазон измерений акселерометра
        * @return диапазон измерений акселерометра
        */
        int get_range()
        {
            return this->range;
        }


        /**
        * @brief преобразовать значения измерений ускорений по трем осям 
        * от двоичных к действительным 
        */
        void get_sample()
        {
            ax = convert(this->ax, this->range);
            ay = convert(this->ay, this->range);
            az = convert(this->az, this->range);
        }

    protected:


        /**
        * @brief установить значения ускорений акселерометра по трем осям
        * @param x значение по оси x
        * @param y значение по оси y
        * @param z значение по оси z
        */
        void set_3d_magnitude(float x, float y, float z)
        {
            this->ax = x;
            this->ay = y;
            this->az = z;
        }


        /**
        * @brief установить диапазон измерений акселерометра
        * @param range диапазон измерений акселерометра
        */
        void set_range(int range)
        {
            this->range = range;
        }


        /**
        * @brief Калибровка акселерометра.
        * Для калибровки необходимо разместить датчик на поверхности
        * параллельной полу и держать его неподвижным.
        * @param rounds количество измерений во время калибровки
        */
        void calibrate(int rounds)
        {
            float axsum = 0.0f, aysum = 0.0f, azsum = 0.0f;
            float axoffset = 0.0f, ayoffset = 0.0f, azoffset = 0.0f;

            std::cout << "Keep accelerometer according to ax = 0 ay = 0 az = 1" << std::endl;

            for (int i; i < rounds; i++)
            {
                get_binary_data();
                get_sample();

                std::cout << "ax = " << ax << " ay = " << ay << " az = " << az << endl;

                axsum += ax;
                aysum += ay;
                azsum += az;
                usleep(25000);
            }
            axoffset = axsum / rounds;
            ayoffset = aysum / rounds;
            azoffset = azsum / rounds - 1;
        }
};


/**
* @brief класс Accelerometer. Наследуется от Sensor3Axis.
* Является базовым для трехосевых акселерометров.
*/
class Gyroscope: public Sensor3Axis
{
    private:

        float gx, gy, gz;
        int range;

    public:


        /**
        * @brief получить значения ускорений гироскопа по трем осям
        * @param x значение по оси x
        * @param y значение по оси y
        * @param z значение по оси z
        */
        void get_3d_magnitude(float &x, float &y ,float &z)
        {
            x = this->gx;
            y = this->gy;
            z = this->gz;
        }


        /**
        * @brief получить диапазон измерений гироскопа
        * @return диапазон измерений гироскопа
        */
        int get_range()
        {
            return this->range;
        }


        /**
        * @brief преобразовать значения измерений угловой скорости по трем осям 
        * от двоичных к действительным 
        */
        void get_sample()
        {
            gx = convert(this->gx, this->range);
            gy = convert(this->gy, this->range);
            gz = convert(this->gz, this->range);
        }


        /**
        * @brief конструктор класса Gyroscope
        */
        Gyroscope()
        {
            this->gx = 0;
            this->gy = 0;
            this->gz = 0;
            this->range = 0;
        }

    protected:


        /**
        * @brief установить значения угловой скорости гироскопа по трем осям
        * @param x значение по оси x
        * @param y значение по оси y
        * @param z значение по оси z
        */
        void set_3d_magnitude(float x, float y, float z)
        {
            this->gx = x;
            this->gy = y;
            this->gz = z;
        }


        /**
        * @brief установить диапазон измерений гироскопа
        * @param range диапазон измерений гироскопа
        */
        void set_range(int range)
        {
            this->range = range;
        }


        /**
        * @brief Калибровка гироскопа.
        * Для калибровки гироскопа необходимо держать датчик неподвижным.
        * @param rounds 
        */
        void calibrate(int rounds)
        {
            float gxsum = 0.0f, gysum = 0.0f, gzsum = 0.0f;
            float gxoffset = 0.0f, gyoffset = 0.0f, gzoffset = 0.0f;

            std::cout << "Keep gyroscope steady" << std::endl;

            for (int i; i < rounds; i++)
            {
                get_binary_data();
                get_sample();

                std::cout << "gx = " << gx << " gy = " << gy << " gz = " << gz << std::endl;

                gxsum += gx;
                gysum += gy;
                gzsum += gz;
                usleep(25000);
            }
            gxoffset = gxsum / rounds;
            gyoffset = gysum / rounds;
            gzoffset = gzsum / rounds;
        }
};


/**
* @brief класс Accelerometer. Наследуется от Sensor3Axis.
* Является базовым для трехосевых акселерометров.
*/
class Magnetometer: public Sensor3Axis
{
    private:

        float mx, my, mz;
        int range;

    public:


        /**
        * @brief получить значения ускорений магнетометра по трем осям
        * @param x значение по оси x
        * @param y значение по оси y
        * @param z значение по оси z
        */
        void get_3d_magnitude(float &x, float &y ,float &z)
        {
            x = this->mx;
            y = this->my;
            z = this->mz;
        }


        /**
        * @brief получить диапазон измерений магнетометра
        * @return диапазон измерений магнетометра
        */
        int get_range()
        {
            return this->range;
        }


        /**
        * @brief преобразовать значения измерений магнитной индукции по трем осям 
        * от двоичных к действительным 
        */
        void get_sample()
        {
            mx = convert(this->mx, this->range);
            my = convert(this->my, this->range);
            mz = convert(this->mz, this->range);
        }


        /**
        * @brief конструктор класса Magnetometer
        */
        Magnetometer()
        {
            this->mx = 0;
            this->my = 0;
            this->mz = 0;
            this->range = 0;
        }

    protected:


        /**
        * @brief установить значения магнитной индукции магнетометра по трем осям
        * @param x значение по оси x
        * @param y значение по оси y
        * @param z значение по оси z
        */
        void set_3d_magnitude(float x, float y, float z)
        {
            this->mx = x;
            this->my = y;
            this->mz = z;
        }      


        /**
        * @brief установить диапазон измерений магнетометра
        * @param range диапазон измерений магнетометра
        */
        void set_range(int range)
        {
            this->range = range;
        }   

  
        /**
        * @brief Калибровка магнетометра.
        * Для калибровки магнетометра необходимо вращать датчик 
        * вокруг трех осей во всех направлениях.
        * @param rounds
        */
        void calibrate(int rounds)
        {
            float mxmax = -32768.0f, mymax = -32768.0f, mzmax = -32768.0f;
            float mxmin = 32767.0f, mymin = 32767.0f, mzmin = 32767.0f;
            float mxoffset = 0.0f, myoffset = 0.0f, mzoffset = 0.0f;
            float mxscale = 0.0f, myscale = 0.0f, mzscale = 0.0f;
            float chordx = 0.0f, chordy = 0.0f, chordz = 0.0f;
            float chord_average = 0.0f;

            std::cout << "Rotate compass" << std::endl;

            for (int i = 0; i < rounds; i++)
            {
                get_binary_data();
                get_sample();

                std::cout << "mx = " << mx << " my = " << my << " mz = " << mz << std::endl;

                mxmin = min(mxmin, mx);
                mymin = min(mymin, my);
                mzmin = min(mzmin, mz);

                mxmax = max(mxmax, mx);
                mymax = max(mymax, my);
                mzmax = max(mzmax, mz);
            }
            mxoffset = (mxmax + mxmin) / 2.0f;
            myoffset = (mymax + mymin) / 2.0f;
            mzoffset = (mzmax + mzmin) / 2.0f;

            chordx = (mxmax - mxmin) / 2.0f;
            chordy = (mymax - mymin) / 2.0f;
            chordz = (mzmax - mzmin) / 2.0f;

            chord_average = (chordx + chordy + chordz) / 3;

            mxscale = chord_average / chordx;
            myscale = chord_average / chordy;
            mzscale = chord_average / chordz;
        }
};


/**
* @brief  класс Barometer. Наследуется от Sensor.
* Является базовым для барометров.
*/
class Barometer : public Sensor
{
    protected:

        double Pressure;


        /**
        * @brief установить значение давления
        * @param Pressure значение давление
        */
        void setP(double Pressure)
        {
            this->Pressure = Pressure;
        }

    public:

    
        /**
        * @brief конструктор класса Barometer
        */
        Barometer()
        {
            this->Pressure = 0;
        }

   
        /**
        * @brief получить значение давления
        * @return значение давления
        */
        double getP()
        {
            return this->Pressure;
        }


        /**
        * @brief получить значение глубины
        * @return значение глубины
        */ 
        float getDepth()
        {
            return static_cast<float>(getP() - 101325) / (9.80665 * 997);
        }


        /**
        * @brief получить значение высоты
        * @return значение высоты
        */
        float getAltitude()
        {
            return static_cast<float>(1 - pow((getP() / 101325), .190295) * 145366.45 * .3048);
        }
};

#endif
