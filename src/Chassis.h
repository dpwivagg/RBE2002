/*
 *  Chassis.h
 *
 *  Created on: 2/26/17
 *      Author: James and Dan
 */

#ifndef DRIVE_H_
#define DRIVE_H_

#include <Arduino.h>
#include "Servo.h"

/**
 * Handles linesensor information
 */
class Chassis {
    public:
        Chassis();
        void attach(unsigned char leftMotorFwd, unsigned char rightMotorFwd);
        void drive(signed char speed, signed char turn);
        void update();
        void stop();
        void instantStop();
        void drive(signed char speed);
        void turn(signed char turn);
        float driveStraight(float setpoint, float currentpoint);
        void instantGo (int go);


    private:
        void updateSinglePWM();

        signed char speedState = 0;
        signed char turnState = 0;

        void updateNav();

        Servo leftMotor;
        Servo rightMotor;

};

#endif /* DRIVE_H_ */
