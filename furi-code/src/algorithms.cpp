#include "algorithms.hpp"
#include "enums.hpp"

int multiplier = 1;

algorithms :: algorithms(motor_actions *robot, world_state *world) {
    this -> robot = robot;
    this -> world = world;
    selfPosition = OFF;
    enemyPosition = FRONT;
}

void algorithms::match_strategy() {
    Serial.print("ALGO");
    // Update positions based on the latest sensor/world state
    selfPosition = world->line_check();
    enemyPosition = world->enemy_pos();

    // // Attack logic
    slammy_whammy();
    draw_circle();

    // Safety adjustments
    if (enemyPosition == LEFT || enemyPosition == RIGHT) {
        dodge();
    }
    
    // try not to fall off doyo
    avoid_white_line();
}

void algorithms :: slammy_whammy() {
    if (enemyPosition != UNKNOWN) {
        if (turn_towards_no_delay() == 0) {
            Serial.print("Slammy Whammy");
            attack_forward_no_delay();
        } else {
            multiplier = 1;
        }
    }
}

int algorithms::draw_circle() {
    // Check if enemy is detected
    if (enemyPosition != UNKNOWN) {
        robot->brake();   // stop immediately
        return 0;         // exit
    }
    // No enemy → turn until enemy is seen
    if (selfPosition == LEFT_LINE) {
        robot->drive_custom(100, 50); // left motor 100, right motor 50 → curve right
        return 0;
    } else {
        robot->drive_custom(50, 100); // left motor 100, right motor 50 → curve right
        return 0;
    }
}

void algorithms :: updateEnemyPos(enemy_states pos) {
    enemyPosition = pos;
}

void algorithms::avoid_white_line() {
    if (selfPosition == LEFT_LINE || selfPosition == RIGHT_LINE || selfPosition == CENTER_LINE) {
        // Step 1: Stop immediately
        robot->brake();
        delay(60); // small pause
        //100!!!!

        // Step 2: Move backwards slightly
        robot->drive_backward(60); // moderate reverse speed
        //100!!!
        delay(300); // reverse for 0.3 seconds
        robot->brake();
        delay(100);

        // Step 3: Turn away from the line
        if (selfPosition == LEFT_LINE) {
            robot->turn_right(60); // turn right if left sensor sees line
            //100!!!
        } else if (selfPosition == RIGHT_LINE) {
            robot->turn_left(60);  // turn left if right sensor sees line
            //100!!!
        } else {
            // Both sensors see line, pick a default turn direction
            robot->turn_left(70);
            //120!!!
        }
        delay(300); // turn for 0.3 seconds
        robot->drive_forward(40); // 80!!!!
    }
}

//if enemy is on either right or left, escape
int algorithms :: dodge() {
    if (enemyPosition == LEFT) {
        robot -> drive_custom(40, 70);//drive_custom(75, 150)
        return 1;
    } else if (enemyPosition == RIGHT) {
        robot -> drive_custom(70, 40);//drive_custom(150, 75)
        return 1;
    }
    return 0;
} 

// drive forward if we see someone in front of us
// assume that we have already been confirmed to see
int algorithms :: attack_forward_no_delay() {
    enemy_states enemy = enemyPosition;
    // if the robot is in front, drive forward
    if (enemy == FRONT) {
        robot -> drive_forward(constrain(50 * multiplier, 0, 100));
        //constrain(150 * multiplier, 0, 255)
        multiplier += 5;
        return 1;
    //if we don't see the robot, brake and do nothing
    } else {
        multiplier = 1;
        robot -> brake();
        return 0;
    }
}

// returns 0 if we should proceed to attack_forward, returns 1 otherwise
int algorithms :: turn_towards_no_delay() {
    enemy_states enemy = enemyPosition;
    if (enemy == MIDLEFT) {
        //turn left a little slower
        robot -> turn_left(60);//140
        return 1;
    } else if (enemy == LEFT) {
        //turn left
        robot -> turn_left(70);//170
        return 1;
    } else if (enemy == MIDRIGHT) {
        //turn right a little slower
        robot -> turn_right(60);//140
        return 1;
    } else if (enemy == RIGHT) {
        //turn right
        robot -> turn_right(70);//170
        return 1;
    } else if (enemy == BACKLEFT) {
        // turn left quickly
        robot -> turn_left(80);//200
        return 1;
    } else if (enemy == BACKRIGHT) {
        // turn right quickly
        robot -> turn_right(80);//200
        return 1;
    } else if (enemy == BEHIND) {
        // make a circle
        draw_circle();
        return 1;
    } else {
        return 0;
    }
}