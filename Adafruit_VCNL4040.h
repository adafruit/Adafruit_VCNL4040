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
#define VCNL4040_PS_MS_H            0x04 ///< Proximity sensor configuration 1/2 register
#define VCNL4040_PS_THDL            0x06 ///< Proximity sensor low threshold register
#define VCNL4040_PS_THDH            0x07 ///< Proximity sensor high threshold register
#define VCNL4040_PS_DATA            0x08 ///< Proximity sensor data register
#define VCNL4040_ALS_DATA           0x09 ///< Ambient light sensor data register
#define VCNL4040_WHITE_DATA         0x0A ///< White light sensor data register
#define VCNL4040_INT_FLAG           0x0B ///< Interrupt status register
#define VCNL4040_DEVICE_ID          0x0C ///< Device ID



/*
    # Ambient light sensor integration times
    ALS_80MS = const(0x0)
    ALS_160MS = const(0x1)
    ALS_320MS = const(0x2)
    ALS_640MS = const(0x3)

    # Proximity sensor integration times
    PS_1T = const(0x0)
    PS_1_5T = const(0x1)
    PS_2T = const(0x2)
    PS_2_5T = const(0x3)
    PS_3T = const(0x4)
    PS_3_5T = const(0x5)
    PS_4T = const(0x6)
    PS_8T = const(0x7)

    # LED current settings
    LED_50MA = const(0x0)
    LED_75MA = const(0x1)
    LED_100MA = const(0x2)
    LED_120MA = const(0x3)
    LED_140MA = const(0x4)
    LED_160MA = const(0x5)
    LED_180MA = const(0x6)
    LED_200MA = const(0x7)

    # LED duty cycle settings
    LED_1_40 = const(0x0)
    LED_1_80 = const(0x1)
    LED_1_160 = const(0x2)
    LED_1_320 = const(0x3)
 */

/**
 * @brief Proximity LED current values
 *
 * Allowed values for `setProximityLEDCurrent`.
 */
typedef enum led_current {
  VCNL4040_LED_CURRENT_50MA,
  VCNL4040_LED_CURRENT_75MA,
  VCNL4040_LED_CURRENT_100MA,
  VCNL4040_LED_CURRENT_120MA,
  VCNL4040_LED_CURRENT_140MA,
  VCNL4040_LED_CURRENT_160MA,
  VCNL4040_LED_CURRENT_180MA,
  VCNL4040_LED_CURRENT_200MA,
} VCNL4040_LEDCurrent;

/**
 * @brief Proximity LED duty cycle values
 *
 * Allowed values for `setProximityLEDDutyCycle`.
 */
typedef enum led_duty_cycle {
  VCNL4040_LED_DUTY_1_40,
  VCNL4040_LED_DUTY_1_80,
  VCNL4040_LED_DUTY_1_160,
  VCNL4040_LED_DUTY_1_320,
} VCNL4040_LEDDutyCycle;


/**
 * @brief Ambient light integration time values
 *
 * Allowed values for `setAmbientIntegrationTime`.
 */
typedef enum ambient_integration_time {
  VCNL4040_AMBIENT_INTEGRATION_TIME_80MS,
  VCNL4040_AMBIENT_INTEGRATION_TIME_160MS,
  VCNL4040_AMBIENT_INTEGRATION_TIME_320MS,
  VCNL4040_AMBIENT_INTEGRATION_TIME_640MS,
} VCNL4040_AmbientIntegration;


/**
 * @brief Proximity measurement integration time values
 *
 * Allowed values for `setProximityIntegrationTime`.
 */
typedef enum proximity_integration_time {
  VCNL4040_PROXIMITY_INTEGRATION_TIME_1T,
  VCNL4040_PROXIMITY_INTEGRATION_TIME_1_5T,
  VCNL4040_PROXIMITY_INTEGRATION_TIME_2T,
  VCNL4040_PROXIMITY_INTEGRATION_TIME_2_5T,
  VCNL4040_PROXIMITY_INTEGRATION_TIME_3T,
  VCNL4040_PROXIMITY_INTEGRATION_TIME_3_5T,
  VCNL4040_PROXIMITY_INTEGRATION_TIME_4T,
  VCNL4040_PROXIMITY_INTEGRATION_TIME_8T,
} VCNL4040_ProximityIntegration;
/**
 * @brief Proximity interrupt types
 *
 * Allowed values for `enableProximityInterrupts`.
 */
typedef enum proximity_type {
  VCNL4040_PROXIMITY_INT_DISABLE,
  VCNL4040_PROXIMITY_INT_CLOSE,
  VCNL4040_PROXIMITY_INT_AWAY,
  VCNL4040_PROXIMITY_INT_CLOSE_AWAY,
} VCNL4040_ProximityType;

/**
 * @brief Interrupt types
 *
 * Values to be matched against the byte returned from `getInterruptStatus`.
 */
typedef enum interrupt_type {
  VCNL4040_PROXIMITY_AWAY,
  VCNL4040_PROXIMITY_CLOSE,
  VCNL4040_AMBIENT_HIGH=4,
  VCNL4040_AMBIENT_LOW,
} VCNL4040_InterruptType;

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            the VCNL4040 I2C Digital Potentiometer
 */
class Adafruit_VCNL4040 {
public:
  Adafruit_VCNL4040();
  boolean begin(uint8_t i2c_addr=VCNL4040_I2CADDR_DEFAULT, TwoWire *wire = &Wire);
  uint16_t getProximity(void);
  uint16_t getAmbientLight(void);
  uint16_t getWhiteLight(void);
  void enableAmbientLightInterrupts(bool enable);
  uint16_t getAmbientLightHighThreshold(void);
  void setAmbientLightHighThreshold(uint16_t high_threshold);
  uint16_t getAmbientLightLowThreshold(void);
  void setAmbientLightLowThreshold(uint16_t low_threshold);
  uint8_t getInterruptStatus(void);
  void enableProximityInterrupts(VCNL4040_ProximityType interrupt_condition);
  void setProximityLowThreshold(uint16_t low_threshold);
  void setProximityHighThreshold(uint16_t high_threshold);
  void setProximityIntegrationTime(VCNL4040_ProximityIntegration integration_time);
  void setAmbientIntegrationTime(VCNL4040_AmbientIntegration integration_time);
  void setProximityLEDCurrent(VCNL4040_LEDCurrent led_current);
  void setProximityLEDDutyCycle(VCNL4040_LEDDutyCycle duty_cycle);
  void enableProximity(bool enable);
  void setProximityHighResolution(bool high_resolution);
  void enableAmbientLight(bool enable);
  void enableWhiteLight(bool enable);


  Adafruit_BusIO_Register 
    *PS_CONFIG_12,  ///< BusIO Register for PS_CONFIG1 and PS_CONFIG2
    *ALS_CONFIG,   ///< BusIO Register for ALS_CONFIG
    *PS_MS;  ///< BusIO Register for PS_MS

private:
  bool _init(void);

  Adafruit_I2CDevice *i2c_dev;
};

#endif

