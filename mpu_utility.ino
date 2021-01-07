void setupMPU(){
  Wire.begin();                      
  Wire.beginTransmission(MPU);      
  Wire.write(0x6B);                  
  Wire.write(0x00);                  
  Wire.endTransmission(true);        
  
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);                  
  Wire.write(0x10);                  
  Wire.endTransmission(true);
  
//  calculate_IMU_error();
  delay(20);
  
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission(); 
}
//
//void recordAccelRegisters() {
//  Wire.beginTransmission(0b1101000); //I2C address of the MPU
//  Wire.write(0x3B); //Starting register for Accel Readings
//  Wire.endTransmission();
//  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
//  while(Wire.available() < 6);
//  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
//  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
//  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
//  processAccelData();
//}
//
//void processAccelData(){
//  gForceX = accelX / 16384.0;
//  gForceY = accelY / 16384.0; 
//  gForceZ = accelZ / 16384.0;
//}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rpmX=rotX/6;
  rotY = gyroY / 131.0; 
  rpmY=rotY/6;
  rotZ = gyroZ / 131.0;
  rpmZ=rotZ/6;
}

void RPMMeasurement() {
  Serial.print("Gyro (RPM)");
  Serial.print(" X=");
  Serial.print(rpmX);
  Serial.print(" Y=");
  Serial.print(rpmY);
  Serial.print(" Z=");
  Serial.print(rpmZ);
}

void mpuloop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); 
  
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; 
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; 
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; 
  
  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; 
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58; 

  recordGyroRegisters();
  RPMMeasurement();
}
