#ifndef SERIAL_HANDLER
#define SERIAL_HANDLER

#include "config.h"
#include <Arduino.h>
#ifdef SOFTWARE_SERIAL
#include <SoftwareSerial.h>
#endif

class SerialHandler {
  private:
    Stream *module;
#ifdef SOFTWARE_SERIAL
    SoftwareSerial ss {SS_RX_PIN, SS_TX_PIN};
#endif
    int bufferIndex;

  public:
    char buffer[MAX_BUFFER_SIZE];
    void init();
    void send(char *text);
    void receive();
    void command(char *text);
    void command(const char *format, ...);
    static void debug(char *text);
    static void debug(const char *format, ...);
    bool available();
};

#endif
