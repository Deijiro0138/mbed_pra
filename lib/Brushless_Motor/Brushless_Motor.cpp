#include "Brushless_Motor.h"

Brushless_Motor::Brushless_Motor(){}


void Brushless_Motor::Setup(){
    motor = 1.0;
    wait_us(2000000);
    motor = 0.0;
    wait_us(2000000);
}

void Brushless_Motor::Move_motor(float duty){
    motor.write(duty);
}

void Brushless_Motor::Check_motor(){
    for (float p = 0.0; p <= 1.0; p += 0.025){
        motor = p;
        wait_us(100000);
    }
    for (float p = 1.0; p >= 0.0; p -= 0.025){
        motor = p;
        wait_us(100000);
    }

}