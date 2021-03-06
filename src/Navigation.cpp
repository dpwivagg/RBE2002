#include "Navigation.h"
#include "Chassis.h"
#include <math.h>

Navigation::Navigation() {}

bool Navigation::init() {
    return gyro.init();
}

double Navigation::getDir() {
    // TODO : Implement sensor fusion with gyro and encoders (currently only encoders are used)
    // gyroRead = gyro.getZ();
    encoderError = encoderTicksL - encoderTicksR;
    if(encoderError < 0) sign = true;
    else sign = false;
    height = pow((((double)encoderError / (double)encTicksPerRev) * 2 * M_PI * radius),2);
    c = (72 - height) / 72;
    heading = acos(c);
    aheading = 0.85*(heading * (180.0 / M_PI));
    if(sign) return (0 - aheading);
    return aheading;  // Returns the angle of displacement in degrees
    // See the page in our box for worked calculations
    // return gyroRead;
}

void Navigation::updateEnc(int _encoderTicksL, int _encoderTicksR) {
    encoderTicksOldL = encoderTicksL;
    encoderTicksOldR = encoderTicksR;
    encoderTicksL = _encoderTicksL;
    encoderTicksR = _encoderTicksR;
}

void Navigation::updateGyro() {
    gyro.update();
    // noInterrupts();
    // float vectorchange = getDir() * ((encoderTicksR - encoderTicksOldR)*(encoderTicksL - encoderTicksOldL))/2;
    // xDir = xDir + cos(vectorchange);
    // yDir = yDir + sin(vectorchange);
    // interrupts();
}
