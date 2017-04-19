#include "Arduino.h"
#include "Ultrasonic.h"
#include "RobotMap.h"
#include <NewPing.h>

Ultrasonic::Ultrasonic() {
}

unsigned int Ultrasonic::getSide() {

}

unsigned int Ultrasonic::getFront() {
    return sensorState;
}

void Ultrasonic::init() {
}

bool Ultrasonic::wallAhead() {
    return getSensorFront() < getSensorSide();
}

unsigned int Ultrasonic::getSensorSide() {
    return (sonarRight.ping_cm() + sonarBack.ping_cm() / 2);
}

unsigned int Ultrasonic::getSensorFront() {
    return sonarFront.ping_cm();
}

void Ultrasonic::update() {
// set the sensor state to something based on what the get sensors returns
    //sensorState = getSensor();

    // Serial.print("sensor = ");
    // Serial.println(temp);
    // Serial.print("sensor = ");
    // Serial.println(sensorState);
}
