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
#define VCNL4040_ALS_CONFIG         0x00 ///< Ambient light sensor configuration
#define VCNL4040_PS_CONF1_L         0x03 ///< Proximity sensor configuration 1/2
#define VCNL4040_PS_DATA         0x08 ///< Proximity sensor data
#define VCNL4040_ALS_DATA         0x09 ///< Ambient light sensor data
#define VCNL4040_DEVICE_ID       0x0C ///< Device ID

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


  Adafruit_BusIO_Register 
    *PS_CONFIG_12,  ///< BusIO Register for PS_CONFIG1 and PS_CONFIG2
    *ALS_CONFIG;  ///< BusIO Register for ALS_CONFIG

private:
  bool _init(void);

  Adafruit_I2CDevice *i2c_dev;
};

#endif
