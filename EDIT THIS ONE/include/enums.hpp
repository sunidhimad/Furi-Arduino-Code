#ifndef ENUMS_HPP
#define ENUMS_HPP

enum line_states {
    OFF,
    LEFT_LINE,
    RIGHT_LINE,
    CENTER_LINE
};

// two sensors on the front
// one on each side of bot
// one more sensor on back
enum enemy_states {
    UNKNOWN, // not seen
    LEFT, // left sensor
    MIDLEFT, // left + frontleft sensors
    FRONT, // both front sensors (frontleft + frontright)
    RIGHT, // right sensor
    MIDRIGHT, // right + frontright sensors
    BACKRIGHT,
    BEHIND, // back sensor
    BACKLEFT
};

#endif