struct gps_{
  int sats = 0;
  char longit[10] = "NONE";
  char latit[10] = "NONE";
  char longd = '0';
  char lattd = '0';
  char alt[7] = "NONE";
  struct gps_time{
    char hh[3] = "xx";
    char mm[3] = "xx";
    char ss[3] = "xx";
  }tt;
}gps;

uint32_t timer = millis();
uint32_t timer2 = millis();

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO  false

void setupgps()
{ 
  delay(500);
  Serial.println("Inside gps setup!");

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(100);
  mySerial.println(PMTK_Q_RELEASE);
}

void gpsloop()                     // run over and over again
{
  // fetch data continuosly
  GPS.read();
}

void gpsdata()
{
    // if a sentence is received, we can check the checksum, parse it...
    if (GPS.newNMEAreceived()) {
      if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
        return;  // we can fail to parse a sentence in which case we should just wait for another
    }

    // update after 1s of previous update
     if (millis() - timer > 1000 && GPS.fix==1)
     {
      timer = millis();
      gps.sats = (int)GPS.satellites;
      dtostrf(GPS.altitude, 5, 1, gps.alt);
      dtostrf(GPS.longitudeDegrees, 6, 4, gps.longit);
      dtostrf(GPS.latitudeDegrees, 6, 4, gps.latit);
      gps.longd = (char)GPS.lon;
      gps.lattd = (char)GPS.lat;
      
      dtostrf(GPS.hour, 2, 0, gps.tt.hh);
      dtostrf(GPS.minute, 2, 0, gps.tt.mm);
      dtostrf(GPS.seconds, 2, 0, gps.tt.ss);
  }
}


void gpsprint()
{
   // print after 1s
   if(millis()-timer2>1000)
  {
    timer2 = millis();
    Serial.print("Time: ");
    Serial.print(gps.tt.hh[1]);
    Serial.print(':');
    Serial.print(gps.tt.mm);
    Serial.print(':');
    Serial.println(gps.tt.ss);

    Serial.print("Longitude: ");
    Serial.print(gps.longit);
    Serial.println(gps.longd);

    Serial.print("Latitude: ");
    Serial.print(gps.latit);
    Serial.println(gps.lattd);

    Serial.print("Altitude: ");
    Serial.println(gps.alt);

    Serial.print("Sats: ");
    Serial.println(gps.sats);
    Serial.print("\n");
  }
}
