#include "Arduino.h"
#include "Wire.h"

#define S11059_SLAVE_ADDRESS 0x2A

// Resgiter map
#define S11059_CTRL_REG 0x00
#define S11059_MANUAL_TIMING_REG 0x01
#define S11059_RED_REG 0x03
#define S11059_GREEN_REG 0x05
#define S11059_BLUE_REG 0x07
#define S11059_IR_REG 0x09

#define S11059_CTRL_RESET_ON 0b10000000
#define S11059_CTRL_RESET_OFF 0b00000000
#define S11059_CTRL_SLEEP_ON 0b01000000
#define S11059_CTRL_SLEEP_OFF 0b00000000
#define S11059_CTRL_HIGH_GAIN 0b00001000
#define S11059_CTRL_LOW_GAIN 0b00000000
#define S11059_CTRL_INT_MANUAL 0b00000100
#define S11059_CTRL_INT_CONTINUOS 0b00000000
#define S11059_CTRL_INT_IME_87_6US 0b00
#define S11059_CTRL_INT_IME_1_4MS 0b01
#define S11059_CTRL_INT_IME_22_4MS 0b10
#define S11059_CTRL_INT_IME_179_2MS 0b11

class FaBoColor
{
public:
	void configuration(void);
	void readRGBI(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *i);
private:
	void readI2c(byte register_addr, int num, byte *buf);
	void writeI2c(byte register_addr, byte value);
};
