/**
 @file FaBoColor_S11059.cpp
 @brief This is a library for the FaBo Color I2C Brick.

   http://fabo.io/203.html

   Released under APACHE LICENSE, VERSION 2.0

   http://www.apache.org/licenses/

 @author FaBo<info@fabo.io>
*/

#include "FaBoColor_S11059.h"

/**
 @brief Constructor
*/
FaBoColor::FaBoColor(uint8_t addr) {
  _i2caddr = addr;
  Wire.begin();
}

/**
 @brief Begin Device
*/
void FaBoColor::begin() {
  setGain(S11059_GAIN_LOW);
  setMode(S11059_MODE_FIXED);
  setTime(S11059_CTRL_TIME_1792M);
}

/**
 @brief Set Gain
 @param [in] gain Gain
*/
void FaBoColor::setGain(uint8_t gain) {
  uint8_t data;
  data = getConfig();
  if ( gain == S11059_GAIN_HIGH ) {
    data |= S11059_CTRL_GAIN;
  } else {
    data &= ~(S11059_CTRL_GAIN);
  }
  writeI2c(S11059_CONTROL, data);
}

/**
 @brief Set Mode
 @param [in] mode Mode
*/
void FaBoColor::setMode(uint8_t mode) {
  _mode = mode;
  uint8_t data;
  data = getConfig();
  if ( mode == S11059_MODE_MANUAL ) {
    data |= S11059_CTRL_MODE;
  } else {
    data &= ~(S11059_CTRL_MODE);
  }
  writeI2c(S11059_CONTROL, data);
}

/**
 @brief Set Time
 @param [in] itime Time
*/
void FaBoColor::setTime(uint8_t itime) {
  _itime = itime;
  uint8_t data;
  data = getConfig();
  data &= 0xFC;
  data |= itime;
  writeI2c(S11059_CONTROL, data);
}

/**
 @brief Start Measurement
*/
void FaBoColor::start() {
  uint8_t data;
  data = getConfig();
  data &= 0x3F; // RESET off,SLEEP off
  writeI2c(S11059_CONTROL, data);
}

/**
 @brief Restart Measurement
*/
void FaBoColor::restart() {
  uint8_t data;
  data = getConfig();
  data |= 0x80; // RESET on,SLEEP off
  data &= 0xBF;
  writeI2c(S11059_CONTROL, data);
  delay(1);
  data = getConfig();
  data &= 0x3F; // RESET off,SLEEP off
  writeI2c(S11059_CONTROL, data);
}

/**
 @brief Set Manual Timing
 @param [in] timing timing
*/
void FaBoColor::setManualTiming(uint16_t timing) {
  uint8_t data[2] = {
    (uint8_t)((timing >> 8) & 0xFF),
    (uint8_t)(timing & 0xFF)
  };
  Wire.beginTransmission(_i2caddr);
  Wire.write(S11059_TIMING_H);
  Wire.write(data, sizeof(data));
  Wire.endTransmission();
}

/**
 @brief Get Manual Timing
 @param [out] timing timing
*/
uint16_t FaBoColor::getManualTiming() {
  uint8_t data[2];
  readI2c(S11059_TIMING_H, 2, data);
  return (((uint16_t)data[0]) << 8) | data[1];
}

/**
 @brief Get Config
 @param [out] config contorl bits
*/
uint8_t FaBoColor::getConfig() {
  uint8_t data;
  readI2c(S11059_CONTROL, 1, &data);
  return data;
}

/**
 @brief Sleep check
 @retval true device sleep
 @retval false device running
*/
bool FaBoColor::checkSleep() {
  uint8_t data;
  readI2c(S11059_CONTROL, 1, &data);
  return data & 0x20;
}

/**
 @brief Wait device sleep
*/
void FaBoColor::waitAdc() {
  while( ! checkSleep() ){
    delayMicroseconds(1);
  }
  delay(1);
}

/**
 @brief Read Measurement data
 @param [out] r red
 @param [out] g green
 @param [out] b blue
 @param [out] i IR
*/
void FaBoColor::readRGBI(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *i) {
  uint8_t data[8];

  if ( _mode == S11059_MODE_MANUAL ) {
    restart(); // wake from sleep
    waitAdc(); // wait measure
  } else {
    switch( _itime ) {
      case S11059_CTRL_TIME_875U: // delay 88usec
        delayMicroseconds(88 * 4);
        delay(1); // wait buffer
        break;
      case S11059_CTRL_TIME_14M: // delay 1.4msec
        delay(2 * 4);
        delay(1); // wait buffer
        break;
      case S11059_CTRL_TIME_224M: // delay 22.4msec
        delay(23 * 4);
        delay(1); // wait buffer
        break;
      case S11059_CTRL_TIME_1792M: // delay 179.2msec
        delay(180 * 4);
        delay(1); // wait buffer
        break;
    }
  }
  readI2c(S11059_DATA_RED_H, 8, data);
  *r = (((uint16_t)data[0]) << 8) | data[1];
  *g = (((uint16_t)data[2]) << 8) | data[3];
  *b = (((uint16_t)data[4]) << 8) | data[5];
  *i = (((uint16_t)data[6]) << 8) | data[7];
}



/**
 @brief Write I2C
 @param [in] address register address
 @param [in] data write data
*/
void FaBoColor::writeI2c(uint8_t address, uint8_t data) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

/**
 @brief Read I2C
 @param [in] address register address
 @param [in] num read length
 @param [out] data read data
*/
void FaBoColor::readI2c(uint8_t address, uint8_t num, uint8_t * data) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.endTransmission();
  uint8_t i = 0;
  Wire.requestFrom(_i2caddr, num);
  while( Wire.available() ) {
    data[i++] = Wire.read();
  }
}
