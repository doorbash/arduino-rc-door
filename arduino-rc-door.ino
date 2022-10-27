#include "config.h"
#include "serial_handler.h"

SerialHandler serial;
int data[50];

void setup() {
  pinMode(DATA_PIN, OUTPUT);

  digitalWrite(DATA_PIN, LOW);

  serial.init();

  if (SERIAL_TX_BUFFER_SIZE != 256 || SERIAL_RX_BUFFER_SIZE != 256) {
    while (true) {
      SerialHandler::debug("please set hardware serial rx/tx buffer size to 256");
      delay(1000);
    }
  }
#ifdef SOFTWARE_SERIAL
  if (_SS_MAX_RX_BUFF != 256) {
    while (true) {
      SerialHandler::debug("please set software serial rx buffer size to 256");
      delay(1000);
    }
  }
#endif

  SerialHandler::debug("Hello There!");
}

void loop() {
  if (serial.available()) {
    delay(500);
    serial.receive();
    if (strlen(serial.buffer) > 0) {
      if (strncmp("OPEN:", serial.buffer, 5) == 0) {
        int size = strlen(serial.buffer) - 6;
        if (size < 1) return;
        for (int i = 0; i < size; i++) {
          char c = serial.buffer[i + 6];
          if (c == 0) break;
          else if (c == '0' || c == '1') data[i] = c - '0';
          else return;
        }
        SerialHandler::debug("Opening door...");
        for (int cnt = 0; cnt < 15; cnt++) {
          for (int i = 0; i < size; i++) {
            digitalWrite(DATA_PIN, data[i]);
            delayMicroseconds(BIT_PERIOD);
          }
          digitalWrite(DATA_PIN, LOW);
          delay(12);
        }
      }
    }
  }
}
