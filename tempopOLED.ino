#include <Wire.h>
#include <SeeedOLED.h>

// Example testing sketch for various DHT humidity/temperature sensors
// Written by Emilie, public domain
// Also written by Grove

#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);

float h = 0;
float t = 0;
float maxReading = 0;
float minReading = 100;


void setup()
{ 

  Serial.begin(9600); 
  Serial.println("DHTxx test!");    
  
  Wire.begin();
  SeeedOled.init();  //initialze SEEED OLED display
  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();           //Set addressing mode to Page Mode
  SeeedOled.setTextXY(0, 0);         //Set the cursor to Xth Page, Yth Column


    /*if using WIO link,must pull up the power pin.*/
    // pinMode(PIN_GROVE_POWER, OUTPUT);
    // digitalWrite(PIN_GROVE_POWER, 1);

  dht.begin();
}

void loop()
{  
    temp();
    
    minmax();

    delay(5000);
  
    schoon();

    printmm();

    delay(5000);

    schoon();

}

int temp(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  
  SeeedOled.putString("Temperatuur =");
  SeeedOled.setTextXY(5, 0);
  SeeedOled.putString("Humidity = ");
  SeeedOled.setTextXY(2, 0); 
  SeeedOled.putFloat(t);
  SeeedOled.putString(" *C");
  SeeedOled.setTextXY(7, 0);
  SeeedOled.putFloat(h);
  SeeedOled.putString(" %");

}


int minmax() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (t > maxReading) {
      maxReading = t;
  }

  if (minReading > t) {
      minReading = t;
  }

  Serial.print(maxReading);         
  Serial.print('\t'); 
  Serial.print(minReading);         
  }


int schoon(){
  
  SeeedOled.clearDisplay();
  
  /* SeeedOled.setTextXY(2, 0);
  SeeedOled.putString("                                            ");
  SeeedOled.setTextXY(7, 0);
  SeeedOled.putString("                                            ");
  */
}

int printmm() {
  SeeedOled.setTextXY(0, 0);
  SeeedOled.putString("MAX:");
  SeeedOled.setTextXY(2, 0);
  SeeedOled.putFloat(maxReading);
  SeeedOled.setTextXY(5, 0);
  SeeedOled.putString("MIN:");
  SeeedOled.setTextXY(7, 0);
  SeeedOled.putFloat(minReading);
  
}
 
