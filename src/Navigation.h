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

    private:
        Gyro gyro;
        int encoderTicksL;
        int encoderTicksR;

};

#endif /* NAVIGATION_H_ */
