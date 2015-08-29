//
//
//

#include "XStepper.h"
namespace NXec
{
    XStepper::XStepper(STEP_MODE step_mode, int pin1, int pin2, int pin3, int pin4)
        : motor_pin_1(pin1), motor_pin_2(pin2), motor_pin_3(pin3), motor_pin_4(pin4)
    {
        motor_step_mode = step_mode;
        current_step = 0;
    }

    void XStepper::init()
    {
        pinMode(this->motor_pin_1, OUTPUT);
        pinMode(this->motor_pin_2, OUTPUT);
        pinMode(this->motor_pin_3, OUTPUT);
        pinMode(this->motor_pin_4, OUTPUT);
    }

    void XStepper::forward()
    {
        setStep(current_step);
        if (motor_step_mode == STEP_4) {
            current_step += 2;
        } else if (motor_step_mode == STEP_8) {
            current_step ++;
        }

        current_step = current_step % 8;
    }

    void XStepper::backward()
    {
        setStep(7 - current_step);
        if (motor_step_mode == STEP_4) {
            current_step += 2;
        } else if (motor_step_mode == STEP_8) {
            current_step++;
        }

        current_step = current_step % 8;
    }

    void XStepper::setStep(int step)
    {
        switch (step) {
        case 0:
            digitalWrite(motor_pin_1, LOW);
            digitalWrite(motor_pin_2, HIGH);
            digitalWrite(motor_pin_3, HIGH);
            digitalWrite(motor_pin_4, HIGH);
            break;
        case 1:
            digitalWrite(motor_pin_1, LOW);
            digitalWrite(motor_pin_2, HIGH);
            digitalWrite(motor_pin_3, HIGH);
            digitalWrite(motor_pin_4, LOW);
            break;
        case 2:
            digitalWrite(motor_pin_1, HIGH);
            digitalWrite(motor_pin_2, HIGH);
            digitalWrite(motor_pin_3, HIGH);
            digitalWrite(motor_pin_4, LOW);
            break;
        case 3:
            digitalWrite(motor_pin_1, HIGH);
            digitalWrite(motor_pin_2, HIGH);
            digitalWrite(motor_pin_3, LOW);
            digitalWrite(motor_pin_4, LOW);
            break;
        case 4:
            digitalWrite(motor_pin_1, HIGH);
            digitalWrite(motor_pin_2, HIGH);
            digitalWrite(motor_pin_3, LOW);
            digitalWrite(motor_pin_4, HIGH);
            break;
        case 5:
            digitalWrite(motor_pin_1, HIGH);
            digitalWrite(motor_pin_2, LOW);
            digitalWrite(motor_pin_3, LOW);
            digitalWrite(motor_pin_4, HIGH);
            break;
        case 6:
            digitalWrite(motor_pin_1, HIGH);
            digitalWrite(motor_pin_2, LOW);
            digitalWrite(motor_pin_3, HIGH);
            digitalWrite(motor_pin_4, HIGH);
            break;
        case 7:
            digitalWrite(motor_pin_1, LOW);
            digitalWrite(motor_pin_2, LOW);
            digitalWrite(motor_pin_3, HIGH);
            digitalWrite(motor_pin_4, HIGH);
            break;
        }

    }
}
