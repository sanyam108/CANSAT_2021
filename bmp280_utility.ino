void setupbmp(){
  float alt,gnd_alt;

  bmp.begin(0x76); // Default initialisation with I2C address (0x76) 
  
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  gnd_alt = bmp.readAltitude(1013.25);
  Serial.print("Ground altitude is: ");
  Serial.println(gnd_alt);
}

void bmploop(){
  get_temp();
  get_altitude();
  read_pressure();
  altitude = alt - gnd_alt;
}

void get_temp(){
  temp = bmp.readTemperature();
  Serial.print(F("Temperature = ")); 
  Serial.print(temp,1); 
  Serial.println(" *C");
}

void read_pressure(){
  pressure = bmp.readPressure();
}

void get_altitude(){
  alt = bmp.readAltitude(1013.25);
  Serial.print(F("Approx altitude = ")); 
  Serial.print(bmp.readAltitude(1013.25),1); 
  Serial.println(" m");
}
