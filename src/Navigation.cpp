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
    height = pow(((encoderError / encTicksPerRev) * 2 * M_PI * radius),2);
    heading = acos((72 - height) / 72);
    return round(heading);
}

void Navigation::updateEnc(int _encoderTicksL, int _encoderTicksR) {
    encoderTicksL = _encoderTicksL;
    encoderTicksR = _encoderTicksR;
}

void Navigation::updateGyro() {
    gyro.update();
}
