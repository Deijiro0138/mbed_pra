#include "Servo.h"

Servo::Servo(){}



void Servo::Check_Servo(int pwm_1, int pwm_2){
    for(int i = pwm_1; i < pwm_2; i += 20){
        Servo_1.pulsewidth_us(i);
    }
}