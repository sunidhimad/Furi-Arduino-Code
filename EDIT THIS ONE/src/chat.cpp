// #include <Arduino.h>
// #include "world_state.hpp"
// #include "algorithms.hpp"
// #include "motor_actions.hpp"
// #include "world_state.hpp"

// // IR sensor pins
// const int irR = 8;
// const int irCR = 10;
// const int irCL = 2;
// const int irL = 4;
// const int irB = 7;

// // Line sensor pins
// const int lineLeft = A0;
// const int lineRight = A1;

// // Motor pins
// const int leftMotorDIR = 9;
// const int leftMotorPWM = 6;
// const int rightMotorDIR = 5;
// const int rightMotorPWM = 3;

// //debug
// unsigned long lastDebug = 0;

// // arrays
// int motors[2] = {0, 0};
// int line_sensors[2] = {0, 0};
// int ir_sensors[5] = {0, 0, 0, 0, 0}; 

// // speed
// int speed = 90;              // 🔧 CHANGED: higher base speed
// int first = 1;
// int initSpeed = 90;          // 🔧 CHANGED: increased from 55
// int attackSpeed = 150;       // 🔧 CHANGED: burst speed

// // 🔧 NEW: higher threshold for earlier detection
// const int LINE_THRESHOLD = 700;

// // 🔧 NEW: EDGE FAILSAFE FUNCTION (used everywhere)
// bool edgeDetected() {
//   return (line_sensors[0] < LINE_THRESHOLD || line_sensors[1] < LINE_THRESHOLD);
// }

// // functions
// void pollSensors();
// void updateState();
// void forward();
// void backward();
// void stopRobot();
// void turnRight();
// void turnLeft();
// void customDrive(int lspeed, int rspeed);
// void firstForward();

// void setup() {
//   pinMode(irR, INPUT);
//   pinMode(irCR, INPUT);
//   pinMode(irCL, INPUT);
//   pinMode(irL, INPUT);
//   pinMode(irB, INPUT);
//   pinMode(A0, INPUT);
//   pinMode(A1, INPUT);

//   pinMode(leftMotorDIR, OUTPUT);
//   pinMode(leftMotorPWM, OUTPUT);
//   pinMode(rightMotorDIR, OUTPUT);
//   pinMode(rightMotorPWM, OUTPUT);

//   delay(3600);
// }

// void loop() {
//   pollSensors();
//   speed = initSpeed;
//   updateState();
// }

// // 🔧 IMPROVED: sensor polling unchanged but used more often
// void pollSensors() {
//   ir_sensors[0] = digitalRead(irL);
//   ir_sensors[1] = digitalRead(irCL);
//   ir_sensors[2] = digitalRead(irCR);
//   ir_sensors[3] = digitalRead(irR);
//   ir_sensors[4] = digitalRead(irB);

//   line_sensors[0] = analogRead(lineLeft);
//   line_sensors[1] = analogRead(lineRight);
// }

// void updateState() {
//   bool left = line_sensors[0] < LINE_THRESHOLD;
//   bool right = line_sensors[1] < LINE_THRESHOLD;

//   if (first == 1) {
//     firstForward();
//     delay(10);
//     first = 0;
//   }

//   // 🔧 PRIORITY 1: EDGE ESCAPE (FASTER + SHORTER DELAYS)
//   if (left || right) {
//     backward();
//     delay(120);   // 🔧 REDUCED from 200

//     turnLeft();
//     delay(40);    // 🔧 REDUCED from 65

//     return;
//   }

//   // -------- PRIORITY 2: ATTACK --------
//   if (ir_sensors[1] == 1 && ir_sensors[2] == 1) {

//     // 🔧 FIXED BUG: correct logic
//     if (line_sensors[0] >= LINE_THRESHOLD && line_sensors[1] >= LINE_THRESHOLD) {
//         speed = attackSpeed;   // 🔧 burst speed instead of increment
//     }

//     if (speed > 255) speed = 255;

//     forward();
//     delay(5);  // 🔧 reduced delay
//     return;

//   } else if (ir_sensors[0] == 1 && ir_sensors[1] == 1) {
//     turnLeft();
//     delay(5);
//     return;

//   } else if (ir_sensors[0] == 1) {
//     turnLeft();
//     delay(5);
//     return;

//   } else if (ir_sensors[2] == 1 && ir_sensors[3] == 1) {
//     turnRight();
//     delay(5);
//     return;

//   } else if (ir_sensors[3] == 1) {
//     turnRight();
//     delay(5);
//     return;
//   }

//   // -------- PRIORITY 3: SEARCH --------
//   else {
//     turnLeft();
//   }
// }

// void stopRobot() {
//   analogWrite(leftMotorDIR, 0);
//   analogWrite(leftMotorPWM, 0);
//   analogWrite(rightMotorDIR, 0);
//   analogWrite(rightMotorPWM, 0);
// }

// // 🔧 UPDATED: forward now constantly checks edge
// void forward() {
//   pollSensors();  // 🔧 NEW: re-check sensors during movement

//   if (edgeDetected()) {
//     backward();
//     delay(120);
//     turnLeft();
//     delay(40);
//     return;
//   }

//   analogWrite(leftMotorDIR, speed);
//   analogWrite(leftMotorPWM, 0);
//   analogWrite(rightMotorDIR, 0);
//   analogWrite(rightMotorPWM, speed);
// }

// void firstForward() {
//   analogWrite(leftMotorDIR, speed);
//   analogWrite(leftMotorPWM, 0);
//   analogWrite(rightMotorDIR, 0);
//   analogWrite(rightMotorPWM, speed);
// }

// void backward() {
//   analogWrite(leftMotorDIR, 0);
//   analogWrite(leftMotorPWM, speed);
//   analogWrite(rightMotorDIR, speed);
//   analogWrite(rightMotorPWM, 0);
// }

// void turnLeft() {
//   pollSensors();  // 🔧 NEW: check while turning

//   if (edgeDetected()) {
//     backward();
//     delay(100);
//     return;
//   }

//   analogWrite(leftMotorDIR, 0);
//   analogWrite(leftMotorPWM, speed);
//   analogWrite(rightMotorDIR, 0);
//   analogWrite(rightMotorPWM, speed);
// }

// void turnRight() {
//   pollSensors();  // 🔧 NEW: check while turning

//   if (edgeDetected()) {
//     backward();
//     delay(100);
//     return;
//   }

//   analogWrite(leftMotorDIR, speed);
//   analogWrite(leftMotorPWM, 0);
//   analogWrite(rightMotorDIR, speed);
//   analogWrite(rightMotorPWM, 0);
// }

// void customDrive(int lspeed, int rspeed) {
//   analogWrite(leftMotorDIR, lspeed);
//   analogWrite(leftMotorPWM, 0);
//   analogWrite(rightMotorDIR, 0);
//   analogWrite(rightMotorPWM, rspeed);
// }