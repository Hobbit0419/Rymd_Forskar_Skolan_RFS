/* ADXL345 accelerometer enkel test-sketch.

Mäter accelerationen i tre dimensioner. Behöver kalibreras mot
känd källa om absoluta värden ska användas (som alla liknande sensorer)

Koppla enligt följande tabell:

------------------------------
Pin på sensor | Pin på Arduino
--------------|---------------
GND           | GND
VCC           | VCC
SDA           | SDA
SCL           | SCL
------------------------------

Koden nedan kräver följande bibliotek:
  - Adafruit Unified Sensor
  - Adafruit ADXL345
  - Adafruit BusIO

För mer information, se https://learn.adafruit.com/adxl345-digital-accelerometer. */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// Tilldela ett unikt ID till sensorn
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup(void) 
{

  Serial.begin(9600);
  Serial.println("Accelerometer Test"); Serial.println("");
  
  // Initiera sensorn 
  if(!accel.begin())
  {
    Serial.println("Ingen ADXL345 kunde detekteras... Kontrollera dina kopplingar!");
    while(1);
  }

  // Sätt maxvärde till vad du tror passar projektet
  //accel.setRange(ADXL345_RANGE_16_G);
  // accel.setRange(ADXL345_RANGE_8_G);
  // accel.setRange(ADXL345_RANGE_4_G);
   accel.setRange(ADXL345_RANGE_2_G);
  Serial.println("");
}

void loop(void) 
{
  // Skapa en ny sensorhändelse
  sensors_event_t event; 
  accel.getEvent(&event);
 
  // Visa resultaten (acceleration mäts i m/s^2)
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  delay(300);
}
