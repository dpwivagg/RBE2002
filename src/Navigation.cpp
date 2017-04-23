#include "Navigation.h"
#include "Chassis.h"
#include <math.h>

Navigation::Navigation() {}

bool Navigation::init() {
    return gyro.init();
}

double Navigation::getDir() {
    // TODO : Implement sensor fusion with gyro and encoders (currently only encoders are used)
    gyroRead = gyro.getZ();
    encoderError = encoderTicksL - encoderTicksR;
    height = pow((((double)encoderError / (double)encTicksPerRev) * 2 * M_PI * radius),2);
    c = (72 - height) / 72;
    heading = acos(c);
    return (0 - (heading * (180.0 / M_PI)));  // Returns the angle of displacement in degrees
    // See the page in our box for worked calculations
}

void Navigation::updateEnc(int _encoderTicksL, int _encoderTicksR) {
    encoderTicksL = _encoderTicksL;
    encoderTicksR = _encoderTicksR;
}

void Navigation::updateGyro() {
    gyro.update();
}
