#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <Arduino.h>
#include "enums.hpp"
#include "motor_actions.hpp"
#include "world_state.hpp"
//#include <algorithm>

class algorithms {
    private:
        motor_actions* robot;
        world_state* world;
        line_states selfPosition;
        enemy_states enemyPosition;

    public:
        algorithms(motor_actions* robot, world_state* world);
        void match_strategy();
        void slammy_whammy();
        void updateEnemyPos(enemy_states pos);
        void avoid_white_line();
        int draw_circle();
        int attack_forward();
        int turn_towards();
        int attack_forward_no_delay();
        int turn_towards_no_delay();
        int dodge();
};

#endif