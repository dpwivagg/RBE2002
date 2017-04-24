/*
 * Ultrasonic.h
 *
 *  Created on: 4/15/17
 *      Author: james
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include <NewPing.h>
#include "RobotMap.h"

enum SonarStates {
    drive, // both side sensors are reading similar values
    wall, // the front sensor has reached a wall

    edge, // the side front sensor has passed a corner but the
    // back is still reading the wall--time to turn
    halfDrive // the side front sensor is next to the wall but the
    // back is not reading anything--drive forward until the back
    // reaches the wall
};
/**
 * Handles Ultrasonic information
 */
class Ultrasonic {
    public:
        Ultrasonic();
        unsigned short get();
        void init();
        void update();
        void updateLineSensor();
        bool safeToDrive();
        void lock();
        void unlock();
        SonarStates state;

    private:
        unsigned int calRight, calBack, currRight, currBack, currFront;
        bool lineSensor;
        unsigned int getSensorRight();
        unsigned int getSensorBack();
        unsigned int getSensorFront();
        bool writeableState = true;
        //bool wallAhead();
};

#endif /* Ultrasonic_H_ */
