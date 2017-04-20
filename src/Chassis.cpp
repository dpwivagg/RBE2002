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

void Chassis::attach(unsigned char leftMotorFwd, unsigned char leftMotorRwd, unsigned char rightMotorFwd, unsigned char rightMotorRwd) {
    driveLF =  leftMotorFwd;
    driveRF = rightMotorFwd;
    driveLR =  leftMotorRwd;
    driveRR = rightMotorRwd;

    speedState = 0;
    turnState = 0;

    pinMode(driveLF, OUTPUT);
    pinMode(driveRF, OUTPUT);
    pinMode(driveLR, OUTPUT);
    pinMode(driveRR, OUTPUT);

}

void Chassis::attach(unsigned char leftMotorFwd, unsigned char rightMotorFwd) {
    driveLF =  leftMotorFwd;
    driveRF = rightMotorFwd;
    driveLR = '\0';
    driveRR = '\0';

    speedState = 0;
    turnState = 0;

    leftMotor.attach(driveLF, 1000, 2000);
    rightMotor.attach(driveRF, 1000, 2000);
}

void Chassis::stop () { //stop
    speedState = 0;
    turnState = 0;
}

void Chassis::instantStop () { //bypasses update();
    analogWrite(driveLF, 0);
    analogWrite(driveRF, 0);
    analogWrite(driveLR, 0);
    analogWrite(driveRR, 0);
}


void Chassis::drive(signed char speed, signed char turn) { //go
    speedState = speed;
    turnState = turn;
}

void Chassis::drive(signed char speed) { //go
    speedState = speed;
}

void Chassis::driveStraight(float setpoint, float currentpoint) { //go
    gyro.getX();
}

void Chassis::updateNav() {
    gyro.update();
}

void Chassis::turn(signed char turn) { //keep going but turn
    turnState = turn;
}

void Chassis::update() {
    if (driveLR == '\0' || driveRR == '\0') {
      updateSinglePWM();
    } else {
      updateDualPWM();
    }

}

void Chassis::updateSinglePWM() {
    signed char currLeftSpeed;
    signed char currRightSpeed;

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


    leftMotor.write(90 + currLeftSpeed);

    rightMotor.write(90 + currRightSpeed);

}

void Chassis::updateDualPWM() {

    signed char currLeftSpeed;
    signed char currRightSpeed;

    if ((int)speedState + (int)turnState > 127) {
        currLeftSpeed =  127;
    } else if ((int)speedState + (int)turnState < -127) {
        currLeftSpeed = -127;
    } else {
        currLeftSpeed = speedState + turnState;
    }

    if ((int)speedState - (int)turnState > 127) {
        currRightSpeed =  127;
    } else if ((int)speedState - (int)turnState < -127) {
        currRightSpeed = -127;
    } else {
        currRightSpeed = speedState - turnState;
    }

    if (currLeftSpeed > 0) {
        analogWrite(driveLF,  2 * currLeftSpeed);
        analogWrite(driveLR, 0);
    } else {
        analogWrite(driveLF, 0);
        analogWrite(driveLR, -2 * currLeftSpeed);

    }

    if (currRightSpeed > 0) {
        analogWrite(driveRF,  2 * currRightSpeed);
        analogWrite(driveRR, 0);

    } else {
        analogWrite(driveRF, 0);
        analogWrite(driveRR, -2 * currRightSpeed);

    }


}
