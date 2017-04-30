#include <Arduino.h>
#include <Servo.h>
#include "FlameSense.h"

int turn = 0;

void FlameSense::init() {
    servoTurn.attach(servoTurnDigitalPin,500,2500);
    servoTilt.attach(servoTiltDigitalPin, 800, 2200);
}

// void FlameSense::update(bool found, int pos) {
//     if(!found) servoSpin(found);
//     else setTurn(pos);
// }

int FlameSense::getTurn() {
    return turn;
}

void FlameSense::servoSpin(bool found) {
    if(found) servoTurn.write(turn);
    else if(turn<=110) {
        turn++;
        servoTurn.write(turn);
    } else {
        turn  = 0;
        servoTurn.write(turn);
    }
}

void FlameSense::setTurn(int t){
  servoTurn.write(turn);
}
