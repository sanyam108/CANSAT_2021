void BMPREAD(){
  get_temp();
  get_altitude();
  float pressure = read_pressure();
}
void bmp280_setup(){
  Serial.println(F("BMP280 setup"));

  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
//    buzz(); /*A buzzer indicates that sensor is not working*/
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

//void buzz(){
//    const int buzzer = 8;
//    pinMode(buzzer, OUTPUT);
//    while (1){
//      tone(buzzer, 1000); // Send 1KHz sound signal...
//      delay(1000);        // ...for 1 sec
//      noTone(buzzer);     // Stop sound...
//      delay(1000);        // ...for 1sec
//    }
//}

float get_temp(){
  Serial.print(F("Temperature = ")); Serial.print(bmp.readTemperature(),1); Serial.println(" *C");
  return bmp.readTemperature();
}

float read_pressure(){
  return bmp.readPressure();
}

float get_altitude(){
  Serial.print(F("Approx altitude = ")); Serial.print(bmp.readAltitude(1013.25),1); Serial.println(" m");
  return bmp.readAltitude(1013.25); 
}
