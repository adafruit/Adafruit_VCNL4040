#include <Adafruit_VCNL4040.h>

Adafruit_VCNL4040 vcnl4040 = Adafruit_VCNL4040();

void setup() {
  Serial.begin(115200);
  // Wait until serial port is opened
  while (!Serial) { delay(1); }

  Serial.println("Adafruit VCNL4040 Test");

  if (!vcnl4040.begin()) {
    Serial.println("Couldn't find VCNL4040 chip");
    while (1);
  }
  Serial.println("Found VCNL4040 chip");
}

void loop() {
  Serial.print("Proximity:"); Serial.println(vcnl4040.getProximity());
  Serial.print("Ambient light:"); Serial.println(vcnl4040.getAmbientLight());
  Serial.print("White light:"); Serial.println(vcnl4040.getWhiteLight());
  delay(500);
}