#include "Arduino.h"
#include "Ultrasonic.h"
#include "RobotMap.h"
#include <NewPing.h>

NewPing sonarFront(sonarFrontOut, sonarFrontIn, 375);
NewPing sonarRight(sonarRightOut, sonarRightIn, 375);
NewPing sonarBack(sonarBackOut, sonarBackIn, 375);

Ultrasonic::Ultrasonic() {
}

void Ultrasonic::lock() {
    writeableState = false;
}

void Ultrasonic::unlock() {
    writeableState = true;
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
    if(writeableState) {
        currRight = getSensorRight();
        currBack = getSensorBack();
        currFront = getSensorFront();
        if(abs(currRight - currBack) < 4) {
            state = drive;
            //Serial.println("All clear");
        }
        if(currRight > (2 * calRight)) {
            state = edge;
            //Serial.println("About to turn!");
        }
        if(currBack > (2 * calBack)) {
            state = halfDrive;
            // Serial.println("Almost around the corner");
        }
        if(currFront < ((calRight + calBack) / 2)) state = wall;
    }
}
