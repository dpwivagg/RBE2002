/*
 *  Arm.cpp
 *
 *  Created on: 2/26/17
 *      Author: james
 */

#include "Arduino.h"
#include "Arm.h"
#include <Servo.h>

static const float kp = 1, ki = 0, kd = 0;
Servo gripServo;

Arm::Arm() {}

void Arm::attach (unsigned char armMotorPort, unsigned char potPort, unsigned char gripServoPort) {
    pot = potPort;

    pinMode(potPort, INPUT_PULLUP);
    pinMode(gripServoPort, OUTPUT);


    armSetPoint = HIGHPOS;
    gripPos = 180;
    armMotor.attach(armMotorPort, 1000, 2000);
    gripServo.attach(gripServoPort);
}

void Arm::setHigh () { //set arm high
    set (HIGHPOS);
}

void Arm::setLow () { //set arm low
    set (LOWPOS);
}

void Arm::stop () { //stop
    armSpeed = 90;
}

void Arm::instantStop () { //skips update();
    armMotor.write(90);
}

void Arm::updatePot () { //set potentiometer current point
    armCurrentPoint = analogRead(pot);
}

unsigned char Arm::getPot() { //get potentiometer current point
    return armCurrentPoint;
}

void Arm::set (int pos) { //set arm to a point
    armSetPoint = pos;
}

int Arm::pid () { //default pid overload
    return pid(armSetPoint, armCurrentPoint);
}

int Arm::pid (int setpoint, int currentpoint) {
    int error = - setpoint + currentpoint;
    int inttime = millis() - lastTime;
    int lasterror = error;

    return (kp * error) + (ki * (integral += (error * inttime))) + (kd * (error-lasterror));
}
void Arm::openGrip() { //open grip
    gripPos = 30;
}

void Arm::closeGrip() { //close grip
    gripPos = 150;
}

void Arm::update() {
    updatePot();
    Serial.print("ARM POT: ");
    Serial.println((int) armCurrentPoint);
    armMotor.write(90 + pid());
    gripServo.write(gripPos);
}
