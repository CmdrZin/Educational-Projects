/*
 * File: Arduino_SPI_Client.ino
 * Author: Nels D. "Chip" Pearson (aka Cmdrzin)
 * Created: 18feb2026
 *
 * This is a simple SPI Client use to test the ITMC_III_4a SPI Host code.
 * It will print to the Serial Monitor and valid ASCII code sent from the Host.
 *
 * (see also https://docs.arduino.cc/language-reference/en/functions/communication/SPI/)
 */

bool volatile spiReceived = false;      // these can be changed by the interrupt routine.
char volatile spiData = '0';

void setup() {
  Serial.begin(9600);

  // SPI control register: enable SPI in slave mode, enable interrupt
  // Arduino API does not support Client SPI setup. So, must be done manually.
  SPCR = _BV(SPE) | _BV(SPIE);      // enable SPI, enable SPI interrupts
  SPCR &= ~_BV(MSTR);               // slave mode

  Serial.println("Client set up to receive data.");
}

void loop() {
  static char count = 0;

  if(spiReceived) {
    spiReceived = false;
    Serial.print(spiData);
    if(++count > 26) {
      count = 0;
      Serial.println("");
    }
  }
}


// SPI Interrupt
ISR(SPI_STC_vect)
{
  spiData = SPDR;
  spiReceived = true;
}
