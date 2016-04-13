/**
 * @file  fabo-s11059.h
 * @brief fabo libtary of S11059
 * @author Akira Sasaki
 * @date 2,10, 2016
 */
#include "Arduino.h"
#include "Wire.h"

/** SLAVE_ADDRESS Register */
#define S11059_SLAVE_ADDRESS 0x2A

/** Control Register */
#define S11059_CTRL_REG 0x00
/** Manual timing Register */
#define S11059_MANUAL_TIMING_REG 0x01
/** Red Color Register */
#define S11059_RED_REG 0x03
/** Green Color Register */
#define S11059_GREEN_REG 0x05
/** Blue Color Register */
#define S11059_BLUE_REG 0x07
/** IR Register */
#define S11059_IR_REG 0x09

/** Control Reset ON */
#define S11059_CTRL_RESET_ON 0b10000000
/** Control Reset OFF */
#define S11059_CTRL_RESET_OFF 0b00000000
/** Control SLEEP ON */
#define S11059_CTRL_SLEEP_ON 0b01000000
/** Control SLEEP OFF */
#define S11059_CTRL_SLEEP_OFF 0b00000000
/** Control GAIN HIGH */
#define S11059_CTRL_HIGH_GAIN 0b00001000
/** Control GAIN LOW */
#define S11059_CTRL_LOW_GAIN 0b00000000
/** Control INT Manual */
#define S11059_CTRL_INT_MANUAL 0b00000100
/** Control INT Continous */
#define S11059_CTRL_INT_CONTINUOS 0b00000000
/** Control INT IME 87.5us */
#define S11059_CTRL_INT_IME_87_5US 0b00
/** Control INT IME 1.4us */
#define S11059_CTRL_INT_IME_1_4MS 0b01
/** Control INT IME 22.4us */
#define S11059_CTRL_INT_IME_22_4MS 0b10
/** Control INT IME 179.2us */
#define S11059_CTRL_INT_IME_179_2MS 0b11

/**
 * @brief S11059 Control
 */
class FaBoColor
{
public:
	void configuration(void);
	void readRGBI(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *i);
private:
	void writeI2c(byte register_addr, byte value);
	void readI2c(byte register_addr, int num, byte *buf);
};
