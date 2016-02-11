#include "fabo-s11059.h"

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

void FaBoColor::configuration()
{
  byte conf = S11059_CTRL_RESET_OFF;
  conf |= S11059_CTRL_SLEEP_OFF;
  conf |= S11059_CTRL_HIGH_GAIN;
  conf |= S11059_CTRL_INT_CONTINUOS;
  conf |= S11059_CTRL_INT_IME_87_6US;
  writeI2c(S11059_CTRL_REG, conf);
}

// I2Cへの書き込み
void FaBoColor::writeI2c(byte register_addr, byte value) {
  Wire.begin();       // I2Cの開始
  Wire.beginTransmission(S11059_SLAVE_ADDRESS);  
  Wire.write(register_addr);         
  Wire.write(value);                 
  Wire.endTransmission();        
}

// I2Cへの読み込み
void FaBoColor::readI2c(byte register_addr, int num, byte buffer[]) {
  Wire.begin();       // I2Cの開始
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
