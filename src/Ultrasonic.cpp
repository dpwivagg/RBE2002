#include "Arduino.h"
#include "Ultrasonic.h"
#include "RobotMap.h"

Ultrasonic::Ultrasonic() {
}

unsigned short Ultrasonic::get() {
    return sensorState;
}

void Ultrasonic::init(unsigned char analogPort) {
    port = analogPort;
}

unsigned short Ultrasonic::getSensor() {
    return analogRead(port);
}

void Ultrasonic::update() {

    sensorState = getSensor();

    // Serial.print("sensor = ");
    // Serial.println(temp);
    // Serial.print("sensor = ");
    // Serial.println(sensorState);
}
