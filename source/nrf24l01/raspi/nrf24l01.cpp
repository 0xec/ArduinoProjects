#include <iostream>
#include <RF24/RF24.h>

using namespace std;

RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);
const uint64_t pipe_name = 0xE8E8F0F0E1LL;
const uint64_t pipe_name2 = 0xE8E8F0F0E2LL;
int joystick[2];
int main(int argc, char* argv[])
{
    radio.begin();
    radio.openReadingPipe(1, pipe_name);
    radio.openWritingPipe(pipe_name2);
    radio.startListening();

    radio.printDetails();

    cout << "start listening" << endl;

    long tick = 0;

    while (true) {
        if (radio.available()) {
            //cout << "data available" << endl;

            char buff[128] = { 0 };
            radio.read(buff, 128);

            printf("data: %s\n", buff);

            radio.stopListening();
            char resp[128];
            sprintf(resp, "response: %ld", tick++);
            radio.write(resp, strlen(resp));
            radio.startListening();

            bcm2835_delay(1000);
        }
    }
    return 0;
}