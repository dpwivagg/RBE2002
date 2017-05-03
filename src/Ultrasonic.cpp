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

bool Ultrasonic::updateLineSensor() {
    // over 335, a line is detected, return true and stop the robot
    if(analogRead(lineSense) > 335) return true;
    else return false;
}

bool Ultrasonic::safeToDrive() {
    if(state == wall || updateLineSensor()) return false;
    return true;
}

void Ultrasonic::init() {
    // calibrate the wall sensor starting values
    calRight = sonarRight.ping_cm();
    calBack = sonarBack.ping_cm();
    //Serial.println((calRight + calBack)/2);
}

unsigned int Ultrasonic::getSensorRight() { //get forward right US
    return sonarRight.ping_cm();
}

unsigned int Ultrasonic::getSensorBack() {  //get backward right US
    return sonarBack.ping_cm();
}

unsigned int Ultrasonic::getSensorFront() { //get front US
    return sonarFront.ping_cm();
}

void Ultrasonic::update() {
    currRight = getSensorRight();
    // Serial.println(currRight);
    currBack = getSensorBack();
    // Serial.println(currBack);
    currFront = getSensorFront();

    // Serial.println(currFront);
    if(currFront < 30 && currFront != 0) state = wall;
    else if(updateLineSensor()) state = wall;
    else if(currRight > (2 * calRight) && currRight != 0) state = edge;
    else if(currBack > (2 * calBack)) state = halfDrive;
    else if(currRight < calRight) state = closeWall;

    else state = drive;
}
