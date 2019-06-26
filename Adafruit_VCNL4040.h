/*!
 *  @file Adafruit_VCNL4040.h
 *
 * 	I2C Driver for VCNL4040 proximity and ambient light sensor library
 *
 * 	This is a library for the Adafruit VCNL4040 breakout:
 * 	http://www.adafruit.com/products
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *
 *	BSD license (see license.txt)
 */

#ifndef _ADAFRUIT_VCNL4040_H
#define _ADAFRUIT_VCNL4040_H

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_BusIO_Register.h>

#define VCNL4040_I2CADDR_DEFAULT 0x60 ///< VCNL4040 default i2c address

// All addresses are for 16bit registers; 
// duplicates are for high or low bytes that aren't used together
#define VCNL4040_ALS_CONFIG         0x00 ///< Ambient light sensor configuration register
#define VCNL4040_ALS_THDH           0x01 ///< Ambient light high threshold register
#define VCNL4040_ALS_THDL           0x02 ///< Ambient light low threshold register
#define VCNL4040_PS_CONF1_L         0x03 ///< Proximity sensor configuration 1/2 register
#define VCNL4040_PS_MS_H         0x04 ///< Proximity sensor configuration 1/2 register
#define VCNL4040_PS_THDL          0x06 /// < Proximity sensor low threshold register
#define VCNL4040_PS_THDH          0x07 /// < Proximity sensor high threshold register
#define VCNL4040_PS_DATA         0x08 ///< Proximity sensor data register
#define VCNL4040_ALS_DATA         0x09 ///< Ambient light sensor data register
#define VCNL4040_WHITE_DATA         0x0A ///< White light sensor data register
#define VCNL4040_INT_FLAG         0x0B ///< Interrupt status register
#define VCNL4040_DEVICE_ID       0x0C ///< Device ID

/*
~
        H PS_MS R / W 0x00 White channel enable / disable, PS mode selection, PS protection setting, and LED current selection

0x05    L PS_CANC_L R / W 0x00 PS cancellation level setting
        H PS_CANC_M R / W 0x00 PS cancellation level setting

0x06    L PS_THDL_L R / W 0x00 PS low interrupt threshold setting LSB byte
        H PS_THDL_M R / W 0x00 PS low interrupt threshold setting MSB byte

0x07    L PS_THDH_L R / W 0x00 PS high interrupt threshold setting LSB byte
        H PS_THDH_M R / W 0x00 PS high interrupt threshold setting MSB byte

0x08    L PS_Data_L R 0x00 PS LSB output data
        H PS_Data_M R 0x00 PS MSB output data

0x09    L ALS_Data_L R 0x00 ALS LSB output data
        H ALS_Data_M R 0x00 ALS MSB output data

0x0A    L White_Data_L R 0x00 White LSB output data
        H White_Data_M R 0x00 White MSB output data
0x0B
        H INT_Flag R 0x00 ALS, PS interrupt flags

0x0C    L ID_L R 0x86 Device ID LSB
        H ID_M R 0x01 Device ID MSB

 */
typedef enum proximity_type {
  VCNL4040_PROXIMITY_INT_DISABLE,
  VCNL4040_PROXIMITY_INT_CLOSE,
  VCNL4040_PROXIMITY_INT_AWAY,
  VCNL4040_PROXIMITY_INT_CLOSE_AWAY,
} VCNL4040_Interrupt;
/*
 (0 : 0) = interrupt disable, (0 : 1) = trigger when close, (1 : 0)= trigger when away,
(1 : 1)= trigger when close or away */


/**
 * @brief Data rate options.
 *
 * Allowed values for `setDataRate`.
 */
// typedef enum _data_rate {
//   VCNL4040_RATE_ONE_SHOT, /**< ONE_SHOT: Put the sensor in a low power shutdown mode
//                               that will only take a measurement when `takeMeasurement`
//                                is called **/
//   VCNL4040_RATE_1_HZ, /** 1 hz  **/
//   VCNL4040_RATE_10_HZ, /** 10 hz  **/
//   VCNL4040_RATE_25_HZ, /** 25 hz  **/
//   VCNL4040_RATE_50_HZ, /** 50 hz  **/
//   VCNL4040_RATE_75_HZ, /** 75 hz  **/
// } VCNL4040_DataRate;

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            VCNL4040 Current and Power Sensor
 */
class Adafruit_VCNL4040 {
public:
  Adafruit_VCNL4040();
  boolean begin(uint8_t i2c_addr=VCNL4040_I2CADDR_DEFAULT, TwoWire *wire = &Wire);
  uint16_t readProximity(void);
  uint16_t readAmbientLight(void);
  uint16_t readWhite(void);
  void enableAmbientLightInterrupts(void);
  void disableAmbientLightInterrupts(void);
  uint16_t readAmbientLightHighThreshold(void);
  void setAmbientLightHighThreshold(uint16_t high_threshold);
  uint16_t readAmbientLightLowThreshold(void);
  void setAmbientLightLowThreshold(uint16_t low_threshold);
  uint8_t readInterruptStatus(void);
  void enableProximityInterrupts(VCNL4040_Interrupt interrupt_type);
  void disableProximityInterrupts(void);
  void setProximityLowThreshold(uint16_t);


  Adafruit_BusIO_Register 
    *PS_CONFIG_12,  ///< BusIO Register for PS_CONFIG1 and PS_CONFIG2
    *ALS_CONFIG,   ///< BusIO Register for ALS_CONFIG
    *PS_MS;  ///< BusIO Register for PS_MS

private:
  bool _init(void);

  Adafruit_I2CDevice *i2c_dev;
};

#endif

