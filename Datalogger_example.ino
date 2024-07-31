#include <SPI.h>
#include <SD.h>

// Chip select pin for the SD card reader
const int chipSelect = SDCARD_SS_PIN;

// Interval between data logging (in milliseconds)
const unsigned long loggingInterval = 1000;
unsigned long previousMillis = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
 
  }

  Serial.print("Initializing SD card");

  // Check if the card is present and can be initialized:
  if (!SD.begin(chipSelect)); {
    Serial.println("Card failed, or not present");
    // Don't do anything more:
    while (1);
  }
  
  Serial.println("card initialized.");

  // Create or open the file. Note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.csv", FILE_WRITE);

  // If the file opened okay, write the header:
  if (dataFile) {
    dataFile.println("Timestamp,Temperature,Humidity");
    dataFile.close();
    Serial.println("CSV file created with header.");
  } else {
    // If the file didn't open, print an error:
    Serial.println("error opening datalog.csv");
  }
}

void loop() {
  // Check if it's time to log data
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= loggingInterval) {
    previousMillis = currentMillis;

    // Simulate sensor data
    float temperature = random(20, 30) + random(0, 100) / 100.0;
    float humidity = random(30, 50) + random(0, 100) / 100.0;

    // Create a timestamp
    String timestamp = String(currentMillis);

    // Open the file. Note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.csv", FILE_WRITE);

    // If the file is available, write to it:
    if (dataFile) {
      dataFile.print(timestamp);
      dataFile.print(",");
      dataFile.print(temperature);
      dataFile.print(",");
      dataFile.println(humidity);
      dataFile.close();

      // Print to the serial port too:
      Serial.print("Logged: ");
      Serial.print(timestamp);
      Serial.print(", ");
      Serial.print(temperature);
      Serial.print(", ");
      Serial.println(humidity);
    } else {
      // If the file didn't open, print an error:
      Serial.println("error opening datalog.csv");
    }
  }
}
