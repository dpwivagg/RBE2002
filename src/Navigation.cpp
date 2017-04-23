#include "Navigation.h"
#include "Chassis.h"
#include <math.h>

Navigation::Navigation() {}

bool Navigation::init() {
    return gyro.init();
}

double Navigation::getDir() {
    gyroRead = gyro.getZ();
    encoderError = abs(encoderTicksL - encoderTicksR);
    height = ((encoderError / encTicksPerRev) * 2 * M_PI * radius);
    heading = 90 - atan2(height, wheelBase);
    return heading;
}

void Navigation::updateEnc(int _encoderTicksL, int _encoderTicksR) {
    encoderTicksL = _encoderTicksL;
    encoderTicksR = _encoderTicksR;
}

void Navigation::updateGyro() {
    gyro.update();
}
