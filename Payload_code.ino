#include "CANSAT.h"
// pins occupied - 

Adafruit_BMP280 bmp = Adafruit_BMP280(); 

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
float rpmX,rpmY,rpmZ;


void setup() {
  Serial.begin(9600);
  setupbmp();
  setupMPU();
}

void loop() {
  bmploop();
  mpuloop();
  delay(1000);

}
