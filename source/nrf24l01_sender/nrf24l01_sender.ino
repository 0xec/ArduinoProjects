#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

#define CE_PIN 9
#define CSN_PIN 10

typedef struct _PACKET {
  uint8_t l;
  uint16_t len;
  char buff[32];
} PACKET;

const uint64_t pipe_name_1 = 0xEC010203LL;
uint64_t tick = 0;
RF24 radio(CE_PIN, CSN_PIN);
char buff[] = "\x06\x04\0x00test";
void setup() {
  Serial.begin(115200);
  radio.begin();
  //radio.openReadingPipe(1, pipe_name_1);
  radio.openWritingPipe(pipe_name_1);
  radio.setAutoAck(true);
  radio.setChannel(1);
  radio.setCRCLength(RF24_CRC_16);
}

void loop() {
  PACKET p;
  strcpy(p.buff, "test");
  p.len = strlen(p.buff);
  p.l = 6;
  radio.write(&p, sizeof(PACKET));
 // delay(1000);
}
