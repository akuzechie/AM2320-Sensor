//-----------------------------------------------------------
// AM2320_Sensor.h - Header File
// Library for Programming I2C AM2320 Temp & Humidity Sensor
// by: Anas Kuzechie (June, 2022)
//-----------------------------------------------------------
//header guards
#ifndef AM2320_Sensor_h
#define AM2320_Sensor_h
//-----------------------------------------------------------------------
//class definition
class AM2320_Sensor
{
    public:
        AM2320_Sensor();
        void Initialize();
        void readSensorBytes();
        float getTemperature();
        float getHumidity();
    private:
        byte humHigh, humLow, tempHigh, tempLow;
        unsigned int temp, hum;
};
//----------------------------------------------------------------------
#endif