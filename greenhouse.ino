#include "SevSeg.h"

#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 128, 56);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

static const int DHT_SENSOR_PIN = 52;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
int finalNb = 1111;

SevSeg sevseg; //Initiate a seven segment controller object

void setup() {

  byte numDigits = 4;
  
  byte digitPins[] = {2, 3, 4, 5};
  
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  
  sevseg.setBrightness(90);

  Serial.begin(9600);
}

/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}

void loop() {
  delay(2000);
  //sevseg.setNumber(finalNb, 2);
  //sevseg.refreshDisplay(); // Must run repeatedly

  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  //if( measure_environment( &temperature, &humidity ) == true )
  //{
    dht_sensor.measure( &temperature, &humidity );
    Serial.print( "T = " );
    Serial.print( temperature, 1 );
    Serial.print( " deg. C, H = " );
    Serial.print( humidity, 1 );
 

    int dispTemp = (int) temperature;
    int dispHumidity = (int) humidity;
    finalNb = dispTemp;
    finalNb *= 100;
    finalNb += dispHumidity;
    Serial.print(" Final = ");
    Serial.print(finalNb, 1);
    Serial.println( "%" );
  //}
}
