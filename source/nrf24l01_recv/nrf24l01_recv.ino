#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>
#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);
void handler();
//
// Channel info
//
const uint64_t pipe_name_1 = 0xEC010203LL;
int message_count = 0;
//
// Setup
//

void setup(void)
{
  Serial.begin(115200);
  Serial.println("initialize start");

  radio.begin();
  //  //  radio.enableAckPayload();                         // We will be using the Ack Payload feature, so please enable it
  //  //radio.enableDynamicPayloads();                    // Ack payloads are dynamic payloads
  radio.openReadingPipe(1, pipe_name_1);
  //  // radio.maskIRQ(true, true, true);
  //radio.setAutoAck(true);
  radio.setChannel(1);
  radio.setCRCLength(RF24_CRC_16);
  //  // radio.openWritingPipe(pipe_name_2);
  radio.startListening();
  //  //   radio.writeAckPayload( 1, &message_count, sizeof(message_count) );  // Add an ack packet for the next time around.  This is a simple
  //  //  ++message_count;
  Serial.println("initialize ok");
  attachInterrupt(0, handler, FALLING);
}



//
// Loop
//
void loop(void)
{
  delay(1000);
}

void handler() {
  bool tx, fail, rx;

  Serial.println("interrupt start");

  radio.whatHappened(tx, fail, rx);                   // What happened?

  if ( tx ) {                                         // Have we successfully transmitted?
    Serial.println("Send OK");
  }

  if ( fail ) {                                       // Have we failed to transmit?
    Serial.println("fail");
  }

  if ( rx || radio.available()) {                     // Did we receive a message?
    char buff[128] = {0};

    radio.read(buff, sizeof(buff));
    Serial.println(buff);
  }

  Serial.println("interrupt end");
}
