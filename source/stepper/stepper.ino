/*
 Name:      Stepper.ino
 Created:   2015/8/18 21:51:45
 Author:    xec
*/

// the setup function runs once when you press reset or power the board
#include "XStepper.h"

enum Direction {
    Forward,
    Backward
};

Direction      current_direction = Forward;
NXec::XStepper stepper(NXec::STEP_8, 8, 9, 10, 11);
void setup()
{
    stepper.init();
}

// the loop function runs over and over again until power down or reset
void loop()
{
    int value = analogRead(A0);
    int direction = digitalRead(2);

    int v = map(value, 0, 1024, 0, 100);

    if (direction == 1) {
        current_direction = current_direction == Forward ? Backward : Forward;
    }

    if (current_direction == Forward) {
        stepper.forward();
    } else if (current_direction == Backward) {
        stepper.backward();
    }

    delay(v);
}
