#include <SPI.h>
#include <SD.h>

// Chip select pin for the SD card reader
const int chipSelect = SDCARD_SS_PIN;

// Interval between data logging (in milliseconds)
const unsigned long loggingInterval = 1000;
unsigned long previousMillis = 0;

void setup() {
  // Starta serial com
  Serial.begin(9600);

  Serial.print("Initializing SD card");

  // Öppnar sd-kortet
  if (!SD.begin(chipSelect)); {
    Serial.println("Card failed, or not present");
    while (1);
  }
  
  Serial.println("card initialized.");

  // Skapar en fil
  File dataFile = SD.open("datalog.csv", FILE_WRITE);

  // Om det gick att starta sd kortet skriver vi headern
  if (dataFile) {
    dataFile.println("Timestamp,accx,accy,accz");
    dataFile.close();
    Serial.println("CSV file created with header.");
  } else {
    // If the file didn't open, print an error:
    Serial.println("error opening datalog.csv");
  }

  if(!accel.begin())
  {
    Serial.println("Ingen ADXL345 kunde detekteras... Kontrollera dina kopplingar!");
    while(1);
  }

  accel.setRange(ADXL345_RANGE_2_G);

  
}

void loop() {
  // Check if it's time to log data
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= loggingInterval) {
    previousMillis = currentMillis;

    sensors_event_t event; 
    accel.getEvent(&event);

    // Simulate sensor data
    float accx = event.acceleration.x;
    float accy = event.acceleration.y;
    float accz = event.acceleration.z;
    // Create a timestamp
    String timestamp = String(currentMillis);

    // Open the file. Note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.csv", FILE_WRITE);

    // If the file is available, write to it:
    if (dataFile) {
      dataFile.print(timestamp);
      dataFile.print(",");
      dataFile.print(accx);
      dataFile.print(",");
      dataFile.print(accy);
      dataFile.print(",");
      dataFile.println(accz);
      dataFile.close();

      // Print to the serial port too:
      Serial.print("Logged: ");
      Serial.print(timestamp);
      Serial.print(",");
      Serial.print(accx);
      Serial.print(",");
      Serial.print(accy);
      Serial.print(",");
      Serial.println(accz);
    } else {
      // If the file didn't open, print an error:
      Serial.println("error opening datalog.csv");
    }
  }
}
