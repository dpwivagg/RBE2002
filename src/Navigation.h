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
        int encoderTicksL;
        int encoderTicksR;
        int encoderError;
        int gyroRead;
        double heading;
        double height;
        double c;
        bool sign;

        const unsigned short encTicksPerRev = 600; // change this if needed
        const float radius = 1.375;
        const unsigned short wheelBase = 6;
};

#endif /* NAVIGATION_H_ */
