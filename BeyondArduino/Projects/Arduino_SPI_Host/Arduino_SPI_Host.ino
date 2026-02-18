/*
 * File: Arduino_SPI_Host.ino
 * Author: Nels D. "Chip" Pearson (aka Cmdrzin)
 * Created: 18feb2026
 *
 * This is a simple SPI Host use to test the ITMC_III_4b SPI Client code.
 * It will send out ASCII characters to control an LED on the Client.
 *
 * (see also https://docs.arduino.cc/language-reference/en/functions/communication/SPI/)
 */
#include <SPI.h>

#define WAIT_DELAY 1000

#define _SS 10

char spiData = '0';

void setup() {
  Serial.begin(9600);

  pinMode(_SS, OUTPUT);

  SPI.begin();
  SPI.beginTransaction(SPISettings(50000, MSBFIRST, SPI_MODE0));

  Serial.println("");
  Serial.println("Host set up to send data.");
}

void loop() {
  static uint32_t waitTime = 0;
  static char count = 0;
  char loopBack;

  if(waitTime < millis()) {
    waitTime = millis() + WAIT_DELAY;

    if(spiData == 'A') {
      spiData = 'B';
    } else {
      spiData = 'A';
    }

    digitalWrite(_SS, LOW);
    SPI.transfer(spiData);
    delay(1);
    // Uncomment out to read data back from the Client.
//    loopBack = SPDR;
//    Serial.print(loopBack);
    digitalWrite(_SS, HIGH);

    Serial.print(spiData);
      if(++count > 20) {
        count = 0;
        Serial.println("");
      }
  }
}
