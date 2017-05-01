/*
 *  Chassis.cpp
 *
 *  Created on: 2/26/17
 *      Author: james
 */

#include "Arduino.h"
#include "Chassis.h"
#include <Servo.h>

Chassis::Chassis(){}

void Chassis::attach(unsigned char leftMotorFwd, unsigned char rightMotorFwd) {
    speedState = 0;
    turnState = 0;

    leftMotor.attach(leftMotorFwd, 1000, 2000);
    rightMotor.attach(rightMotorFwd, 1000, 2000);
}

void Chassis::tank (signed short leftspd, signed short rightspd) {
    leftMotor.write(90 - leftspd);

    rightMotor.write(90 + rightspd);
}

void Chassis::stop () { //stop
    speedState = 0;
    turnState =  0;
}

void Chassis::instantStop () {
        leftMotor.write(90);

        rightMotor.write(90);
}

void Chassis::instantGo(int go) { //bypasses update();
        leftMotor.write(90 + go);

        rightMotor.write(90 - go);
}


void Chassis::drive(signed char speed, signed char turn) { //go
    speedState = speed;
    turnState = 0.3 * turn;
}

void Chassis::drive(signed char speed) { //go
    speedState = speed;
}

float Chassis::driveStraight(float setpoint, float currentpoint) { //go
    float kp = 0.1;
    return kp * (setpoint - currentpoint);
}

void Chassis::turn(signed char turn) { //keep going but turn
    turnState = turn;
}

void Chassis::update() {
      updateSinglePWM();

}

void Chassis::updateSinglePWM() {
    volatile signed char currLeftSpeed = 0;
    volatile signed char currRightSpeed = 0;

    if ((int)speedState + (int)turnState > 90) {
        currLeftSpeed =  90;
    } else if ((int)speedState + (int)turnState < -90) {
        currLeftSpeed = -90;
    } else {
        currLeftSpeed = speedState + turnState;
    }

    if ((int)speedState - (int)turnState > 90) {
        currRightSpeed =  90;
    } else if ((int)speedState - (int)turnState < -90) {
        currRightSpeed = -90;
    } else {
        currRightSpeed = speedState - turnState;
    }


    leftMotor.write(90 + (currLeftSpeed));

    rightMotor.write(90 - (currRightSpeed));

}
