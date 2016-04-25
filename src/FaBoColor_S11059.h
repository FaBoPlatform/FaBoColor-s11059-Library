/**
 @file FaBoColor_S11059.h
 @brief This is a library for the FaBo Color I2C Brick.

   http://fabo.io/203.html

   Released under APACHE LICENSE, VERSION 2.0

   http://www.apache.org/licenses/

 @author FaBo<info@fabo.io>
*/

#ifndef FABOCOLOR_S11059_H
#define FABOCOLOR_S11059_H

#include <Arduino.h>
#include <Wire.h>

#define S11059_SLAVE_ADDRESS 0x2A ///< S11059 I2C slave address

/// @name S11059 Register Addresses
/// @{
#define S11059_CONTROL 0x00
#define S11059_TIMING_H 0x01
#define S11059_TIMING_L 0x02
#define S11059_DATA_RED_H 0x03
#define S11059_DATA_RED_L 0x04
#define S11059_DATA_GREEN_H 0x05
#define S11059_DATA_GREEN_L 0x06
#define S11059_DATA_BLUE_H 0x07
#define S11059_DATA_BLUE_L 0x08
#define S11059_DATA_IR_H 0x09
#define S11059_DATA_IR_L 0x0A
/// @}

/// @name S11059 Control bits
/// @{
#define S11059_CTRL_RESET 0x80
#define S11059_CTRL_SLEEP 0x40
#define S11059_CTRL_GAIN  0x08
#define S11059_CTRL_MODE  0x04
/// @}

/// @name S11059 Measurement time select
/// @{
#define S11059_CTRL_TIME_875U 0x0
#define S11059_CTRL_TIME_14M 0x1
#define S11059_CTRL_TIME_224M 0x2
#define S11059_CTRL_TIME_1792M 0x3
/// @}

/// @name S11059 Gain select
/// @{
#define S11059_GAIN_HIGH 1
#define S11059_GAIN_LOW  0
/// @}

/// @name S11059 Mode select
/// @{
#define S11059_MODE_MANUAL 1
#define S11059_MODE_FIXED  0
/// @}


/**
 * @class FaBoColor
 * @brief FaBo Color I2C Controll class
 */
class FaBoColor {
  public:
    FaBoColor(uint8_t addr = S11059_SLAVE_ADDRESS);
    void begin(void);
    void setGain(uint8_t gain);
    void setMode(uint8_t mode);
    void setTime(uint8_t itime);
    void start(void);
    void restart(void);
    void setManualTiming(uint16_t timing);
    uint16_t getManualTiming(void);
    uint8_t getConfig(void);
    bool checkSleep(void);
    void waitAdc(void);
    void readRGBI(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *i);
  private:
    uint8_t _i2caddr;
    uint8_t _mode;
    uint8_t _itime;
    void writeI2c(uint8_t address, uint8_t data);
    void readI2c(uint8_t address, uint8_t num, uint8_t * data);
};

#endif // FABOCOLOR_S11059_H
