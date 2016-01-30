#include "fabo-s11059.h"
#include "Wire.h"

unsigned int r;
unsigned int g;
unsigned int b;
unsigned int i;

void setup() {
  Serial.begin(9600); // シリアルの開始デバック用
  faboColor.configuration();
}

void loop() {
  
  faboColor.readRGBI(&r, &g, &b, &i);
  
  Serial.print("r: ");
  Serial.print(r);
  Serial.print(", g: ");
  Serial.print(g);
  Serial.print(", b: ");
  Serial.print(b);
  Serial.print(", i: ");
  Serial.println(i);
  
  delay(500);
}
