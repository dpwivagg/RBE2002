#include "Arduino.h"
#include "Ultrasonic.h"
#include "RobotMap.h"
#include <NewPing.h>

NewPing sonarFront(sonarFrontOut, sonarFrontIn, 375);
NewPing sonarRight(sonarRightOut, sonarRightIn, 375);
NewPing sonarBack(sonarBackOut, sonarBackIn, 375);

Ultrasonic::Ultrasonic() {
}

unsigned short Ultrasonic::get() {
    return state;
}

void Ultrasonic::updateLineSensor() {
    // over 335, a line is detected, return true and stop the robot
    if(analogRead(lineSense) > 335) lineSensor = true;
    else lineSensor = false;
}

/*void Ultrasonic::wallAhead() {
    return (sonarFront.ping_cm() < ((calRight + calBack) / 2));
}*/

bool Ultrasonic::safeToDrive() {
    if(state == wall || lineSensor) return false;
    return true;
}

void Ultrasonic::init() {
    // calibrate the wall sensor starting values
    calRight = sonarRight.ping_cm();
    calBack = sonarBack.ping_cm();
    //Serial.println((calRight + calBack)/2);
}

unsigned int Ultrasonic::getSensorRight() {
    return sonarRight.ping_cm();
}

unsigned int Ultrasonic::getSensorBack() {
    return sonarBack.ping_cm();
}

unsigned int Ultrasonic::getSensorFront() {
    return sonarFront.ping_cm();
}

void Ultrasonic::update() {
    currRight = getSensorRight();
    currBack = getSensorBack();
    currFront = getSensorFront();
    if(currFront < 30 && currFront != 0) state = wall;
    // else if(currRight > (2 * calRight) && currBack > (2 * calBack)) state = closeWall;
    else if(currRight > (2 * calRight) && currRight != 0) state = edge;
    // else if(currBack > (2 * calBack) && currBack != 0) state = halfDrive;
    else state = drive;
}
