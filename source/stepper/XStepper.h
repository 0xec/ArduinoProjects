// XStepper.h

#ifndef _XSTEPPER_h
#define _XSTEPPER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

namespace NXec
{
    enum STEP_MODE {
        STEP_4,  // 4拍方式
        STEP_8   // 8拍方式
    };
    class XStepper
    {

      public:
        XStepper(STEP_MODE step_mode, int pin1, int pin2, int pin3, int pin4);
        void init();

        void forward();
        void backward();

      protected:
        void setStep(int step);

      private:
        int motor_pin_1;
        int motor_pin_2;
        int motor_pin_3;
        int motor_pin_4;

        int current_step = 0;
        STEP_MODE motor_step_mode;
    };
}

#endif

