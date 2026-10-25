#include "world_state.hpp"
#include <Arduino.h>

world_state :: world_state (int* line_sensors, int* ir_sensors) {
    this -> ir_sensors = ir_sensors;
    this -> line_sensors = line_sensors;
};

line_states world_state :: line_check() {
    bool left = line_sensors[0] < 800; // 600
    bool right = line_sensors[1] < 800;

    if (left && right) return CENTER_LINE;
    if (left && !right) return LEFT_LINE;
    if (!left && right) return RIGHT_LINE;
    return OFF;
};

//uses ir_sensors array to decide where enemy is
enemy_states world_state :: enemy_pos() {
    bool left = ir_sensors[0] == 1;
    bool centerLeft = ir_sensors[1] == 1;
    bool right = ir_sensors[2] == 1;
    bool centerRight = ir_sensors[3] == 1;
    bool behind = ir_sensors[4] == 1;

    if (centerLeft && centerRight) return FRONT;
    if (left && centerLeft) return MIDLEFT;
    if (right && centerRight) return MIDRIGHT;
    
    if (behind && left) return BACKLEFT;
    if (behind && right) return BACKRIGHT;
    if (behind) return BEHIND;

    if (left) return LEFT;
    if (right) return RIGHT;

    // safety checks
    if (centerLeft) return MIDLEFT;
    if (centerRight) return MIDRIGHT;

    return UNKNOWN;
};
