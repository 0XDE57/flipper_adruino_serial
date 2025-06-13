#include <SoftwareSerial.h>

int baudRate = 9600;

SoftwareSerial softSerial(6, 7);

void setup() {
  Serial.begin(baudRate);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  softSerial.begin(baudRate);
}

void loop() {
  if (softSerial.available()) {
    Serial.write(softSerial.read());
  }
}
