#include "Arduino.h"
#include "Ultrasonic.h"
#include "RobotMap.h"
#include <NewPing.h>

NewPing sonarFront(sonarFrontOut, sonarFrontIn, 300);
NewPing sonarRight(sonarRightOut, sonarRightIn, 300);
NewPing sonarBack(sonarBackOut, sonarBackIn, 300);

Ultrasonic::Ultrasonic() {
}

unsigned short Ultrasonic::get() {
    return state;
}

void Ultrasonic::updateLineSensor() {
    // over 335, a line is detected, return true and stop the robot
    lineSensor = (analogRead(lineSense) > 335);
}

/*void Ultrasonic::wallAhead() {
    return (sonarFront.ping_cm() < ((calRight + calBack) / 2));
}*/

bool Ultrasonic::safeToDrive() {
    return (lineSensor || state == wall);
}

void Ultrasonic::init() {
    // calibrate the wall sensor starting values
    calRight = sonarRight.ping_cm();
    calBack = sonarBack.ping_cm();
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
    if(abs(currRight - currBack) < 4) state = drive;
    if(currRight > (2 * currBack)) state = edge;
    if(currBack > (2 * currFront)) state = halfDrive;
    if(currFront < ((calRight + calBack) / 2)) state = wall;
}
