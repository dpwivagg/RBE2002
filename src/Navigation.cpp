#include "Navigation.h"

Navigation::Navigation() {}

void Navigation::init() {

}

void Navigation::update(int _encoderTicksL, int _encoderTicksR) {
    encoderTicksL = _encoderTicksL;
    encoderTicksR = _encoderTicksR;
}
