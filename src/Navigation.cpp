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
    height = pow((((double)encoderError / (double)encTicksPerRev) * 2 * M_PI * radius),2);
    c = (72 - height) / 72;
    heading = acos(c);
    return (heading * (180.0 / M_PI));
}

void Navigation::updateEnc(int _encoderTicksL, int _encoderTicksR) {
    encoderTicksL = _encoderTicksL;
    encoderTicksR = _encoderTicksR;
}

void Navigation::updateGyro() {
    gyro.update();
}
