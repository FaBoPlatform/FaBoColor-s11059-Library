/**
 * @file  fabo-s11059.cpp
 * @brief fabo libtary of S11059
 * @author Akira Sasaki
 * @date 2,10, 2016
 */
#include "fabo-s11059.h"

/**
 * @brief Set Config
 */
void FaBoColor::configuration()
{
  byte conf = S11059_CTRL_RESET_OFF;
  conf |= S11059_CTRL_SLEEP_OFF;
  conf |= S11059_CTRL_HIGH_GAIN;
  conf |= S11059_CTRL_INT_CONTINUOS;
  conf |= S11059_CTRL_INT_IME_87_5US;
  writeI2c(S11059_CTRL_REG, conf);
}

/**
 * @brief Read Color Value
 * @param [out] *r  : red value
 * @param [out] *g  : green value
 * @param [out] *b  : blue value
 * @param [out] *i  : IR value
 */
void FaBoColor::readRGBI(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *i)
{
  uint8_t length = 8;
  byte color_buff[8];
  readI2c(S11059_RED_REG, length, color_buff);
  *r = (((int)color_buff[0]) << 8) | color_buff[1];
  *g = (((int)color_buff[2]) << 8) | color_buff[3];
  *b = (((int)color_buff[4]) << 8) | color_buff[5];
  *i = (((int)color_buff[6]) << 8) | color_buff[7];
}

/**
 * @brief Write I2C Data
 * @param [in] address : Write Register Address
 * @param [in] data    : Write Data
 */
void FaBoColor::writeI2c(byte register_addr, byte value) {
  Wire.begin();
  Wire.beginTransmission(S11059_SLAVE_ADDRESS);
  Wire.write(register_addr);
  Wire.write(value);
  Wire.endTransmission();
}

/**
 * @brief Read I2C Data
 * @param [in] register_addr : register address
 * @param [in] num       : Data Length
 * @param [out] buffer[] : Read Data
 */
void FaBoColor::readI2c(byte register_addr, int num, byte buffer[]) {
  Wire.begin();
  Wire.beginTransmission(S11059_SLAVE_ADDRESS);
  Wire.write(register_addr);
  Wire.endTransmission();

  Wire.beginTransmission(S11059_SLAVE_ADDRESS);
  Wire.requestFrom(S11059_SLAVE_ADDRESS, num);

  int i = 0;
  while(Wire.available())
  {
    buffer[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();
}
