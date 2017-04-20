#include "Arduino.h"
#include "Ultrasonic.h"
#include "RobotMap.h"
#include <NewPing.h>

Ultrasonic::Ultrasonic() {
}

unsigned int Ultrasonic::getSide() {
    return getSensorSide();
}

unsigned int Ultrasonic::getFront() {
    return getSensorFront();
}

void Ultrasonic::init() {
    // calibrate the wall sensor starting values
    calRight = sonarRight.ping_cm();
    calBack = sonarBack.ping_cm();

}

bool Ultrasonic::wallAhead() {
    return (getSensorFront() < getSensorSide());
}

bool Ultrasonic::clifAhead() {
    // is the front sensor reading out of range (>300cm)?
    return (getSensorFront() == 0);
}

unsigned int Ultrasonic::getSensorSide() {
    return (sonarRight.ping_cm() + sonarBack.ping_cm()) / 2;
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
// set the sensor state to something based on what the get sensors returns
    if(getSensorRight() > (2 * calRight))
}
