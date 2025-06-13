# Flipper Adruino Serial (UART) Forward

Read Flipper Zero logs via UART using an Arduino. 

The Flipper docs provide a way to do it with the Wi-Fi Developer Board:
https://developer.flipper.net/flipperzero/doxygen/dev_board_reading_logs.html
>The Developer Board allows you to read Flipper Zero logs via UART. Unlike reading logs via the command-line interface (CLI), the Developer Board enables you to collect logs from the device directly to a serial console independently from the operating system of Flipper Zero. It allows you to see the device's logs when it's loading, updating, or crashing. It's useful for debugging and troubleshooting during software development.

See Flipper docs for pin outs: https://docs.flipper.net/gpio-and-modules

See Arduino Boards for supported serial ports: https://docs.arduino.cc/language-reference/en/functions/communication/serial/


## Flipper -> Arduino -> PuTTY

The arduino is simply forwarding UART messages from input RX and TX pins, and writing them to serial USB.

Flipper Log Baud Rates: `9600, 38400, 57600, 115200, 230400, 460800, 9261600`

Currently only working at **9600**. Unknown why 38400+ doesn't work... *todo*

**NOTE:** Adruino IDE > Tools > Serial Monitor will see messages from flipper, but does not understand color tokens so the output will look funny. Recommend use putty instead.

UNO
-
Arduino Uno only has one serial port, so we use SoftwareSerial instead: https://arduinogetstarted.com/tutorials/arduino-softwareserial

Flipper: `TX = 13, RX = 14`

Auduino UNO: `RX = 6,  TX = 7`

```ino
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

```

DUE
-
Boards like the DUE have multiple serial ports:

Flipper: `TX = 13, RX = 14`

Auduino DUE: `TX1 = 19, RX1 = 18`

```ino
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
```


# Serial over Wifi?
Arduino Uno R4 Wifi: https://arduinogetstarted.com/tutorials/arduino-serial-to-wifi-converter 
