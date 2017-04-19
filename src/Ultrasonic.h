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
/**
 * Handles Ultrasonic information
 */
class Ultrasonic {
    public:
        Ultrasonic();
        unsigned int getSide();
        unsigned int getFront();
        void update();
        void init();
        bool wallAhead();

    private:
        unsigned int cm[3];
        bool sensorState;
        unsigned char port = 0;
        unsigned int getSensorSide();
        unsigned int getSensorFront();

        NewPing sonarFront(sonarFrontOut, sonarFrontIn, 300);
        NewPing sonarRight(sonarRightOut, sonarRightIn, 300);
        NewPing sonarBack(sonarBackOut, sonarBackIn, 300);
};

#endif /* Ultrasonic_H_ */
