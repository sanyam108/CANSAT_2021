#include "CANSAT.h"
// pins occupied - 

Adafruit_BMP280 bmp = Adafruit_BMP280(); 

float temp,pressure,altitude;

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
float rpmX,rpmY,rpmZ;

String tel = "";
char str[100];

void setup() {
  Serial.begin(9600);
  setupbmp();
  setupMPU();

  payload_tel();
}

void loop() {
  bmploop();
  mpuloop();
  delay(1000);
}

void payload_tel(){

  dtostrf(altitude,4,1,str);
  tel += str;
  tel += ',';

  dtostrf(temp,4,1,str);
  tel += str;
  tel += ',';

  dtostrf(rpmX,3,0,str);
  tel += str;
  tel += ',';

  dtostrf(rpmY,3,0,str);
  tel += str;
  tel += ',';

  dtostrf(rpmZ,3,0,str);
  tel += str;
  tel += ',';

  Serial.println(tel);

}
