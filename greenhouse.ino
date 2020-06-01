

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"
#include "SevSeg.h" // Required for Segments
#include <SPI.h>
#include <Ethernet.h>

#define DHTPIN 22     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:dh
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 128, 56);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

int finalNb = 1111;
SevSeg sevseg; //Initiate a seven segment controller object

void setup() {
  Serial.begin(9600);

  // Segments setup
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5}; 
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
  
  // DHT
  dht.begin();

}

void loop() {
    
  /*sevseg.setNumber(finalNb, 2);
  sevseg.refreshDisplay(); // Must run repeatedly
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  Serial.print( "T = " );
  Serial.print( t, 1 );
  Serial.print( " deg. C, H = " );
  Serial.print( h, 1 );
  Serial.println( "%" );*/

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
 
  /*int dispTemp = (int) t;
  int dispHumidity = (int) h;
  finalNb = dispTemp;
  finalNb *= 100;
  finalNb += dispHumidity;
  Serial.print(" Final = ");
  Serial.print(finalNb, 1);
  */
}
