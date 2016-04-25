/**
 @file color.ino
 @brief This is an Example for the FaBo Color I2C Brick.

   http://fabo.io/203.html

   Released under APACHE LICENSE, VERSION 2.0

   http://www.apache.org/licenses/

 @author FaBo<info@fabo.io>
*/

#include <Wire.h>
#include <FaBoColor_S11059.h>

FaBoColor faboColor;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("RESET");
  faboColor.begin();
}

void loop() {
  uint16_t r,g,b,i;

  faboColor.readRGBI(&r, &g, &b, &i);

  Serial.print("r: ");
  Serial.print(r);
  Serial.print(", g: ");
  Serial.print(g);
  Serial.print(", b: ");
  Serial.print(b);
  Serial.print(", i: ");
  Serial.println(i);

  delay(1000);
}
