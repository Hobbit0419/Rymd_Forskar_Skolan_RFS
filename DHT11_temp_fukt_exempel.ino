/* DHT11 temperatur- och luftfuktighetssensor enkel test-sketch.

Behöver kalibreras mot känd källa om absoluta värden ska användas (som alla liknande sensorer)

Koppla enligt följande tabell:

------------------------------
Pin på sensor | Pin på Arduino
(vänster till |
höger)        |
--------------|---------------
1             | VCC
2             | Valfri pin, ex. 6
3             | ingen
4             | GND
------------------------------

Koden nedan kräver följande bibliotek:
  - DHT sensor library

För mer information, se https://learn.adafruit.com/dht. */

#include <DHT.h>
#define DHTTYPE DHT11

// Bestäm vilken pin vi har data-sensorn
// inkopplad på
#define DHTPIN 6

// Vi initierar ett objekt av typen DHT 
// som vi kallar "dht". Detta är vad vi använder
// för att läsa av sensorn
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  // starta DHT 
  dht.begin();
}


void loop() {
  // Vänta ett par sekunder mellan avläsningar
  delay(500);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Kolla ifall någonting misslyckats och avbryt (för att försöka igen).
  // (NaN betyder "not a number".)
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Skriv ut luftfuktighet och temperatur i
  // Serial-monitorn
  Serial.print(humidity);
  Serial.print(",");
  Serial.println(temperature);

}
