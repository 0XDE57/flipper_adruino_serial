
//9600 works. other rates no worky :(
//Flipper Log Baud Rate: [9600, 38400, 57600, 115200, 230400, 460800, 9261600]
int baudRate = 9600;

void setup() {
  Serial.begin(baudRate);  //RX0 = 0,  TX0 = 1  -> USB -> PuTTY
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  Serial1.begin(baudRate);  //TX1 = 19, RX1 = 18 -> Flipper: TX = 13, RX = 14
}

void loop() {
  //forward serial
  if (Serial1.available()) {
    Serial.write(Serial1.read());
  }
}