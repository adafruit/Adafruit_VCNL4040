
/*!
 *  @file Adafruit_VCNL4040.cpp
 *
 *  @mainpage Adafruit VCNL4040 proximity and ambient light sensor library
 *
 *  @section intro_sec Introduction
 *
 * 	I2C Driver for the VCNL4040 proximity and ambient light sensor library
 * 
 * 	This is a library for the Adafruit VCNL4040 breakout:
 * 	http://www.adafruit.com/products
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *  @section dependencies Dependencies
 *
 *  This library depends on the Adafruit BusIO library
 *
 *  @section author Author
 *
 *  Bryan Siepert for Adafruit Industries
 *
 * 	@section license License
 * 
 * 	BSD (see license.txt)
 *
 * 	@section  HISTORY
 *
 *     v1.0 - First release
 */

#include "Arduino.h"
#include <Wire.h>

#include "Adafruit_VCNL4040.h"

/*!
 *    @brief  Instantiates a new VCNL4040 class
 */
Adafruit_VCNL4040::Adafruit_VCNL4040(void) {}

/*!
 *    @brief  Sets up the hardware and initializes I2C
 *    @param  i2c_address
 *            The I2C address to be used.
 *    @param  wire
 *            The Wire object to be used for I2C connections.
 *    @return True if initialization was successful, otherwise false.
 */
boolean Adafruit_VCNL4040::begin(uint8_t i2c_address, TwoWire *wire) {
  i2c_dev = new Adafruit_I2CDevice(i2c_address, wire);

  if (!i2c_dev->begin()) {
    return false;
  }

  return _init();
}

boolean Adafruit_VCNL4040::_init(void) {
  Adafruit_BusIO_Register chip_id = 
    Adafruit_BusIO_Register(i2c_dev, VCNL4040_DEVICE_ID, 2);

  // make sure we're talking to the right chip
  if (chip_id.read() != 0x0186) {
    Serial.print("Got other id: "); Serial.println(chip_id.read());
    return false;
  }


  PS_CONFIG_12 = new Adafruit_BusIO_Register(i2c_dev, VCNL4040_PS_CONF1_L, 2);
  ALS_CONFIG = new Adafruit_BusIO_Register(i2c_dev, VCNL4040_ALS_CONFIG, 2);
  PS_MS = new Adafruit_BusIO_Register(i2c_dev, VCNL4040_PS_MS_H, 2);

  Adafruit_BusIO_RegisterBits ps_disable = Adafruit_BusIO_RegisterBits(PS_CONFIG_12, 1, 0);
  Adafruit_BusIO_RegisterBits ps_hd = Adafruit_BusIO_RegisterBits(PS_CONFIG_12, 1, 11);
  
  Adafruit_BusIO_RegisterBits als_disable = Adafruit_BusIO_RegisterBits(ALS_CONFIG, 1, 0);
  Adafruit_BusIO_RegisterBits white_disable = Adafruit_BusIO_RegisterBits(PS_MS, 1, 15);

  ps_disable.write(false);
  ps_hd.write(true);

  als_disable.write(false);
  white_disable.write(false);
  // turn on ints
  Serial.println("Got good device ID, returning true from _init()");

  return true;
}


/**************************************************************************/
/*!
    @brief Reads the proximity sensor register.
    @return The current proximity measurement in units
*/
/**************************************************************************/
uint16_t Adafruit_VCNL4040::readProximity(void) {
  Adafruit_BusIO_Register proximity =
    Adafruit_BusIO_Register(i2c_dev, VCNL4040_PS_DATA, 2);
  delay(10);
  return (int16_t)proximity.read();
}

/**************************************************************************/
/*!
    @brief Reads the ambient light sensor register.
    @return The current ambient light measurement in units
*/
/**************************************************************************/
uint16_t Adafruit_VCNL4040::readAmbientLight(void) {
  Adafruit_BusIO_Register ambient_light =
    Adafruit_BusIO_Register(i2c_dev, VCNL4040_ALS_DATA, 2);
  delay(10);
  return (int16_t)ambient_light.read();
}
/**************************************************************************/
/*!
    @brief Reads the white sensor register.
    @return The current white light measurement in units
*/
/**************************************************************************/
uint16_t Adafruit_VCNL4040::readWhite(void) {
  Adafruit_BusIO_Register white_light =
    Adafruit_BusIO_Register(i2c_dev, VCNL4040_WHITE_DATA, 2);
  delay(10);
  return (int16_t)white_light.read();
}