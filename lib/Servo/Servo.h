#ifndef Servo_h
#define Servo_h

#include "mbed.h"
PwmOut Servo_1(A0);

class Servo{
    public:
    Servo();

    void setup(PwmOut pwm);

    private:
    void Check_Servo(int pwm_1, int pwm_2);
    
};

#endif