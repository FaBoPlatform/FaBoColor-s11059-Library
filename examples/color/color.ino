#include "fabo-s11059.h"
#include "Wire.h"

FaBoColor faboColor;

void setup() {
  Serial.begin(9600); // シリアルの開始デバック用
  faboColor.configuration();
}

void loop() {

  uint16_t r;
  uint16_t g;
  uint16_t b;
  uint16_t i;

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
