#ifndef Brushless_Motor_h
#define Brushless_Motor_h
#include "mbed.h"
PwmOut motor(A1);


class Brushless_Motor{
    public:
    Brushless_Motor();

    const float max_duty = 1.0;
    const float min_duty = 0.0;
    const float setup_period = 10;
    void Setup();
    void Move_motor(float duty);

    private:
    void Check_motor();
};
#endif