//-----------------------------------------------------
// AM2320_Sensor.cpp - Source File
// Library for Programming I2C AM2320 Temp & Humidity Sensor
// by: Anas Kuzechie (June, 2022)
//-----------------------------------------------------
#include <Arduino.h>
#include <AM2320_Sensor.h>
//========================================================================
// Function Prototypes
//========================================================================
extern "C"
{
  /*defined in S file and coded in assembly*/
  void I2C_init();
  void I2C_START();
  void I2C_write(byte);
  void I2C_read();
  void I2C_read_NACK();
  void I2C_STOP();
  void delay_2ms();
}
//========================================================================
// Constructor
//========================================================================
AM2320_Sensor::AM2320_Sensor() {}
//========================================================================
// Public Methods
//========================================================================
void AM2320_Sensor::Initialize()
{
  I2C_init();
}
//========================================================================
void AM2320_Sensor::readSensorBytes()
{
  /*wake up sensor from sleep mode*/
  I2C_START();                /*send START condition*/
  I2C_write(0xB8);            /*send write address of AM2320*/
  I2C_STOP();                 /*send STOP condition*/

  /*write function code to point to data register of sensor*/
  I2C_START();                /*send START condition*/
  I2C_write(0xB8);            /*send write address of AM2320*/
  I2C_write(0x03);            /*send function code: read data reg*/
  I2C_write(0x00);            /*send start address of data reg*/
  I2C_write(0x04);            /*send number of registers to read*/
  I2C_STOP();                 /*send STOP condition*/

  delay_2ms();                /*wait 2ms*/

  /*read & store humidity & temp bytes from sensor*/
  I2C_START();                /*send START condition*/
  I2C_write(0xB9);            /*send read address of AM2320*/
  //------------------------------------------------------------------
  I2C_read();                 /*read function code (0x30)*/
  I2C_read();                 /*read number of registers (4)*/
  //------------------------------------------------------------------
  I2C_read();                 /*read humidity high byte*/
  humHigh = TWDR;             /*copy humidity high byte from TWDR*/
  I2C_read();                 /*read humidity low byte*/
  humLow = TWDR;              /*copy humidity low byte from TWDR*/
  //------------------------------------------------------------------
  I2C_read();                 /*read temp high byte*/
  tempHigh = TWDR;            /*copy temp high byte from TWDR*/
  I2C_read();                 /*read temp low byte*/
  tempLow = TWDR;             /*copy temp low byte from TWDR*/
  //------------------------------------------------------------------
  I2C_read();                 /*read low byte CRC*/
  I2C_read_NACK();            /*read high byte CRC & send NACK pulse*/
  //------------------------------------------------------------------
  I2C_STOP();                 /*send STOP condition*/

  /*compute 16-bit humidity & temp values*/
  hum  = (humHigh << 8) | humLow;   /*compute 16-bit humidity*/
  temp = (tempHigh << 8) | tempLow; /*compute 16-bit temp*/
}
//========================================================================
float AM2320_Sensor::getTemperature()
{
  return(float(temp)/10.0);   /*return floating-point temp value*/
}
//========================================================================
float AM2320_Sensor::getHumidity()
{
  return(float(hum)/10.0);   /*return floating-point humidity value*/
}