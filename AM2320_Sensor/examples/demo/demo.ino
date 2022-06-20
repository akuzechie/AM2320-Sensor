//--------------------------------------------------
// AM2320 Sensor: Temp & Humidity on Serial Monitor
// using AM2320_Sensor.h Library
// by: Anas Kuzechie (June, 2022)
//---------------------------------------------------
#include <AM2320_Sensor.h>
//-------------------------
AM2320_Sensor AM2320;       /*declare object to constructor*/
//=============================================================
void setup()
{
  AM2320.Initialize();      /*initialize I2C of ATmega328*/
  Serial.begin(9600);
}
//=============================================================
void loop()
{
  AM2320.readSensorBytes(); /*read temp & humidity bytes*/
  //-----------------------------------------------------------
  float t = AM2320.getTemperature();/*get floating-point temp*/
  float h = AM2320.getHumidity();   /*get floating-point hum*/
  //-----------------------------------------------------------
  Serial.print(t); Serial.print("°C   ");/*display on monitor*/
  Serial.print(h); Serial.println("%");
  //--------------------------------------
  delay(2000);              /*get sensor data every 2s*/
}