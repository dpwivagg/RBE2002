/*
 * Navigation.h
 *
 *  Created on: 4/19/17
 *      Author: james
 */

#ifndef NAVIGATION_H_
#define NAVIGATION_H_

#include "Gyro.h"

/**
 * Handles nav information
 */
class Navigation {
    public:
        Navigation();
        void updateEnc(int encoderTicksL, int encoderTicksR);
        void updateGyro();
        bool init();
        double getDir();

    private:
        Gyro gyro;
        int encoderTicksL = 0;
        int encoderTicksR = 0;
        int encoderTicksOldL = 0;
        int encoderTicksOldR = 0;
        int encoderError;
        int gyroRead;
        double heading;
        double aheading;
        double height;
        double c;
        bool sign;

        double xDir = 0;
        double yDir = 0;

        const unsigned short encTicksPerRev = 600; // change this if needed
        const float radius = 1.375;
        const unsigned short wheelBase = 6;
};

#endif /* NAVIGATION_H_ */
