#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include "enums.hpp"

class world_state {

    private:
        int* ir_sensors;
        int* line_sensors;
        line_states line_arr[4] = {OFF, LEFT_LINE, RIGHT_LINE, CENTER_LINE};

    public:
        world_state(int* line_sensors, int* ir_sensors);
        line_states line_check();
        enemy_states enemy_pos();
};

#endif

