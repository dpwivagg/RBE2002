/*
 *  Navigation.cpp
 *
 *  Created on: 4/19/17
 *      Author: James and Dan
 */

#include "Navigation.h"
#include "Chassis.h"
#include <math.h>

Navigation::Navigation() {}

bool Navigation::init() {
    return gyro.init();
}

double Navigation::getDir() {
    gyroRead = gyro.getZ();
    encoderError = encoderTicksL - encoderTicksR;
    if(encoderError < 0) sign = true;
    else sign = false;

    // determine angular displacement from encoders:
    height = pow((((double)encoderError / (double)encTicksPerRev) * 2 * M_PI * radius),2);
    c = (72 - height) / 72;
    heading = acos(c);

    // sensor fusion algorithm:
    aheading = (0.85*(heading * (180.0 / M_PI)) / 1.35) + (0.5*gyroRead / 1.35);

    if(sign) return (0 - aheading);
    return aheading;  // Returns the angle of displacement in degrees
}

// encoders must be handled in main.cpp because they utilize interrupts
void Navigation::updateEnc(int _encoderTicksL, int _encoderTicksR) {
    encoderTicksOldL = encoderTicksL;
    encoderTicksOldR = encoderTicksR;
    encoderTicksL = _encoderTicksL;
    encoderTicksR = _encoderTicksR;
}

// call when making a right turn to update distance tracking
void Navigation::right() {
    yDist += ((encoderTicksL + encoderTicksR) / 2) - xDist;
}

// call when making a left turn to update distance tracking
void Navigation::left() {
    xDist += ((encoderTicksL + encoderTicksR) / 2) - yDist;
}

// returns the final distance followed based on encoders
int Navigation::getXpos() {
    return xDist / encTicksPerRev * 2 * M_PI * radius;
}

int Navigation::getYpos() {
    return yDist / encTicksPerRev * 2 * M_PI * radius;
}

void Navigation::updateGyro() {
    gyro.update();
    // noInterrupts();
    // float vectorchange = getDir() * ((encoderTicksR - encoderTicksOldR)*(encoderTicksL - encoderTicksOldL))/2;
    // xDir = xDir + cos(vectorchange);
    // yDir = yDir + sin(vectorchange);
    // interrupts();
}
