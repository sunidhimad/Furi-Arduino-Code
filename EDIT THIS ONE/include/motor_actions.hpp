#ifndef ROBOT_ACTIONS_H
#define ROBOT_ACTIONS_H

class motor_actions {
    private:
        int* motors;
        int acceleration;
    public:
        motor_actions(int* motor);
        void brake();
        void drive_forward(int speed);
        void drive_backward(int speed);
        void turn_left(int speed);
        void turn_right(int speed);
        void drive_custom(int rightSpeed, int leftSpeed);
};

#endif