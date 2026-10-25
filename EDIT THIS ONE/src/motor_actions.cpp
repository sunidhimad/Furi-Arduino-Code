#include <Arduino.h>
#include "motor_actions.hpp"

motor_actions :: motor_actions(int* motors) {
    this -> motors = motors;
    acceleration = 5;
}

void motor_actions :: brake() {
    motors[0] = 0;
    motors[1] = 0;
}

void motor_actions :: drive_forward(int speed) {
    if (speed - motors[0] > acceleration || speed - motors[1] > acceleration) {
        motors[0] += acceleration;
        motors[1] += acceleration;
    } else {
        motors[0] = speed; //left motor
        motors[1] = speed; //right motor
    }
};

void motor_actions :: drive_backward(int speed) {
    motors[0] = -1 * speed;
    motors[1] = -1 * speed;
};

//need to test for direction
void motor_actions :: turn_left(int speed) {
    motors[0] = -1 * speed;
    motors[1] = speed;
};

//need to test for direction
void motor_actions :: turn_right(int speed) {
    motors[0] = speed;
    motors[1] = -1 * speed;
};

void motor_actions :: drive_custom(int rSpeed, int lSpeed) {
    if (lSpeed - motors[0] > acceleration) {
        motors[0] += acceleration;
    } else if (rSpeed - motors[1] > acceleration) {
        motors[1] += acceleration;
    }
}