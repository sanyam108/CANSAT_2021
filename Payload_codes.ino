#include "CANSAT.h"
// pins occupied - 

Adafruit_BMP280 bmp = Adafruit_BMP280(); 
SoftwareSerial mySerial(8, 7);
Adafruit_GPS GPS(&mySerial);

const int MPU = 0x68; 
float AccX, AccY, AccZ;

float accAngleX, accAngleY;
float AccErrorX, AccErrorY;
float elapsedTime, currentTime, previousTime;


long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
float rpmX,rpmY,rpmZ;


void setup() {
  Serial.begin(115200);
  
  bmp280_setup();
  setupgps();
  setupMPU();
}

void loop() {
  BMPREAD();
  gpsloop();
  gpsdata();
  gpsprint();
  mpuloop();
  delay(100);

}
