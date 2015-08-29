#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 7
#define CSN_PIN 8

const uint64_t pipe = 0xE8E8F0F0E1LL;
const uint64_t pipe_name2 = 0xE8E8F0F0E2LL;
RF24 radio(CE_PIN, CSN_PIN);
char buff[] = "Hello, Xec!";
void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.openReadingPipe(1, pipe_name2);
}

void loop() {
  radio.write( buff, strlen(buff) + 1 );
  radio.startListening();
  delay(100);
  if (radio.available()) {
    char buff2[128] = { 0 };
    radio.read(buff2, 128);
    Serial.println(buff2);
  }
  radio.stopListening();
}
